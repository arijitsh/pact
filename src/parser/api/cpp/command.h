/******************************************************************************
 * Top contributors (to current version):
 *   Mathias Preiner, Andrew Reynolds, Tim King
 *
 * This file is part of the cvc5 project.
 *
 * Copyright (c) 2009-2023 by the authors listed in the file AUTHORS
 * in the top-level source directory and their institutional affiliations.
 * All rights reserved.  See the file COPYING in the top-level source
 * directory for licensing information.
 * ****************************************************************************
 *
 * Implementation of the command pattern on SolverEngines.
 *
 * Command objects are generated by the parser (typically) to implement the
 * commands in parsed input (see Parser::parseNextCommand()), or by client
 * code.
 */

#include "cvc5_public.h"

#ifndef CVC5__PARSER__API__CPP__COMMAND_H
#define CVC5__PARSER__API__CPP__COMMAND_H

#include <cvc5/cvc5.h>
#include <cvc5/cvc5_export.h>

#include <iosfwd>
#include <sstream>
#include <string>
#include <vector>

#include "options/language.h"

namespace cvc5 {

namespace main {
class CommandExecutor;
}

namespace parser {

class CommandStatus;
class SymbolManager;

class CVC5_EXPORT Command
{
  friend class main::CommandExecutor;

 public:
  Command();
  Command(const Command& cmd);

  virtual ~Command();

  /**
   * Invoke the command on the solver and symbol manager sm.
   */
  virtual void invoke(cvc5::Solver* solver, parser::SymbolManager* sm) = 0;
  /**
   * Same as above, and prints the result to output stream out.
   */
  virtual void invoke(cvc5::Solver* solver,
                      parser::SymbolManager* sm,
                      std::ostream& out);

  virtual void toStream(std::ostream& out) const = 0;

  std::string toString() const;

  virtual std::string getCommandName() const = 0;

  /**
   * Either the command hasn't run yet, or it completed successfully
   * (CommandSuccess, not CommandUnsupported or CommandFailure).
   */
  bool ok() const;

  /**
   * The command completed in a failure state (CommandFailure, not
   * CommandSuccess or CommandUnsupported).
   */
  bool fail() const;

  /**
   * The command was ran but was interrupted due to resource limiting.
   */
  bool interrupted() const;

 protected:
  /**
   * This field contains a command status if the command has been
   * invoked, or NULL if it has not.  This field is either a
   * dynamically-allocated pointer, or it's a pointer to the singleton
   * CommandSuccess instance.  Doing so is somewhat asymmetric, but
   * it avoids the need to dynamically allocate memory in the common
   * case of a successful command.
   */
  const CommandStatus* d_commandStatus;
  /**
   * Print the result of running the command. This method is only called if the
   * command ran successfully.
   */
  virtual void printResult(cvc5::Solver* solver, std::ostream& out) const;
  /**
   * Reset the given solver in-place (keep the object at the same memory
   * location).
   */
  static void resetSolver(cvc5::Solver* solver);

  // These methods rely on Command being a friend of classes in the API.
  // Subclasses of command should use these methods for conversions,
  // which is currently necessary for e.g. printing commands.
  /** Helper to convert a Term to an internal internal::Node */
  static internal::Node termToNode(const cvc5::Term& term);
  /** Helper to convert a vector of Terms to internal Nodes. */
  static std::vector<internal::Node> termVectorToNodes(
      const std::vector<cvc5::Term>& terms);
  /** Helper to convert a Sort to an internal internal::TypeNode */
  static internal::TypeNode sortToTypeNode(const cvc5::Sort& sort);
  /** Helper to convert a vector of Sorts to internal TypeNodes. */
  static std::vector<internal::TypeNode> sortVectorToTypeNodes(
      const std::vector<cvc5::Sort>& sorts);
  /** Helper to convert a Grammar to an internal internal::TypeNode */
  static internal::TypeNode grammarToTypeNode(cvc5::Grammar* grammar);
}; /* class Command */

std::ostream& operator<<(std::ostream&, const Command&) CVC5_EXPORT;
std::ostream& operator<<(std::ostream&, const Command*) CVC5_EXPORT;

}  // namespace parser
}  // namespace cvc5

#endif /* CVC5__PARSER__COMMAND_H */
