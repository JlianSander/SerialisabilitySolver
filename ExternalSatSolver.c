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

SATSolver_t* create_solver()
{
	SATSolver_t *solver = NULL;
	solver = malloc(sizeof *solver);
	if (solver == NULL)
	{
		printf("Memory allocation failed\n");
		exit(1);
	}else 
	{
		solver->assumptions = create_list_int64(0);
		solver->clauses = create_list_list_int64(create_list_int64(0));
		solver->minimizationClauses = create_list_list_int64(create_list_int64(0));
		solver->model = create_list_int64(0);
		return solver;
	}
}

void free_solver(SATSolver_t *solver)
{
	free_list_int64(solver->model);
	free_list_list_int64(solver->clauses);
	free_list_list_int64(solver->minimizationClauses);
	free_list_int64(solver->assumptions);
	free(solver);
}