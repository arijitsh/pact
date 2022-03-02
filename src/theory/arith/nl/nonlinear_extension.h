/******************************************************************************
 * Top contributors (to current version):
 *   Andrew Reynolds, Gereon Kremer, Tim King
 *
 * This file is part of the cvc5 project.
 *
 * Copyright (c) 2009-2021 by the authors listed in the file AUTHORS
 * in the top-level source directory and their institutional affiliations.
 * All rights reserved.  See the file COPYING in the top-level source
 * directory for licensing information.
 * ****************************************************************************
 *
 * Extensions to the theory of arithmetic incomplete handling of nonlinear
 * multiplication via axiom instantiations.
 */

#ifndef CVC5__THEORY__ARITH__NL__NONLINEAR_EXTENSION_H
#define CVC5__THEORY__ARITH__NL__NONLINEAR_EXTENSION_H

#include <map>
#include <vector>

#include "expr/node.h"
#include "smt/env_obj.h"
#include "theory/arith/nl/coverings_solver.h"
#include "theory/arith/nl/ext/ext_state.h"
#include "theory/arith/nl/ext/factoring_check.h"
#include "theory/arith/nl/ext/monomial_bounds_check.h"
#include "theory/arith/nl/ext/monomial_check.h"
#include "theory/arith/nl/ext/proof_checker.h"
#include "theory/arith/nl/ext/split_zero_check.h"
#include "theory/arith/nl/ext/tangent_plane_check.h"
#include "theory/arith/nl/ext_theory_callback.h"
#include "theory/arith/nl/iand_solver.h"
#include "theory/arith/nl/icp/icp_solver.h"
#include "theory/arith/nl/nl_model.h"
#include "theory/arith/nl/pow2_solver.h"
#include "theory/arith/nl/stats.h"
#include "theory/arith/nl/strategy.h"
#include "theory/arith/nl/transcendental/transcendental_solver.h"
#include "theory/ext_theory.h"
#include "theory/theory.h"
#include "util/result.h"

namespace cvc5 {
namespace theory {
namespace eq {
  class EqualityEngine;
}
namespace arith {

class InferenceManager;
class TheoryArith;

namespace nl {

class NlLemma;

/** Non-linear extension class
 *
 * This class implements model-based refinement schemes
 * for non-linear arithmetic, described in:
 *
 * - "Invariant Checking of NRA Transition Systems
 * via Incremental Reduction to LRA with EUF" by
 * Cimatti et al., TACAS 2017.
 *
 * - Section 5 of "Desiging Theory Solvers with
 * Extensions" by Reynolds et al., FroCoS 2017.
 *
 * - "Satisfiability Modulo Transcendental
 * Functions via Incremental Linearization" by Cimatti
 * et al., CADE 2017.
 *
 * It's main functionality is a check(...) method,
 * which is called by TheoryArithPrivate either:
 * (1) at full effort with no conflicts or lemmas emitted, or
 * (2) at last call effort.
 * In this method, this class calls d_im.lemma(...)
 * for valid arithmetic theory lemmas, based on the current set of assertions,
 * where d_im is the inference manager of TheoryArith.
 */
class NonlinearExtension : EnvObj
{
  typedef context::CDHashSet<Node> NodeSet;

 public:
  NonlinearExtension(Env& env, TheoryArith& containing, ArithState& state);
  ~NonlinearExtension();
  /**
   * Does non-context dependent setup for a node connected to a theory.
   */
  void preRegisterTerm(TNode n);

  /**
   * Performs the main checks for nonlinear arithmetic, based on the current
   * (linear) arithmetic model from `arithModel`. This method may already send
   * lemmas, but most lemmas are stored and only sent when finalizeModel
   * is called.
   *
   * The argument arithModel is a map of the form { v1 -> c1, ..., vn -> cn }
   * which represents the linear arithmetic theory solver's contribution to the
   * current candidate model where v1, ..., vn are arithmetic variables and
   * c1, ..., cn are constants. Note, that arithmetic variables may be
   * real-valued terms belonging to other theories, or abstractions of
   * applications of multiplication (kind NONLINEAR_MULT).
   *
   * The argument termSet is the set of terms that is currently appearing in the
   * assertions.
   */
  void checkFullEffort(std::map<Node, Node>& arithModel,
                       const std::set<Node>& termSet);

  /** Does this class need a call to check(...) at last call effort? */
  bool hasNlTerms() const { return d_hasNlTerms; }

  /** Process side effect se */
  void processSideEffect(const NlLemma& se);

 private:
  /** Model-based refinement
   *
   * This is the main entry point of this class for generating lemmas on the
   * output channel of the theory of arithmetic.
   *
   * It is currently run at last call effort. It applies lemma schemas
   * described in Reynolds et al. FroCoS 2017 that are based on ruling out
   * the current candidate model.
   *
   * This function returns whether we found a satisfying assignment
   * (Result::Sat::SAT), or not (Result::Sat::UNSAT). Note that UNSAT does not
   * necessarily means the whole query is UNSAT, but that the linear model was
   * refuted by a lemma.
   */
  Result::Sat modelBasedRefinement(const std::set<Node>& termSet);

  /** get assertions
   *
   * Let M be the set of assertions known by THEORY_ARITH. This function adds a
   * set of literals M' to assertions such that M' and M are equivalent.
   *
   * Examples of how M' differs with M:
   * (1) M' may not include t < c (in M) if t < c' is in M' for c' < c, where
   * c and c' are constants,
   * (2) M' may contain t = c if both t >= c and t <= c are in M.
   */
  void getAssertions(std::vector<Node>& assertions);
  /** check model
   *
   * Returns the subset of assertions whose concrete values we cannot show are
   * true in the current model. Notice that we typically cannot compute concrete
   * values for assertions involving transcendental functions. Any assertion
   * whose model value cannot be computed is included in the return value of
   * this function.
   */
  std::vector<Node> getUnsatisfiedAssertions(
      const std::vector<Node>& assertions);

  //---------------------------check model
  /** Check model
   *
   * Checks the current model based on solving for equalities, and using error
   * bounds on the Taylor approximation.
   *
   * If this function returns true, then all assertions in the input argument
   * "assertions" are satisfied for all interpretations of variables within
   * their computed bounds (as stored in d_check_model_bounds).
   *
   * For details, see Section 3 of Cimatti et al CADE 2017 under the heading
   * "Detecting Satisfiable Formulas".
   */
  bool checkModel(const std::vector<Node>& assertions);
  //---------------------------end check model
  /** compute relevant assertions */
  void computeRelevantAssertions(const std::vector<Node>& assertions,
                                 std::vector<Node>& keep);

  /** run check strategy
   *
   * Check assertions for consistency in the effort LAST_CALL with a subset of
   * the assertions, false_asserts, that evaluate to false in the current model.
   *
   * xts : the list of (non-reduced) extended terms in the current context.
   *
   * This method adds lemmas to d_im directly.
   */
  void runStrategy(Theory::Effort effort,
                   const std::vector<Node>& assertions,
                   const std::vector<Node>& false_asserts,
                   const std::vector<Node>& xts);

  /** commonly used terms */
  Node d_zero;
  Node d_one;
  Node d_neg_one;
  Node d_true;
  // The theory of arithmetic containing this extension.
  TheoryArith& d_containing;
  /** A reference to the arithmetic state object */
  ArithState& d_astate;
  InferenceManager& d_im;
  /** The statistics class */
  NlStats d_stats;
  // needs last call effort
  bool d_hasNlTerms;
  /**
   * The number of times we have the called main check method
   * (modelBasedRefinement). This counter is used for interleaving strategies.
   */
  unsigned d_checkCounter;
  /** The callback for the extended theory below */
  NlExtTheoryCallback d_extTheoryCb;
  /** Extended theory, responsible for context-dependent simplification. */
  ExtTheory d_extTheory;
  /** The non-linear model object
   *
   * This class is responsible for computing model values for arithmetic terms
   * and for establishing when we are able to answer "SAT".
   */
  NlModel d_model;

  /** The transcendental extension object
   *
   * This is the subsolver responsible for running the procedure for
   * transcendental functions.
   */
  transcendental::TranscendentalSolver d_trSlv;
  /** The proof checker for proofs of the nlext. */
  ExtProofRuleChecker d_proofChecker;
  /**
   * Holds common lookup data for the checks implemented in the "nl-ext"
   * solvers (from Cimatti et al., TACAS 2017).
   */
  ExtState d_extState;
  /** Solver for factoring lemmas. */
  FactoringCheck d_factoringSlv;
  /** Solver for lemmas about monomial bounds. */
  MonomialBoundsCheck d_monomialBoundsSlv;
  /** Solver for lemmas about monomials. */
  MonomialCheck d_monomialSlv;
  /** Solver for lemmas that split multiplication at zero. */
  SplitZeroCheck d_splitZeroSlv;
  /** Solver for tangent plane lemmas. */
  TangentPlaneCheck d_tangentPlaneSlv;
  /** The coverings-based solver */
  CoveringsSolver d_covSlv;
  /** The ICP-based solver */
  icp::ICPSolver d_icpSlv;
  /** The integer and solver
   *
   * This is the subsolver responsible for running the procedure for
   * constraints involving integer and.
   */
  IAndSolver d_iandSlv;

  /** The pow2 solver
   *
   * This is the subsolver responsible for running the procedure for
   * constraints involving powers of 2.
   */
  Pow2Solver d_pow2Slv;

  /** The strategy for the nonlinear extension. */
  Strategy d_strategy;
}; /* class NonlinearExtension */

}  // namespace nl
}  // namespace arith
}  // namespace theory
}  // namespace cvc5

#endif /* CVC5__THEORY__ARITH__NONLINEAR_EXTENSION_H */
