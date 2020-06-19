/*********************                                                        */
/*! \file rewrite_db_sc.h
 ** \verbatim
 ** Top contributors (to current version):
 **   Andrew Reynolds
 ** This file is part of the CVC4 project.
 ** Copyright (c) 2009-2019 by the authors listed in the file AUTHORS
 ** in the top-level source directory) and their institutional affiliations.
 ** All rights reserved.  See the file COPYING in the top-level source
 ** directory for licensing information.\endverbatim
 **
 ** \brief Rewrite database side conditions
 **/

#include "cvc4_private.h"

#ifndef CVC4__THEORY__REWRITE_DB_SC__H
#define CVC4__THEORY__REWRITE_DB_SC__H

#include <map>
#include <vector>

#include "expr/node.h"

namespace CVC4 {
namespace theory {

/**
 * A database of conditional rewrite rules.
 */
class RdbSideConditionEvaluator
{
 public:
  RdbSideConditionEvaluator();
  ~RdbSideConditionEvaluator() {}
  /** is side condition */
  static bool isSideCondition(Node f);
  /** run side condition */
  static Node runSideCondition(Node f, const std::vector<Node>& args);
};

// TrustNode prove(Node a, Node b);

}  // namespace theory
}  // namespace CVC4

#endif /* CVC4__THEORY__REWRITE_DB_SC__H */
