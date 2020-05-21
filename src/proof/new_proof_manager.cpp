/*********************                                                        */
/*! \file new_proof_manager.cpp
 ** \verbatim
 ** Top contributors (to current version):
 **   Haniel Barbosa
 ** This file is part of the CVC4 project.
 ** Copyright (c) 2009-2019 by the authors listed in the file AUTHORS
 ** in the top-level source directory) and their institutional affiliations.
 ** All rights reserved.  See the file COPYING in the top-level source
 ** directory for licensing information.\endverbatim
 **
 ** \brief A new manager for Proofs
 **/

#include "proof/new_proof_manager.h"

#include "base/check.h"
#include "context/context.h"
#include "options/bv_options.h"
#include "options/proof_options.h"
#include "proof/clause_id.h"
#include "proof/proof_utils.h"
#include "proof/resolution_bitvector_proof.h"
#include "proof/sat_proof_implementation.h"
#include "proof/theory_proof.h"
#include "prop/minisat/core/Solver.h"
#include "smt/smt_engine.h"
#include "smt/smt_engine_scope.h"
#include "smt/smt_statistics_registry.h"
#include "theory/arrays/theory_arrays.h"
#include "theory/output_channel.h"
#include "theory/term_registration_visitor.h"
#include "theory/uf/equality_engine.h"
#include "theory/uf/theory_uf.h"
#include "theory/valuation.h"
#include "util/hash.h"
#include "util/proof.h"

namespace CVC4 {

NewProofManager::NewProofManager(TheoryEngine* te)
    : d_theoryEngine(te),
      d_pnm(new ProofNodeManager(new ProofChecker)),
      d_cdproof(d_pnm.get())
{
}

NewProofManager::~NewProofManager() {}

NewProofManager* NewProofManager::currentPM()
{
  return smt::currentNewProofManager();
}

void NewProofManager::addStep(Node expected,
                              PfRule rule,
                              const std::vector<Node>& children,
                              const std::vector<Node>& args)
{
  if (!d_cdproof.addStep(expected, rule, children, args))
  {
    Assert(false) << "NewProofManager::couldn't add " << rule
                  << " step with conclusion: " << expected
                  << ", children: " << children << ", args: " << args << "\n";
  }
}


inline void NewProofManager::printLit(const Minisat::Solver::TLit lit)
{
  Debug("newproof::sat") << (Minisat::sign(lit) ? "-" : "")
                         << Minisat::var(lit) + 1 << " ";
}

inline void NewProofManager::printClause(const Minisat::Solver::TClause& clause)
{
  for (unsigned i = 0, size = clause.size(); i < size; ++i)
  {
    Debug("newproof::sat") << (Minisat::sign(clause[i]) ? "-" : "")
                           << Minisat::var(clause[i]) + 1 << " ";
    if (Debug.isOn("newproof::sat::cnf"))
    {
      prop::SatLiteral satLit = toSatLiteral<Minisat::Solver>(clause[i]);
      Assert(d_litToNode.find(satLit) != d_litToNode.end());
      Debug("newproof::sat::cnf") << "[" << d_litToNode[satLit] << "] ";
    }
  }
}

void NewProofManager::addLitDef(prop::SatLiteral lit, Node litNode)
{
  Debug("newproof::sat") << "NewProofManager::addLitDef: lit/def: " << lit
                         << " / " << litNode << "\n";
  d_litToNode[lit] = litNode;
}

void NewProofManager::registerClause(Minisat::Solver::TLit lit)
{
  prop::SatLiteral satLit = toSatLiteral<Minisat::Solver>(lit);
  auto it = d_litToClauseId.find(satLit);
  if (it != d_litToClauseId.end())
  {
    if (Debug.isOn("newproof::sat"))
    {
      Debug("newproof::sat")
          << "NewProofManager::registerClause: id " << it->second << ", TLit: ";
      printLit(lit);
      Debug("newproof::sat") << " already registered\n";
    }
    return;
  }
  ClauseId id = d_nextId++;
  d_litToClauseId[satLit] = id;
  d_clauseIdToLit[id] = satLit;
  Assert(d_litToNode.find(satLit) != d_litToNode.end())
      << "NewProofManager::registerClause: literal " << satLit
      << " should have been defined.\n";
  Node litNode = d_litToNode[satLit];
  d_clauseIdToNode[id] = litNode;
  // register in proof as assumption, which should be filled later, since it's
  // not possible yet to know, in general, how this literal came to be. Some
  // components register facts eagerly, like the theory engine, but other
  // lazily, like CNF stream and internal SAT solver propagation.
  if (!d_cdproof.addStep(litNode, PfRule::ASSUME, {}, {litNode}))
  {
    Assert(false) << "NewProofManager::couldn't add " << PfRule::ASSUME
                  << " step with conclusion: " << litNode << "\n";
  }
  if (Debug.isOn("newproof::sat"))
  {
    Debug("newproof::sat") << "NewProofManager::registerClause: id " << id
                           << ", TLit: ";
    printLit(lit);
    Debug("newproof::sat") << "\n";
  }
}

void NewProofManager::registerClause(Minisat::Solver::TClause& clause)
{
  if (Debug.isOn("newproof::sat"))
  {
    Debug("newproof::sat") << "NewProofManager::registerClause: TClause: ";
    printClause(clause);
    Debug("newproof::sat") << "\n";
  }
  if (clause.proofId() != 0)
  {
    Assert(d_clauseIdToClause.find(clause.proofId())
           != d_clauseIdToClause.end());
    Debug("newproof::sat") << "NewProofManager::registerClause: id "
                           << clause.proofId()
                           << " of clause already registered\n";
    return;
  }
  ClauseId id = d_nextId++;
  clause.setProofId(id);
  d_clauseIdToClause[id] = &clause;
  // build clauseNode
  std::vector<Node> clauseNodes;
  for (unsigned i = 0, size = clause.size(); i < size; ++i)
  {
    prop::SatLiteral satLit = toSatLiteral<Minisat::Solver>(clause[i]);
    Assert(d_litToNode.find(satLit) != d_litToNode.end())
        << "NewProofManager::registerClause: literal " << satLit
        << " not defined yet\n";
    clauseNodes.push_back(d_litToNode[satLit]);
  }
  Node clauseNode = NodeManager::currentNM()->mkNode(kind::OR, clauseNodes);
  d_clauseIdToNode[id] = clauseNode;
  // register in proof as assumption, which should be filled later, since it's
  // not possible yet to know, in general, how this clause came to be. Some
  // components register facts eagerly, like the theory engine, but other
  // lazily, like CNF stream and internal SAT solver propagation.
  if (!d_cdproof.addStep(clauseNode, PfRule::ASSUME, {}, {clauseNode}))
  {
    Assert(false) << "NewProofManager::couldn't add " << PfRule::ASSUME
                  << " step with conclusion: " << clauseNode << "\n";
  }
  if (Debug.isOn("newproof::sat"))
  {
    Debug("newproof::sat") << "NewProofManager::registerClause: id " << id
                           << ", TClause: ";
    printClause(clause);
    Debug("newproof::sat") << ", clauseNode: " << clauseNode << "\n";
  }
}

void NewProofManager::startResChain(Minisat::Solver::TClause& start)
{
  Assert(start.proofId() != 0);
  ClauseId id = start.proofId();
  Debug("newproof::sat") << "NewProofManager::startResChain " << id << "\n";
  // TODO what should I add here? Who is "start"???
}

void NewProofManager::addResolutionStep(Minisat::Solver::TLit lit,
                                        Minisat::Solver::TClause& clause,
                                        bool sign)
{
  Assert(clause.proofId() != 0);
  Debug("newproof::sat") << "NewProofManager::addResolutionStep: ("
                         << clause.proofId() << ", ";
  printLit(lit);
  Debug("newproof::sat") << "\n";
  prop::SatLiteral satLit = toSatLiteral<Minisat::Solver>(lit);
  Assert(d_litToNode.find(satLit) != d_litToNode.end());
  d_resolution.push_back(
      Resolution(clause.proofId(), d_litToNode[satLit], sign));
}

void NewProofManager::endResChain(Minisat::Solver::TLit lit)
{
  prop::SatLiteral satLit = toSatLiteral<Minisat::Solver>(lit);
  Assert(d_litToClauseId.find(satLit) != d_litToClauseId.end());
  endResChain(d_litToClauseId[satLit]);
}

void NewProofManager::endResChain(Minisat::Solver::TClause& clause)
{
  Assert(clause.proofId() != 0);
  endResChain(clause.proofId());
}

// id is the conclusion
void NewProofManager::endResChain(ClauseId id)
{
  Debug("newproof::sat") << "NewProofManager::endResChain " << id << "\n";
  Assert(d_resolution.size() > 0);
  Debug("newproof::sat") << "========\n"
                         << "set .c" << id << "(resolution :clauses (";
  for (unsigned i = 0, size = d_resolution.size(); i < size; ++i)
  {
    Debug("newproof::sat") << ".c" << d_resolution[i].d_id;
    if (i < size - 1)
    {
      Debug("newproof::sat") << " ";
    }
  }
  Debug("newproof::sat") << "========\n";

  // saving for later printing
  d_resolutions.push_back(std::vector<Resolution>());
  d_resolutions.back().insert(
      d_resolutions.back().end(), d_resolution.begin(), d_resolution.end());
  // clearing
  d_resolution.clear();
}

ClauseId NewProofManager::justifyLit(Minisat::Solver::TLit lit)
{
  ClauseId id;
  Debug("newproof::sat") << "NewProofManager::justifyLit: lit: ";
  printLit(lit);
  prop::SatLiteral satLit = toSatLiteral<Minisat::Solver>(lit);
  Debug("newproof::sat") << "[" << d_litToNode[satLit] << "]\n";
  // see if already computed
  if (d_litToClauseId.find(satLit) != d_litToClauseId.end())
  {
    id = d_litToClauseId[satLit];
    Debug("newproof::sat") << "NewProofManager::justifyLit: already has id "
                           << id << "\n";
    return id;
  }
  Debug("newproof::sat")
      << "NewProofManager::justifyLit: computing justification...\n";
  Minisat::Solver::TCRef reason_ref = d_solver->reason(Minisat::var(lit));
  Assert(reason_ref != Minisat::Solver::TCRef_Undef);
  Assert(reason_ref >= 0 && reason_ref < d_solver->ca.size());
  // Here, the call to resolveUnit() can reallocate memory in the
  // clause allocator.  So reload reason ptr each time.
  const Minisat::Solver::TClause& initial_reason = d_solver->ca[reason_ref];
  unsigned current_reason_size = initial_reason.size();
  Debug("newproof::sat") << "NewProofManager::justifyLit: with clause: ";
  printClause(initial_reason);
  Debug("newproof::sat") << "\n";
  std::vector<Resolution> reason_resolutions;
  // add the reason clause first
  Assert(initial_reason.proofId() != 0);
  reason_resolutions.push_back(Resolution(initial_reason.proofId()));
  for (unsigned i = 0; i < current_reason_size; ++i)
  {
    const Minisat::Solver::TClause& current_reason = d_solver->ca[reason_ref];
    Assert(current_reason_size == static_cast<unsigned>(current_reason.size()));
    current_reason_size = current_reason.size();
    Minisat::Solver::TLit curr_lit = current_reason[i];
    // ignore the lit we are trying to justify...
    if (curr_lit == lit)
    {
      continue;
    }
    prop::SatLiteral curr_satLit = toSatLiteral<Minisat::Solver>(curr_lit);
    Assert(d_litToNode.find(curr_satLit) != d_litToNode.end());
    Resolution res(justifyLit(~curr_lit),
                   d_litToNode[curr_satLit],
                   Minisat::sign(curr_lit) ? 0 : 1);
    reason_resolutions.push_back(res);
  }
  // retrieve lit's node definition
  Assert(d_litToNode.find(satLit) != d_litToNode.end());
  Node litDef = d_litToNode[satLit];
  // TODO generate resolution step that allows the derivation of lit
  // via turning a resolution chain into a proof node
  d_litToClauseId[satLit] = id;
  d_clauseIdToLit[id] = satLit;
  return id;
}

void NewProofManager::finalizeProof(ClauseId conflict_id)
{
  std::vector<Resolution> reasons;
  reasons.push_back(Resolution(conflict_id));
  // retrive clause
  std::vector<Minisat::Solver::TLit> conflict_clause;
  auto it = d_clauseIdToClause.find(conflict_id);
  if (it != d_clauseIdToClause.end())
  {
    for (unsigned i = 0, size = it->second->size(); i < size; ++i)
    {
      conflict_clause.push_back((*it->second)[i]);
    }
  }
  else
  {
    Assert(d_clauseIdToLit.find(conflict_id) != d_clauseIdToLit.end());
    conflict_clause.push_back(
        prop::MinisatSatSolver::toMinisatLit(d_clauseIdToLit[conflict_id]));
  }
  Debug("newproof::sat") << "NewProofManager::finalizeProof: conflict_id: "
                         << conflict_id << "\n";
  // since this clause is conflicting, I must be able to resolve away each of
  // its literals l_1...l_n. Each literal ~l_i must be justifiable
  //
  // Either ~l_i is the conclusion of some previous, already built, step or from
  // a subproof to be computed.
  //
  // For each l_i, a resolution step is created with the id of the step allowing
  // the derivation of ~l_i, whose pivot in the conflict_clause will be l_i. All
  // resolution steps will be saved in the given reasons vector.
  for (unsigned i = 0, size = conflict_clause.size(); i < size; ++i)
  {
    prop::SatLiteral satLit = toSatLiteral<Minisat::Solver>(conflict_clause[i]);
    Assert(d_litToNode.find(satLit) != d_litToNode.end());
    Resolution res(justifyLit(~conflict_clause[i]),
                   d_litToNode[satLit],
                   Minisat::sign(conflict_clause[i]) ? 0 : 1);
    reasons.push_back(res);
  }
  if (d_format == options::ProofFormatMode::VERIT)
  {
    std::vector<unsigned> reason_ids;
    for (unsigned i = 0, size = reasons.size(); i < size; ++i)
    {
      reason_ids.push_back(reasons[i].d_id);
    }
    VeritProof* vtproof = static_cast<VeritProof*>(d_proof.get());
    vtproof->addProofStep(RULE_RESOLUTION, reason_ids, Node::null());
  }
  else if (d_format == options::ProofFormatMode::LEAN)
  {
    LeanProof* leanproof = static_cast<LeanProof*>(d_proof.get());
    leanproof->addResSteps(reasons, Node::null());
  }
}

// case in which I addded a false unit clause
void NewProofManager::finalizeProof(Minisat::Solver::TLit lit)
{
  prop::SatLiteral satLit = toSatLiteral<Minisat::Solver>(lit);
  Debug("newproof::sat")
      << "NewProofManager::finalizeProof: conflicting satLit: " << satLit
      << "\n";
  auto it = d_litToClauseId.find(satLit);
  if (it != d_litToClauseId.end())
  {
    // for whatever reason I may already have a clause id for it...
    finalizeProof(it->second);
    return;
  }
  // must come from input then
  Assert(d_litToNode.find(satLit) != d_litToNode.end());
  Node litDef = d_litToNode[satLit];
  Assert(d_assertionToClauseId.find(litDef) != d_assertionToClauseId.end());
  ClauseId id = d_assertionToClauseId[litDef];
  // since I'm here update this already
  d_litToClauseId[satLit] = id;
  d_clauseIdToLit[id] = satLit;
  finalizeProof(id);
}

void NewProofManager::finalizeProof()
{
  // last added clause is the conflicting one
  ClauseId conflict_id;
  if (d_format == options::ProofFormatMode::VERIT)
  {
    VeritProof* vtproof = static_cast<VeritProof*>(d_proof.get());
    conflict_id = vtproof->getId() - 1;
  }
  else if (d_format == options::ProofFormatMode::LEAN)
  {
    LeanProof* leanproof = static_cast<LeanProof*>(d_proof.get());
    conflict_id = leanproof->getId() - 1;
  }
  finalizeProof(conflict_id);
}

}  // namespace CVC4
