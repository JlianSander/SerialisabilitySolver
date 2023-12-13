#ifndef SAT_SOLVER_H
#define SAT_SOLVER_H


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "List.h"

///<summary>
/// Data model of the clauses used by the solver for calculation.
///</summary>
typedef struct SATSolver {
    nodeInt64_t *model;
    listInt64_t *clauses;
    listInt64_t *minimizationClauses;
    nodeInt64_t *assumptions;
} SATSolver_t;


void assume(SATSolver_t *solver, int64_t literal);
void add_clause(SATSolver_t *solver, nodeInt64_t *clause);
void add_minimization_clause(SATSolver_t *solver, nodeInt64_t *clause);
SATSolver_t* create_solver();
void free_solver(SATSolver_t *solver);
int solve(SATSolver_t *solver);
int solve_with_assumptions(SATSolver_t *solver, nodeInt64_t *assumptions);

#endif