/*********************                                                        */
/*! \file let_binding.cpp
 ** \verbatim
 ** Top contributors (to current version):
 **   Andrew Reynolds
 ** This file is part of the CVC4 project.
 ** Copyright (c) 2009-2020 by the authors listed in the file AUTHORS
 ** in the top-level source directory) and their institutional affiliations.
 ** All rights reserved.  See the file COPYING in the top-level source
 ** directory for licensing information.\endverbatim
 **
 ** \brief A let binding
 **/

#include "proof/lfsc/let_binding.h"

#include "proof/lfsc/letify.h"

namespace CVC4 {
namespace proof {
  
LetBinding::LetBinding(uint32_t thresh) : d_thresh(thresh), d_context(), d_visitList(&d_context), d_count(&d_context), d_letList(&d_context), d_letMap(&d_context){}

void LetBinding::push(Node n, std::vector< std::pair<Node, Node> >& letList)
{
  d_context.push();
  if (d_thresh == 0)
  {
    // value of 0 means do not introduce let
    return;
  }
  // update the count of occurrences
  updateCounts(n);
  // Now populate the d_letList and d_letMap
  convertCountToLet();
  // add the new entries to the letList
}

void LetBinding::pop()
{
  d_context.pop();
}

uint32_t LetBinding::getId(Node n) const
{
  NodeIdMap::const_iterator it = d_letMap.find(n);
  if (it==d_letMap.end())
  {
    return 0;
  }
  return (*it).second;
}

Node LetBinding::convert(Node n,
                      const std::string& prefix) const
{

  if (d_letMap.empty())
  {
    return n;
  }
  std::map<Node, uint32_t>::const_iterator itl;
  NodeManager* nm = NodeManager::currentNM();
  std::unordered_map<TNode, Node, TNodeHashFunction> visited;
  std::unordered_map<TNode, Node, TNodeHashFunction>::iterator it;
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
      uint32_t id = getId(cur);
      // do not letify id 0
      if (id>0)
      {
        // make the let variable
        std::stringstream ss;
        ss << prefix << itl->second;
        visited[cur] = nm->mkBoundVar(ss.str(), cur.getType());
      }
      else
      {
        visited[cur] = Node::null();
        visit.push_back(cur);
        visit.insert(visit.end(), cur.begin(), cur.end());
      }
    }
    else if (it->second.isNull())
    {
      Node ret = cur;
      bool childChanged = false;
      std::vector<Node> children;
      if (cur.getMetaKind() == kind::metakind::PARAMETERIZED)
      {
        children.push_back(cur.getOperator());
      }
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
        ret = nm->mkNode(cur.getKind(), children);
      }
      visited[cur] = ret;
    }
  } while (!visit.empty());
  Assert(visited.find(n) != visited.end());
  Assert(!visited.find(n)->second.isNull());
  return visited[n];
}


void LetBinding::updateCounts(Node n)
{
  NodeIdMap::iterator it;
  std::vector<Node> visit;
  TNode cur;
  visit.push_back(n);
  do
  {
    cur = visit.back();
    it = d_count.find(cur);
    if (it == d_count.end())
    {
      // do not traverse beneath quantifiers
      if (cur.getNumChildren() == 0 || cur.isClosure())
      {
        d_visitList.push_back(cur);
        d_count[cur] = 1;
      }
      else
      {
        d_count[cur] = 0;
        visit.insert(visit.end(), cur.begin(), cur.end());
      }
    }
    else
    {
      if ((*it).second == 0)
      {
        d_visitList.push_back(cur);
      }
      d_count[cur] = (*it).second + 1;
      visit.pop_back();
    }
  } while (!visit.empty());
}

void LetBinding::convertCountToLet()
{
  Assert (d_thresh > 0);
  // Assign ids for those whose d_count is > 1, traverse in reverse order
  // so that deeper proofs are assigned lower identifiers
  NodeIdMap::const_iterator itc;
  for (const Node& n : d_visitList)
  {
    if (n.getNumChildren() == 0)
    {
      // do not letify terms with no children
      continue;
    }
    else if (d_letMap.find(n)!=d_letMap.end())
    {
      // already letified, perhaps at a lower context
      continue;
    }
    itc = d_count.find(n);
    Assert(itc != d_count.end());
    if ((*itc).second >= d_thresh)
    {
      d_letList.push_back(n);
      // start with id 1
      size_t id = d_letMap.size() + 1;
      d_letMap[n] = id;
    }
  }
}

}  // namespace proof
}  // namespace CVC4

