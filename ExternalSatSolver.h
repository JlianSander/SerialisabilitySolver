#ifndef EXTERNAL_SAT_SOLVER_H
#define EXTERNAL_SAT_SOLVER_H


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "List.h"

///<summary>
/// Data model of the clauses used by the solver for calculation.
///</summary>
typedef struct SATSolver {
    nodeInt_t *model;
    listInt_t *clauses;
    listInt_t *minimizationClauses;
    nodeInt_t *assumptions;
} SATSolver_t;


void assume(SATSolver_t *solver, uint32_t literal);
void add_clause(SATSolver_t *solver, nodeInt_t *clause);
void add_minimization_clause(SATSolver_t *solver, nodeInt_t *clause);
int solve(SATSolver_t *solver);
int solve_with_assumptions(SATSolver_t *solver, nodeInt_t *assumptions);
void free_solver(SATSolver_t *solver);

#endif