/******************************************************************************
 * Top contributors (to current version):
 *   Arijit Shaw
 *
 * This file is part of the cvc5 project.
 *
 * Copyright (c) 2009-2022 by the authors listed in the file AUTHORS
 * in the top-level source directory and their institutional affiliations.
 * All rights reserved.  See the file COPYING in the top-level source
 * directory for licensing information.
 * ****************************************************************************
 *
 * Word-level function generator.
 *
 * Implementation Hash function generator needed for counting with SMTApproxMC.
 */

#include "cvc5_private.h"
#include <vector>

#ifndef CVC5__SMT__APXMC_H
#define CVC5__SMT__APXMC_H

#include "smt/env_obj.h"
#include "expr/node_algorithm.h"

using std::vector;

namespace cvc5::internal {
namespace counting {

class SmtApproxMc;

class SmtApproxMc
{
 private:
  SolverEngine* d_slv;
  uint32_t width = 0, num_bv = 0, num_bool;
  uint32_t slice_size = 2;
  vector<uint64_t> primes;
  std::unordered_set<Node> bvnodes_in_formula;
  std::vector<Node> bvnode_in_formula_v;
  std::vector<Term> bvs_in_formula, bvs_in_formula_aux;
  Term ff[100];
  int verb = 0;

 public:
  SmtApproxMc(SolverEngine* slv);
  virtual ~SmtApproxMc(){}

  void populatePrimes();
  vector<Node> generateNHashes(uint32_t numHashes);
  Term generate_hash();
  uint64_t smtApproxMcMain();
  uint64_t smtApproxMcCore();
  uint32_t getPivot();
  uint32_t getNumIter();
  template<class T> T findMedian(vector<T>& numList);

};

}  //namespace counting
}  // namespace cvc5::internal
#endif
