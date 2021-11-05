/******************************************************************************
 * Top contributors (to current version):
 *   Haniel Barbosa, Andrew Reynolds, Gereon Kremer
 *
 * This file is part of the cvc5 project.
 *
 * Copyright (c) 2009-2021 by the authors listed in the file AUTHORS
 * in the top-level source directory and their institutional affiliations.
 * All rights reserved.  See the file COPYING in the top-level source
 * directory for licensing information.
 * ****************************************************************************
 *
 * Implementation of lazy proof utility.
 */

#include "proof/lazy_proof_chain.h"

#include "options/proof_options.h"
#include "proof/proof.h"
#include "proof/proof_ensure_closed.h"
#include "proof/proof_node.h"
#include "proof/proof_node_algorithm.h"
#include "proof/proof_node_manager.h"

namespace cvc5 {

LazyCDProofChain::LazyCDProofChain(ProofNodeManager* pnm,
                                   bool cyclic,
                                   context::Context* c,
                                   ProofGenerator* defGen,
                                   bool defRec,
                                   const std::string& name)
    : d_manager(pnm),
      d_cyclic(cyclic),
      d_defRec(defRec),
      d_context(),
      d_gens(c ? c : &d_context),
      d_defGen(defGen),
      d_name(name)
{
}

LazyCDProofChain::~LazyCDProofChain() {}

const std::map<Node, std::shared_ptr<ProofNode>> LazyCDProofChain::getLinks()
    const
{
  std::map<Node, std::shared_ptr<ProofNode>> links;
  for (const std::pair<const Node, ProofGenerator* const>& link : d_gens)
  {
    Assert(link.second);
    std::shared_ptr<ProofNode> pfn = link.second->getProofFor(link.first);
    Assert(pfn);
    links[link.first] = pfn;
  }
  return links;
}

std::shared_ptr<ProofNode> LazyCDProofChain::getProofFor(Node fact)
{
  Trace("lazy-cdproofchain")
      << "LazyCDProofChain::getProofFor of gen " << d_name << "\n";
  Trace("lazy-cdproofchain")
      << "LazyCDProofChain::getProofFor: " << fact << "\n";
  // which facts have had proofs retrieved for. This is maintained to avoid
  // cycles. It also saves the proof node of the fact
  std::unordered_map<Node, std::shared_ptr<ProofNode>> toConnect;
  // leaves of proof node links in the chain, i.e. assumptions, yet to be
  // expanded
  std::unordered_map<Node, std::vector<std::shared_ptr<ProofNode>>>
      assumptionsToExpand;
  // invariant of the loop below, the first iteration notwithstanding:
  //   visit = domain(assumptionsToExpand) \ domain(toConnect)
  std::vector<Node> visit{fact};
  std::unordered_map<Node, bool> visited;
  Node cur;
  do
  {
    cur = visit.back();
    visit.pop_back();
    auto itVisited = visited.find(cur);
    // pre-traversal
    if (itVisited == visited.end())
    {
      Trace("lazy-cdproofchain")
          << "LazyCDProofChain::getProofFor: check " << cur << "\n";
      Assert(toConnect.find(cur) == toConnect.end());
      bool rec = true;
      ProofGenerator* pg = getGeneratorForInternal(cur, rec);
      if (!pg)
      {
        Trace("lazy-cdproofchain")
            << "LazyCDProofChain::getProofFor: nothing to do\n";
        // nothing to do for this fact, it'll be a leaf in the final proof
        // node, don't post-traverse.
        visited[cur] = true;
        continue;
      }
      Trace("lazy-cdproofchain")
          << "LazyCDProofChain::getProofFor: Call generator " << pg->identify()
          << " for chain link " << cur << "\n";
      std::shared_ptr<ProofNode> curPfn = pg->getProofFor(cur);
      if (curPfn == nullptr)
      {
        Trace("lazy-cdproofchain")
            << "LazyCDProofChain::getProofFor: No proof found, skip\n";
        visited[cur] = true;
        continue;
      }
      // map node whose proof node must be expanded to the respective poof node
      toConnect[cur] = curPfn;
      // We may not want to recursively connect this proof or, if it's
      // assumption, there is nothing to connect, so we skip. Note that in the
      // special case in which curPfn is an assumption and cur is actually the
      // initial fact that getProofFor is called on, the cycle detection below
      // would prevent this method from generating the assumption proof for it,
      // which would be wrong.
      if (!rec || curPfn->getRule() == PfRule::ASSUME)
      {
        visited[cur] = true;
        continue;
      }
      Trace("lazy-cdproofchain-debug")
          << "LazyCDProofChain::getProofFor: stored proof: " << *curPfn.get()
          << "\n";
      // retrieve free assumptions and their respective proof nodes
      std::map<Node, std::vector<std::shared_ptr<ProofNode>>> famap;
      expr::getFreeAssumptionsMap(curPfn, famap);
      if (Trace.isOn("lazy-cdproofchain"))
      {
        unsigned alreadyToVisit = 0;
        Trace("lazy-cdproofchain")
            << "LazyCDProofChain::getProofFor: " << famap.size()
            << " free assumptions:\n";
        for (auto fap : famap)
        {
          Trace("lazy-cdproofchain")
              << "LazyCDProofChain::getProofFor:  - " << fap.first << "\n";
          alreadyToVisit +=
              std::find(visit.begin(), visit.end(), fap.first) != visit.end()
                  ? 1
                  : 0;
        }
        Trace("lazy-cdproofchain")
            << "LazyCDProofChain::getProofFor: " << alreadyToVisit
            << " already to visit\n";
      }
      // If we are controlling cycle, check whether any of the assumptions of
      // cur would provoke a cycle. In such a case we treat cur as an
      // assumption, removing it from toConnect, and do not proceed to expand
      // any of its assumptions.
      if (d_cyclic)
      {
        Trace("lazy-cdproofchain") << "LazyCDProofChain::getProofFor: marking "
                                   << cur << " for cycle check\n";
        bool isCyclic = false;
        // enqueue free assumptions to process
        for (const auto& fap : famap)
        {
          // A cycle is characterized by cur having an assumption being
          // *currently* expanded that is seen again, i.e. in toConnect and not
          // yet post-visited
          auto itToConnect = toConnect.find(fap.first);
          if (itToConnect != toConnect.end() && !visited[fap.first])
          {
            // Since we have a cycle with an assumption, cur will be an
            // assumption in the final proof node produced by this
            // method.
            Trace("lazy-cdproofchain")
                << "LazyCDProofChain::getProofFor: cyclic assumption "
                << fap.first << "\n";
            isCyclic = true;
            break;
          }
        }
        if (isCyclic)
        {
          visited[cur] = true;
          Trace("lazy-cdproofchain")
              << "LazyCDProofChain::getProofFor: Removing " << cur
              << " from toConnect\n";
          auto itToConnect = toConnect.find(cur);
          toConnect.erase(itToConnect);
          continue;
        }
        visit.push_back(cur);
        visited[cur] = false;
      }
      else
      {
        visited[cur] = true;
      }
      // enqueue free assumptions to process
      for (const auto& fap : famap)
      {
        Trace("lazy-cdproofchain")
            << "LazyCDProofChain::getProofFor: marking " << fap.first
            << " for revisit and for expansion\n";
        // We always add assumptions to visit so that their last seen occurrence
        // is expanded (rather than the first seen occurrence, if we were not
        // adding assumptions, say, in assumptionsToExpand). This is so because
        // in the case where we are checking cycles this is necessary (and
        // harmless when we are not). For example the cycle
        //
        //                 a2
        //                ...
        //               ----
        //                a1
        //               ...
        //             --------
        //   a0   a1    a2
        //       ...
        //  ---------------
        //       n
        //
        // in which a2 has a1 as an assumption, which has a2 an assumption,
        // would not be captured if we did not revisit a1, which is an
        // assumption of n and this already occur in assumptionsToExpand when
        // it shows up again as an assumption of a2.
        visit.push_back(fap.first);
        // add assumption proof nodes to be updated
        assumptionsToExpand[fap.first].insert(
            assumptionsToExpand[fap.first].end(),
            fap.second.begin(),
            fap.second.end());
      }
      if (d_cyclic)
      {
        Trace("lazy-cdproofchain") << push;
        Trace("lazy-cdproofchain-debug") << push;
      }
    }
    else if (!itVisited->second)
    {
      visited[cur] = true;
      Trace("lazy-cdproofchain") << pop;
      Trace("lazy-cdproofchain-debug") << pop;
      Trace("lazy-cdproofchain")
          << "LazyCDProofChain::getProofFor: post-visited " << cur << "\n";
    }
    else
    {
      Trace("lazy-cdproofchain")
          << "LazyCDProofChain::getProofFor: already fully processed " << cur
          << "\n";
    }
  } while (!visit.empty());
  // expand all assumptions marked to be connected
  for (const std::pair<const Node, std::shared_ptr<ProofNode>>& npfn :
       toConnect)
  {
    auto it = assumptionsToExpand.find(npfn.first);
    if (it == assumptionsToExpand.end())
    {
      Assert(npfn.first == fact);
      continue;
    }
    Assert(npfn.second);
    Trace("lazy-cdproofchain")
        << "LazyCDProofChain::getProofFor: expand assumption " << npfn.first
        << "\n";
    Trace("lazy-cdproofchain-debug")
        << "LazyCDProofChain::getProofFor: ...expand to " << *npfn.second.get()
        << "\n";
    // update each assumption proof node
    for (std::shared_ptr<ProofNode> pfn : it->second)
    {
      d_manager->updateNode(pfn.get(), npfn.second.get());
    }
  }
  Trace("lazy-cdproofchain") << "===========\n";
  // final proof of fact
  auto it = toConnect.find(fact);
  if (it == toConnect.end())
  {
    return nullptr;
  }
  return it->second;
}

void LazyCDProofChain::addLazyStep(Node expected, ProofGenerator* pg)
{
  Assert(pg != nullptr);
  Trace("lazy-cdproofchain") << "LazyCDProofChain::addLazyStep: " << expected
                             << " set to generator " << pg->identify() << "\n";
  // note this will replace the generator for expected, if any
  d_gens.insert(expected, pg);
}

void LazyCDProofChain::addLazyStep(Node expected,
                                   ProofGenerator* pg,
                                   const std::vector<Node>& assumptions,
                                   const char* ctx)
{
  Assert(pg != nullptr);
  Trace("lazy-cdproofchain") << "LazyCDProofChain::addLazyStep: " << expected
                             << " set to generator " << pg->identify() << "\n";
  // note this will rewrite the generator for expected, if any
  d_gens.insert(expected, pg);
  // check if chain is closed if eager checking is on
  if (options::proofCheck() == options::ProofCheckMode::EAGER)
  {
    Trace("lazy-cdproofchain")
        << "LazyCDProofChain::addLazyStep: Checking closed proof...\n";
    std::shared_ptr<ProofNode> pfn = pg->getProofFor(expected);
    std::vector<Node> allowedLeaves{assumptions.begin(), assumptions.end()};
    // add all current links in the chain
    for (const std::pair<const Node, ProofGenerator* const>& link : d_gens)
    {
      allowedLeaves.push_back(link.first);
    }
    if (Trace.isOn("lazy-cdproofchain"))
    {
      Trace("lazy-cdproofchain") << "Checking relative to leaves...\n";
      for (const Node& n : allowedLeaves)
      {
        Trace("lazy-cdproofchain") << "  - " << n << "\n";
      }
      Trace("lazy-cdproofchain") << "\n";
    }
    pfnEnsureClosedWrt(pfn.get(), allowedLeaves, "lazy-cdproofchain", ctx);
  }
}

bool LazyCDProofChain::hasGenerator(Node fact) const
{
  return d_gens.find(fact) != d_gens.end();
}

ProofGenerator* LazyCDProofChain::getGeneratorFor(Node fact)
{
  bool rec = true;
  return getGeneratorForInternal(fact, rec);
}

ProofGenerator* LazyCDProofChain::getGeneratorForInternal(Node fact, bool& rec)
{
  auto it = d_gens.find(fact);
  if (it != d_gens.end())
  {
    return (*it).second;
  }
  // otherwise, if no explicit generators, we use the default one
  if (d_defGen != nullptr)
  {
    rec = d_defRec;
    return d_defGen;
  }
  return nullptr;
}

std::string LazyCDProofChain::identify() const { return d_name; }

}  // namespace cvc5
