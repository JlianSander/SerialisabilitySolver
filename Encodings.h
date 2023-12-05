#ifndef ENCODINGS_H
#define ENCODINGS_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "AF.h"
#include "Actives.h"
#include "ExternalSatSolver.h"


/// <summary>
/// Adds clauses for the basic acceptance and rejection of a specified argument through the attacks in the specified framework to a specified solver.
/// </summary>
/// <param name="solver">The solver, to whom the clauses will be added.</param>
/// <param name="framework">The abstract argumentation framework, based upon which the attacks are analysed.</param>
/// <param name="activeArgs">The set of active arguments, in the current state of the framework.</param>
/// <param name="argument">The argument, for which the clauses shall be defined.</param>
void add_rejected_clauses(SATSolver_t *solver, argFramework_t *framework, activeArgs_t *activeArgs, uint32_t argument);
/// <summary>
/// Adds clauses to ensure that the set of arguments, found by the specified solver, is free of any conflicts in which the specified argument is involved.
/// </summary>
/// <param name="solver">The solver, to whom the clauses will be added.</param>
/// <param name="framework">The abstract argumentation framework, based upon which the attacks are analysed.</param>
/// <param name="activeArgs">The set of active arguments, in the current state of the framework.</param>
/// <param name="argument">The argument, for which the clauses shall be defined.</param>
void add_conflict_free(SATSolver_t *solver, argFramework_t *framework, activeArgs_t *activeArgs, uint32_t argument);
/// <summary>
/// Adds clauses to encode an admissible set of arguments, including the notion of defense.
/// </summary>
/// <param name="solver">The solver, to whom the clauses will be added.</param>
/// <param name="framework">The abstract argumentation framework, based upon which the attacks are analysed.</param>
/// <param name="activeArgs">The set of active arguments, in the current state of the framework.</param>
/// <param name="argument">The argument, for which the clauses shall be defined.</param>
void add_admissible(SATSolver_t *solver, argFramework_t *framework, activeArgs_t *activeArgs, uint32_t argument);
void add_complete(SATSolver_t *solver, argFramework_t *framework, activeArgs_t *activeArgs, uint32_t argument);
/// <summary>
/// Adds all clauses necessary to encode an initial set.
/// </summary>
/// <param name="solver">The solver, to whom the clauses will be added.</param>
/// <param name="framework">The abstract argumentation framework, based upon which the attacks are analysed.</param>
/// <param name="activeArgs">The set of active arguments, in the current state of the framework.</param>
void add_clauses_IS(SATSolver_t *solver, argFramework_t *framework, activeArgs_t *activeArgs);
/// <summary>
/// Extends a specified clause to ensure the nonemptyness of any set of arguments found by a SATsolver, 
/// by the part of the clause which is based on the specified argument.
/// </summary>
/// <param name="activeArgs">The set of active arguments, in the current state of the framework.</param>
/// <param name="argument">The argument, for which the clause shall be extended.</param>
/// <param name="existingClause">The clause, representing a disjunction of literals about other arguments.</param>
void extend_nonempty(activeArgs_t *activeArgs, uint32_t argument, nodeInt64_t *existingClause);

#endif
