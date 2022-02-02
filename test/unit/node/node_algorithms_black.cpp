/******************************************************************************
 * Top contributors (to current version):
 *   Gereon Kremer
 *
 * This file is part of the cvc5 project.
 *
 * Copyright (c) 2009-2021 by the authors listed in the file AUTHORS
 * in the top-level source directory and their institutional affiliations.
 * All rights reserved.  See the file COPYING in the top-level source
 * directory for licensing information.
 * ****************************************************************************
 *
 * Black box testing of expr/algorithms/
 */

#include "base/output.h"
#include "expr/algorithm/flatten.h"
#include "expr/node_manager.h"
#include "test_node.h"

namespace cvc5 {

using namespace expr;
using namespace kind;

namespace test {

class TestNodeBlackNodeAlgorithms : public TestNode
{
};

TEST_F(TestNodeBlackNodeAlgorithms, flatten)
{
  {
    Node x = d_nodeManager->mkBoundVar(*d_realTypeNode);
    Node n = d_nodeManager->mkNode(Kind::PLUS, x, x);
    EXPECT_FALSE(expr::algorithm::canFlatten(n));
    EXPECT_FALSE(expr::algorithm::canFlatten(n, Kind::PLUS));
    EXPECT_FALSE(expr::algorithm::canFlatten(n, Kind::MULT));
    EXPECT_FALSE(expr::algorithm::canFlatten(n, Kind::PLUS, Kind::MULT));
    EXPECT_EQ(expr::algorithm::flatten(n), n);
    EXPECT_EQ(expr::algorithm::flatten(n, Kind::PLUS), n);
    EXPECT_EQ(expr::algorithm::flatten(n, Kind::MULT), n);
    EXPECT_EQ(expr::algorithm::flatten(n, Kind::PLUS, Kind::MULT), n);

    {
      std::vector<TNode> children;
      expr::algorithm::flatten(n, children);
      EXPECT_EQ(children.size(), 2);
      EXPECT_EQ(children[0], x);
      EXPECT_EQ(children[1], x);
    }
    {
      std::vector<TNode> children;
      expr::algorithm::flatten(n, children, Kind::PLUS);
      EXPECT_EQ(children.size(), 2);
      EXPECT_EQ(children[0], x);
      EXPECT_EQ(children[1], x);
    }
    {
      std::vector<TNode> children;
      expr::algorithm::flatten(n, children, Kind::MULT);
      EXPECT_EQ(children.size(), 1);
      EXPECT_EQ(children[0], n);
    }
    {
      std::vector<TNode> children;
      expr::algorithm::flatten(n, children, Kind::PLUS, Kind::MULT);
      EXPECT_EQ(children.size(), 2);
      EXPECT_EQ(children[0], x);
      EXPECT_EQ(children[1], x);
    }
  }
  {
    Node x = d_nodeManager->mkBoundVar(*d_realTypeNode);
    Node n = d_nodeManager->mkNode(
        Kind::PLUS, x, d_nodeManager->mkNode(Kind::PLUS, x, x));
    EXPECT_TRUE(expr::algorithm::canFlatten(n));
    EXPECT_TRUE(expr::algorithm::canFlatten(n, Kind::PLUS));
    EXPECT_FALSE(expr::algorithm::canFlatten(n, Kind::MULT));
    EXPECT_TRUE(expr::algorithm::canFlatten(n, Kind::PLUS, Kind::MULT));
    EXPECT_NE(expr::algorithm::flatten(n), n);
    EXPECT_NE(expr::algorithm::flatten(n, Kind::PLUS), n);
    EXPECT_EQ(expr::algorithm::flatten(n, Kind::MULT), n);
    EXPECT_NE(expr::algorithm::flatten(n, Kind::PLUS, Kind::MULT), n);

    {
      std::vector<TNode> children;
      expr::algorithm::flatten(n, children);
      EXPECT_EQ(children.size(), 3);
      EXPECT_EQ(children[0], x);
      EXPECT_EQ(children[1], x);
      EXPECT_EQ(children[2], x);
    }
    {
      std::vector<TNode> children;
      expr::algorithm::flatten(n, children, Kind::PLUS);
      EXPECT_EQ(children.size(), 3);
      EXPECT_EQ(children[0], x);
      EXPECT_EQ(children[1], x);
      EXPECT_EQ(children[2], x);
    }
    {
      std::vector<TNode> children;
      expr::algorithm::flatten(n, children, Kind::MULT);
      EXPECT_EQ(children.size(), 1);
      EXPECT_EQ(children[0], n);
    }
    {
      std::vector<TNode> children;
      expr::algorithm::flatten(n, children, Kind::PLUS, Kind::MULT);
      EXPECT_EQ(children.size(), 3);
      EXPECT_EQ(children[0], x);
      EXPECT_EQ(children[1], x);
      EXPECT_EQ(children[2], x);
    }
  }
  {
    Node x = d_nodeManager->mkBoundVar(*d_realTypeNode);
    Node n = d_nodeManager->mkNode(
        Kind::PLUS, x, d_nodeManager->mkNode(Kind::MULT, x, x));
    EXPECT_FALSE(expr::algorithm::canFlatten(n));
    EXPECT_FALSE(expr::algorithm::canFlatten(n, Kind::PLUS));
    EXPECT_FALSE(expr::algorithm::canFlatten(n, Kind::MULT));
    EXPECT_TRUE(expr::algorithm::canFlatten(n, Kind::PLUS, Kind::MULT));
    EXPECT_EQ(expr::algorithm::flatten(n), n);
    EXPECT_EQ(expr::algorithm::flatten(n, Kind::PLUS), n);
    EXPECT_EQ(expr::algorithm::flatten(n, Kind::MULT), n);
    EXPECT_NE(expr::algorithm::flatten(n, Kind::PLUS, Kind::MULT), n);

    {
      std::vector<TNode> children;
      expr::algorithm::flatten(n, children);
      EXPECT_EQ(children.size(), 2);
      EXPECT_EQ(children[0], x);
      EXPECT_EQ(children[1], n[1]);
    }
    {
      std::vector<TNode> children;
      expr::algorithm::flatten(n, children, Kind::PLUS);
      EXPECT_EQ(children.size(), 2);
      EXPECT_EQ(children[0], x);
      EXPECT_EQ(children[1], n[1]);
    }
    {
      std::vector<TNode> children;
      expr::algorithm::flatten(n, children, Kind::MULT);
      EXPECT_EQ(children.size(), 1);
      EXPECT_EQ(children[0], n);
    }
    {
      std::vector<TNode> children;
      expr::algorithm::flatten(n, children, Kind::PLUS, Kind::MULT);
      EXPECT_EQ(children.size(), 3);
      EXPECT_EQ(children[0], x);
      EXPECT_EQ(children[1], x);
      EXPECT_EQ(children[2], x);
    }
  }
}

}  // namespace test
}  // namespace cvc5
