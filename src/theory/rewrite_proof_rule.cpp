/*********************                                                        */
/*! \file rewrite_proof_rule.cpp
 ** \verbatim
 ** Top contributors (to current version):
 **   Andrew Reynolds
 ** This file is part of the CVC4 project.
 ** Copyright (c) 2009-2019 by the authors listed in the file AUTHORS
 ** in the top-level source directory) and their institutional affiliations.
 ** All rights reserved.  See the file COPYING in the top-level source
 ** directory for licensing information.\endverbatim
 **
 ** \brief Implementation of rewrite proof rule
 **/

#include "theory/rewrite_proof_rule.h"

#include <sstream>

#include "expr/node_algorithm.h"
#include "proof/proof_checker.h"
#include "theory/rewrite_db_sc.h"
#include "theory/rewrite_db_term_process.h"

using namespace cvc5::kind;
using namespace cvc5::theory::rewriter;

namespace cvc5 {
namespace theory {

bool getDslPfRule(TNode n, DslPfRule& id)
{
  uint32_t i;
  if (ProofRuleChecker::getUInt32(n, i))
  {
    id = static_cast<DslPfRule>(i);
    return true;
  }
  return false;
}

RewriteProofRule::RewriteProofRule() : d_id(DslPfRule::FAIL) {}

void RewriteProofRule::init(DslPfRule id,
                            const std::vector<Node>& fvs,
                            const std::vector<Node>& cond,
                            Node conc)
{
  d_id = id;
  d_cond.clear();
  d_obGen.clear();
  // Must purify side conditions from the condition. For each subterm of
  // condition c that is an application of a side condition, we replace it
  // with a free variable and add its definition to d_scs. In the end,
  // d_cond contains formulas that have no side conditions, but may have
  // (internally generated) variables.
  for (const Node& c : cond)
  {
    d_cond.push_back(c);
    Node cc = purifySideConditions(c, d_scs);
    d_obGen.push_back(cc);
  }
  d_conc = conc;

  d_numFv = fvs.size();

  std::unordered_set<Node> fvsCond;
  for (const Node& c : d_cond)
  {
    expr::getFreeVariables(c, fvsCond);
  }
  for (const Node& v : fvs)
  {
    d_fvs.push_back(v);
    if (fvsCond.find(v) == fvsCond.end())
    {
      d_noOccVars[v] = true;
    }
  }
}

Node RewriteProofRule::purifySideConditions(Node n, std::vector<Node>& scs)
{
  NodeManager* nm = NodeManager::currentNM();
  std::unordered_map<TNode, Node> visited;
  std::unordered_map<TNode, Node>::iterator it;
  std::vector<TNode> visit;
  TNode cur;
  visit.push_back(n);
  do
  {
    cur = visit.back();
    visit.pop_back();
    it = visited.find(cur);

    if (it == visited.end())
    {
      visited[cur] = Node::null();
      visit.push_back(cur);
      visit.insert(visit.end(), cur.begin(), cur.end());
    }
    else if (it->second.isNull())
    {
      Node ret = cur;
      bool childChanged = false;
      std::vector<Node> children;
      for (const Node& cn : cur)
      {
        it = visited.find(cn);
        Assert(it != visited.end());
        Assert(!it->second.isNull());
        childChanged = childChanged || cn != it->second;
        children.push_back(it->second);
      }
      if (childChanged)
      {
        if (cur.getMetaKind() == metakind::PARAMETERIZED)
        {
          children.insert(children.begin(), cur.getOperator());
        }
        ret = nm->mkNode(cur.getKind(), children);
      }
      if (ret.getKind() == APPLY_UF)
      {
        // Is it a side condition? If so, we replace by a fresh variable
        // and store the defining equality into scs.
        if (RewriteDbSc::isSideCondition(ret.getOperator()))
        {
          std::stringstream ss;
          ss << "k" << (scs.size() + 1);
          Node k = nm->mkBoundVar(ss.str(), cur.getType());
          Node scEq = ret.eqNode(k);
          scs.push_back(scEq);
          ret = k;
        }
      }
      visited[cur] = ret;
    }
  } while (!visit.empty());
  Assert(visited.find(n) != visited.end());
  Assert(!visited.find(n)->second.isNull());
  return visited[n];
}

const char* RewriteProofRule::getName() const { return toString(d_id); }

const std::vector<Node>& RewriteProofRule::getVarList() const
{
  return d_fvs;
}
bool RewriteProofRule::isExplicitVar(Node v) const
{
  Assert (std::find(d_fvs.begin(), d_fvs.end(), v)!=d_fvs.end());
  return d_noOccVars.find(v)!=d_noOccVars.end();
}
bool RewriteProofRule::hasConditions() const { return !d_cond.empty(); }

const std::vector<Node>& RewriteProofRule::getConditions() const
{
  return d_cond;
}

bool RewriteProofRule::hasSideConditions() const { return !d_scs.empty(); }

bool RewriteProofRule::getObligations(const std::vector<Node>& vs,
                                      const std::vector<Node>& ss,
                                      std::vector<Node>& vcs) const
{
  if (!d_scs.empty())
  {
    return runSideConditions(vs, ss, vcs);
  }
  // otherwise, just substitute into each condition
  for (const Node& c : d_obGen)
  {
    Node sc = c.substitute(vs.begin(), vs.end(), ss.begin(), ss.end());
    vcs.push_back(sc);
  }
  return true;
}

bool RewriteProofRule::runSideConditions(const std::vector<Node>& vs,
                                         const std::vector<Node>& ss,
                                         std::vector<Node>& vcs) const
{
  // the side condition substitution
  std::vector<Node> vctx = vs;
  std::vector<Node> sctx = ss;
  for (const Node& sc : d_scs)
  {
    Assert(sc.getKind() == kind::EQUAL);
    Node sct = sc[0];
    Assert(sct.getKind() == kind::APPLY_UF);
    Node f = sct.getOperator();
    std::vector<Node> scArgs;
    for (const Node& a : sct)
    {
      Node sa =
          a.substitute(vctx.begin(), vctx.end(), sctx.begin(), sctx.end());
      scArgs.push_back(sa);
    }
    // evaluate the side condition
    Node res = RewriteDbSc::evaluate(f, scArgs);
    if (res.isNull())
    {
      // the side condition failed, return false
      return false;
    }
    // store it in the substitution we are building
    vctx.push_back(sc[1]);
    sctx.push_back(res);
  }
  for (const Node& c : d_obGen)
  {
    Node sc = c.substitute(vctx.begin(), vctx.end(), sctx.begin(), sctx.end());
    vcs.push_back(sc);
  }
  return true;
}

Node RewriteProofRule::getConclusion() const { return d_conc; }

}  // namespace theory
}  // namespace cvc5
