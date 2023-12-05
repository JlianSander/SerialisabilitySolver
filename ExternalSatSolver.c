//#include <stdio.h>
//#include <stdint.h>
//#include <stdbool.h>
//#include <string.h>
//#include "List.h"
#include "ExternalSatSolver.h"

void assume(SATSolver_t *solver, int64_t literal)
{
	push_int64(solver->assumptions, literal);
}

void add_clause(SATSolver_t *solver, nodeInt64_t *clause)
{
	push_list_int64(solver->clauses, clause);
}

void add_minimization_clause(SATSolver_t *solver, nodeInt64_t *clause)
{
	push_list_int64(solver->minimizationClauses, clause);
}

void free_solver(SATSolver_t *solver)
{
	free_list_int64(solver->model);
	free_list_list_int64(solver->clauses);
	free_list_list_int64(solver->minimizationClauses);
	free_list_int64(solver->assumptions);
}