//#include <stdio.h>
//#include <stdint.h>
//#include <stdbool.h>
//#include <string.h>
//#include "List.h"
#include "SatSolver.h"

void assume(SATSolver_t *solver, int64_t literal)
{
	if (solver->assumptions == NULL)
	{
		solver->assumptions = create_list_int64(literal);
	}
	else
	{
		push_int64(solver->assumptions, literal);
	}
}

void add_clause(SATSolver_t *solver, nodeInt64_t *clause)
{
	if (solver->clauses == NULL)
	{
		solver->clauses = create_list_list_int64(clause);
	}
	else
	{
		push_list_int64(solver->clauses, clause);
	}

	push_int64(clause, 0);
}

void add_minimization_clause(SATSolver_t *solver, nodeInt64_t *clause)
{
	if (solver->minimizationClauses == NULL)
	{
		solver->minimizationClauses = create_list_list_int64(clause);
	}
	else
	{
		push_list_int64(solver->minimizationClauses, clause);
	}

	push_int64(clause, 0);
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
		solver->assumptions = NULL;
		solver->clauses = NULL;
		solver->minimizationClauses = NULL;
		solver->model = NULL;
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

int solve(SATSolver_t *solver)
{

}

int solve_with_assumptions(SATSolver_t *solver, nodeInt64_t *assumptions)
{
	nodeInt64_t *current = assumptions;
	while (current != NULL)
	{
		assume(solver, current->number);
		current = current->next;
	}

	solve(solver);
}