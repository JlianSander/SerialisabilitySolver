
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "List.h"
#include "ExternalSatSolver.h"

void assume(SATSolver_t *solver, uint32_t literal)
{
	push(solver->assumptions, literal);
}

void addClause(SATSolver_t *solver, nodeInt_t *clause)
{
	pushList(solver->clauses, clause);
}

void addMinimizationClause(SATSolver_t *solver, nodeInt_t *clause)
{
	pushList(solver->minimizationClauses, clause);
}

void free(SATSolver_t *solver)
{
	freeList(solver->model);
	freeListOfList(solver->clauses);
	freeListOfList(solver->minimizationClauses);
	freeList(solver->assumptions);
}