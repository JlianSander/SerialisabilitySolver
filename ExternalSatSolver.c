
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

void add_clause(SATSolver_t *solver, nodeInt_t *clause)
{
	push_list(solver->clauses, clause);
}

void add_minimization_clause(SATSolver_t *solver, nodeInt_t *clause)
{
	push_list(solver->minimizationClauses, clause);
}

void free_solver(SATSolver_t *solver)
{
	free_list(solver->model);
	free_list_of_list(solver->clauses);
	free_list_of_list(solver->minimizationClauses);
	free_list(solver->assumptions);
}