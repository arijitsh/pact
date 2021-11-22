/******************************************************************************
 * Top contributors (to current version):
 *   Hanna Lachnitt
 *
 * This file is part of the cvc5 project.
 *
 * Copyright (c) 2009-2021 by the authors listed in the file AUTHORS
 * in the top-level source directory and their institutional affiliations.
 * All rights reserved.  See the file COPYING in the top-level source
 * directory for licensing information.
 * ****************************************************************************
 *
 * The module for printing Alethe proof nodes.
 */

#include "proof/alethe/alethe_printer.h"

#include <iostream>
#include <unordered_map>

#include "proof/alethe/alethe_proof_rule.h"

namespace cvc5 {

namespace proof {

AletheProofPrinter::AletheProofPrinter()
{
  d_nested_level = 0;
  d_step_id = 1;
  d_prefix = "";
  d_assumptions.push_back({});
  d_steps.push_back({});
}

void AletheProofPrinter::print(std::ostream& out,
                               std::shared_ptr<ProofNode> pfn)
{
  Trace("alethe-printer") << "- Print proof in Alethe format. " << std::endl;
  const std::vector<Node>& args = pfn->getArguments();
  // Special handling for the first scope
  // Print assumptions and add them to the list but do not print anchor.
  for (size_t i = 3, size = args.size(); i < size; i++)
  {
    Trace("alethe-printer")
        << "... print assumption " << args[i] << std::endl;
    out << "(assume a" << i - 3 << " " << args[i] << ")\n";
    d_assumptions[0][args[i]] = i - 3;
  }

  // Then, print the rest of the proof node
  printInternal(out, pfn->getChildren()[0]);
}

std::string AletheProofPrinter::printInternal(
    std::ostream& out, std::shared_ptr<ProofNode> pfn)
{
  // Store current id in case a subproof overwrites step_id
  int current_step_id = d_step_id;

  // If the proof node is untranslated a problem might have occured during
  // postprocessing
  if (pfn->getArguments().size() < 3 || pfn->getRule() != PfRule::ALETHE_RULE)
  {
    Trace("alethe-printer")
        << "... printing failed! Encountered untranslated Node. "
        << pfn->getResult() << " " << toString(pfn->getRule()) << " "
        << " / " << pfn->getArguments() << std::endl;
    return "";
  }

  // Get the alethe proof rule
  AletheRule vrule =
      static_cast<AletheRule>(std::stoul(pfn->getArguments()[0].toString()));

  // In case the rule is an anchor it is printed before its children.
  if (vrule == AletheRule::ANCHOR_SUBPROOF || vrule == AletheRule::ANCHOR_BIND)
  {
    // Look up if subproof has already been printed
    auto it = d_steps[d_nested_level].find(pfn->getArguments()[2]);
    if (it != d_steps[d_nested_level].end())
    {
      Trace("alethe-printer")
          << "... subproof is already printed " << pfn->getResult() << " "
          << vrule << " / " << pfn->getArguments() << std::endl;
      return d_prefix + "t" + std::to_string(it->second);
    }

    // If not printed before, enter next level
    d_nested_level++;
    d_assumptions.push_back({});
    d_steps.push_back({});

    // Print anchor
    Trace("alethe-printer")
        << "... print anchor " << pfn->getResult() << " " << vrule << " "
        << " / " << pfn->getArguments() << std::endl;
    out << "(anchor :step " << d_prefix << "t" << d_step_id;

    // Append index of anchor to prefix so that all steps in the subproof use it
    d_prefix.append("t" + std::to_string(d_step_id) + ".");
    d_step_id++;

    // If the subproof is a bind the arguments need to be printed as
    // assignments, i.e. args=[(= v0 v1)] is printed as (:= (v0 Int) v1).
    if (vrule == AletheRule::ANCHOR_BIND)
    {
      out << " :args (";
      for (unsigned long int j = 3, size = pfn->getArguments().size(); j < size;
           j++)
      {
        out << "(:= (" << pfn->getArguments()[j][0].toString() << " "
            << pfn->getArguments()[j][0].getType().toString() << ") "
            << pfn->getArguments()[j][1].toString() << ")";
        if (j != pfn->getArguments().size() - 1)
        {
          out << " ";
        }
      }
      out << ")";
    }
    // In all other cases there are no arguments
    out << ")\n";

    // If the subproof is a genuine subproof the arguments are printed as
    // assumptions
    if (vrule == AletheRule::ANCHOR_SUBPROOF)
    {
      for (size_t i = 3, size = pfn->getArguments().size(); i < size; i++)
      {
        Trace("alethe-printer")
            << "... print assumption " << pfn->getArguments()[i] << std::endl;
        out << "(assume " << d_prefix << "a" << std::to_string(i - 3) << " "
            << pfn->getArguments()[i] << ")\n";
        d_assumptions[d_nested_level][pfn->getArguments()[i]] = i - 3;
      }
    }

    // Store step_id until children are printed to resume counter at current
    // position
    current_step_id = d_step_id;
    d_step_id = 1;
  }

  // Assumptions are printed at the anchor and therefore have to be in the list
  // of assumptions when an assume is reached.
  if (vrule == AletheRule::ASSUME)
  {
    Trace("alethe-printer")
        << "... reached assumption " << pfn->getResult() << " " << vrule << " "
        << " / " << pfn->getArguments() << " " << d_nested_level << std::endl;

    // While in most cases the assumption is printed at the same level than the
    // step whose premise it is, it is possible that it is from a different
    // level. Thus, the whole list needs to be traversed. Since this case is
    // rare adapting the prefix should be rarely necessary.
    for (size_t i = d_nested_level; i >= 0; i--)
    {
      // This could just be pfn->getResult() since Assumptions are not changed
      // when printed. However, in case this ever changes this uses the 2nd
      // argument
      auto it = d_assumptions[i].find(pfn->getArguments()[2]);
      if (it != d_assumptions[i].end())
      {
        std::string new_prefix = d_prefix;
        // get substring of prefix
        for (size_t j = 0; j < d_nested_level - i; j++)
        {
          new_prefix = new_prefix.substr(0, new_prefix.find_last_of("."));
          new_prefix = new_prefix.substr(0, new_prefix.find_last_of(".") + 1);
        }
        Trace("alethe-printer")
            << "... found assumption in list on level " << i << ": "
            << pfn->getArguments()[2] << "/" << d_assumptions[i] << "     "
            << new_prefix << std::endl;
        return new_prefix + "a" + std::to_string(it->second);
      }
    }

    Trace("alethe-printer") << "... printing failed! Encountered assumption "
                               "that has not been printed! "
                            << pfn->getArguments()[2] << "/"
                            << d_assumptions[d_nested_level] << std::endl;
    return "";
  }

  // Print children
  std::vector<std::string> child_prefixes;
  for (const std::shared_ptr<ProofNode> child : pfn->getChildren())
  {
    child_prefixes.push_back(printInternal(out, child));
  }

  // If the rule is a subproof a final subproof step needs to be printed
  if (vrule == AletheRule::ANCHOR_SUBPROOF || vrule == AletheRule::ANCHOR_BIND)
  {
    Trace("alethe-printer")
        << "... print node " << pfn->getResult() << " " << vrule << " / "
        << pfn->getArguments() << std::endl;

    d_prefix.pop_back();  // Remove last .
    // print subproof or bind
    out << "(step " << d_prefix << " " << pfn->getArguments()[2] << " :rule "
        << vrule;

    // Discharge assumptions in the case of subproof
    if (vrule == AletheRule::ANCHOR_SUBPROOF)
    {
      out << " :discharge (";
      for (unsigned long int j = 0; j < d_assumptions[d_nested_level].size(); j++)
      {
        out << d_prefix << ".a" + std::to_string(j);
        if (j != d_assumptions[d_nested_level].size() - 1)
        {
          out << " ";
        }
      }
      out << ")";
    }
    out << ")\n";

    // Set counters back to their old value before subproof was entered
    d_nested_level--;
    d_assumptions.pop_back();
    d_steps.pop_back();
    d_step_id = current_step_id;
    std::string current_t = d_prefix;
    d_prefix = d_prefix.substr(0, d_prefix.find_last_of("t"));
    return current_t;
  }

  // If the current step is already printed return its id
  auto it = d_steps[d_nested_level].find(pfn->getArguments()[2]);

  if (it != d_steps[d_nested_level].end())
  {
    Trace("alethe-printer")
        << "... step is already printed " << pfn->getResult() << " " << vrule
        << " / " << pfn->getArguments() << std::endl;
    return d_prefix + "t" + std::to_string(it->second);
  }

  // Print current step
  Trace("alethe-printer") << "... print node " << pfn->getResult() << " "
                          << vrule << " / " << pfn->getArguments() << std::endl;
  std::string current_t;
  current_t = "t" + std::to_string(d_step_id);
  d_steps[d_nested_level][pfn->getArguments()[2]] = d_step_id;
  out << "(step " << d_prefix << current_t << " ";
  out << pfn->getArguments()[2].toString() << " :rule " << vrule;
  if (pfn->getArguments().size() > 3)
  {
    out << " :args (";
    for (unsigned long int i = 3, size = pfn->getArguments().size(); i < size;
         i++)
    {
      if (vrule == AletheRule::FORALL_INST)
      {
        out << "(:= " << pfn->getArguments()[i][0].toString() << " "
            << pfn->getArguments()[i][1].toString() << ")";
      }
      else
      {
        out << pfn->getArguments()[i].toString();
      }
      if (i != pfn->getArguments().size() - 1)
      {
        out << " ";
      }
    }
    out << ")";
  }
  if (pfn->getChildren().size() >= 1)
  {
    out << " :premises (";
    for (unsigned long int i = 0, size = child_prefixes.size(); i < size; i++)
    {
      out << child_prefixes[i];
      if (i != child_prefixes.size() - 1)
      {
        out << " ";
      }
    }
    out << "))\n";
  }
  else
  {
    out << ")\n";
  }
  ++d_step_id;
  return d_prefix + current_t;
}

}  // namespace proof

}  // namespace cvc5
