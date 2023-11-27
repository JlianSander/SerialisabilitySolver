#ifndef EXTERNAL_SAT_SOLVER_H
#define EXTERNAL_SAT_SOLVER_H


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "List.h"

///<summary>
/// Data model of the clauses used by the solver for calculation.
///</summary>
typedef struct SATSolverInfo {
    listInt_t *clauses;
    listInt_t *minimizationClauses;
    nodeInt_t *assumptions;
} SATSolverInfo_t;


void assume(SATSolverInfo *solver, int literal);
void addClause(SATSolverInfo *solver, nodeInt_t *clause);
void addMinimizationClause(SATSolverInfo *solver, nodeInt_t *clause);
int solve();
int solve(nodeInt_t *assumptions);
void free();

#endif