//#include <stdio.h>
//#include <stdint.h>
//#include <stdbool.h>
#include "Encodings.h"

static int64_t get_accepted_variable(activeArgs_t *activeArgs, uint32_t argument)
{
	return (int64_t) 0 + activeArgs->matrix->content[argument][2];
}

static int64_t get_rejected_variable(activeArgs_t *activeArgs, uint32_t argument)
{
	return get_accepted_variable(activeArgs, argument) + activeArgs->encodingToArgument->length - 1;
}

void add_rejected_clauses(SATSolver_t *solver, argFramework_t *framework, activeArgs_t *activeArgs, uint32_t argument)
{
	// basic acceptance and rejection clause
	//Part I:  models that an argument cannot be accepted and rejected at the same time
	//create disjunction
	nodeInt64_t *non_simultaneity_clause = create_list_int64(-1 * get_rejected_variable(activeArgs, argument));
	push_int64(non_simultaneity_clause, -1 * get_accepted_variable(activeArgs, argument));
	add_clause(solver, non_simultaneity_clause);

	//Part II: ensures that if an attacker 'b' of an argument 'a' is accepted, then 'a' must be rejected
	//iterate through all active attackers
	uint32_t currentAttacker = 0;
	while(has_next_in_row(framework->attackers, argument, currentAttacker)) 
	{
		currentAttacker = get_next_in_row(framework->attackers, argument, currentAttacker);
		if (is_active(activeArgs, currentAttacker))
		{
			//create disjunction
			nodeInt64_t *non_simultaneity_with_attacker_clause = create_list_int64(get_rejected_variable(activeArgs, argument));
			push_int64(non_simultaneity_with_attacker_clause, -1 * get_accepted_variable(activeArgs, currentAttacker));
			add_clause(solver, non_simultaneity_with_attacker_clause);
		}
	}

	//Part III: constitutes that if an argument 'a' is rejected, one of its attackers must be accepted
	//create disjunction
	nodeInt64_t *rejection_reason_clause = create_list_int64(-1 * get_rejected_variable(activeArgs, argument));
	//iterate through all active attackers
	currentAttacker = 0;
	while (has_next_in_row(framework->attackers, argument, currentAttacker))
	{
		currentAttacker = get_next_in_row(framework->attackers, argument, currentAttacker);
		if (is_active(activeArgs, currentAttacker))
		{
			push_int64(rejection_reason_clause, get_accepted_variable(activeArgs, currentAttacker));
		}
	}
	add_clause(solver, rejection_reason_clause);
}

void add_rejected_clauses_per_attacker(SATSolver_t *solver, argFramework_t *framework, activeArgs_t *activeArgs, uint32_t argument, uint32_t attacker, nodeInt64_t *rejection_reason_clause)
{
	nodeInt64_t *non_simultaneity_with_attacker_clause = create_list_int64(get_rejected_variable(activeArgs, argument));
	push_int64(non_simultaneity_with_attacker_clause, -1 * get_accepted_variable(activeArgs, attacker));
	add_clause(solver, non_simultaneity_with_attacker_clause);

	push_int64(rejection_reason_clause, get_accepted_variable(activeArgs, attacker));
}

void extend_nonempty(activeArgs_t *activeArgs, uint32_t argument, nodeInt64_t *existingClause)
{
	//models the nonemptiness of initial sets, by extending a disjunction demanding that at least one argument has to be accepted
	//extend disjunction
	push_int64(existingClause, get_accepted_variable(activeArgs, argument));
}

void add_conflict_free_per_attacker(SATSolver_t *solver, activeArgs_t *activeArgs, uint32_t argument, uint32_t attacker)
{
	//create disjunction
	nodeInt64_t *conflictfree_clause = create_list_int64(-1 * get_accepted_variable(activeArgs, argument));
	if (argument != attacker)
	{
		//is not a self-attack
		push_int64(conflictfree_clause, -1 * get_accepted_variable(activeArgs, attacker));
	}
	add_clause(solver, conflictfree_clause);
}

void add_conflict_free(SATSolver_t *solver, argFramework_t *framework, activeArgs_t *activeArgs, uint32_t argument)
{
	// for every pair of arguments, if there is an attack between them, then one of these arguments has to be not accepted

	//iterate through all active attackers
	uint32_t currentAttacker = 0;
	while (has_next_in_row(framework->attackers, argument, currentAttacker))
	{
		currentAttacker = get_next_in_row(framework->attackers, argument, currentAttacker);
		if (is_active(activeArgs, currentAttacker))
		{
			add_conflict_free_per_attacker(solver, activeArgs, argument, currentAttacker);
		}
	}
}

void add_admissible(SATSolver_t *solver, argFramework_t *framework, activeArgs_t *activeArgs, uint32_t argument)
{
	add_rejected_clauses(solver, framework, activeArgs, argument);
	add_conflict_free(solver, framework, activeArgs, argument);

	//models the notion of defense in an abstract argumentation framework: 
	// if an argument is accepted to be in the admissible set, all its attackers must be rejected

	//iterate through all active attackers
	uint32_t currentAttacker = 0;
	while (has_next_in_row(framework->attackers, argument, currentAttacker))
	{
		currentAttacker = get_next_in_row(framework->attackers, argument, currentAttacker);
		if (is_active(activeArgs, currentAttacker))
		{
			if (argument == currentAttacker)
			{
				continue;
			}

			//create disjunction
			nodeInt64_t *defense_clause = create_list_int64(-1 * get_accepted_variable(activeArgs, argument));
			//is not a self-attack
			push_int64(defense_clause, get_rejected_variable(activeArgs, currentAttacker));
			add_clause(solver, defense_clause);
		}
	}
}

void add_clauses_IS(SATSolver_t *solver, argFramework_t *framework, activeArgs_t *activeArgs)
{
	uint32_t currentArgument = get_first_active(activeArgs);
	if (currentArgument == 0)
	{
		return;
	}

	nodeInt64_t *non_empty_clause = create_list_int64(get_accepted_variable(activeArgs, currentArgument));
	add_admissible(solver, framework, activeArgs, currentArgument);

	while (has_next_active(activeArgs, currentArgument))
	{
		currentArgument = get_next_active(activeArgs, currentArgument);
		add_admissible(solver, framework, activeArgs, currentArgument);
		extend_nonempty(activeArgs, currentArgument, non_empty_clause);
	}

	add_clause(solver, non_empty_clause);
}


//========================================== OPTIMIZATION ================================================================================

//nodeInt64_t* add_rejected_clauses(SATSolver_t *solver, argFramework_t *framework, activeArgs_t *activeArgs, uint32_t argument)
//{
//	// basic acceptance and rejection clause
//	//Part I:  models that an argument cannot be accepted and rejected at the same time
//	//create disjunction
//	nodeInt64_t *non_simultaneity_clause = create_list_int64(-1 * get_rejected_variable(activeArgs, argument));
//	push_int64(non_simultaneity_clause, -1 * get_accepted_variable(activeArgs, argument));
//	add_clause(solver, non_simultaneity_clause);
//
//	//Part III: constitutes that if an argument 'a' is rejected, one of its attackers must be accepted
//	//create disjunction
//	nodeInt64_t *rejection_reason_clause = create_list_int64(-1 * get_rejected_variable(activeArgs, argument));
//	add_clause(solver, rejection_reason_clause);
//
//	return rejection_reason_clause;
//}
//
//void add_rejected_clauses_per_attacker(SATSolver_t *solver, activeArgs_t *activeArgs, uint32_t argument, uint32_t attacker, nodeInt64_t *rejection_reason_clause)
//{
//	//Part II: ensures that if an attacker 'b' of an argument 'a' is accepted, then 'a' must be rejected
//	//iterate through all active attackers
//	nodeInt64_t *non_simultaneity_with_attacker_clause = create_list_int64(get_rejected_variable(activeArgs, argument));
//	push_int64(non_simultaneity_with_attacker_clause, -1 * get_accepted_variable(activeArgs, attacker));
//	add_clause(solver, non_simultaneity_with_attacker_clause);
//
//	//Part III: constitutes that if an argument 'a' is rejected, one of its attackers must be accepted
//	//create disjunction
//	push_int64(rejection_reason_clause, get_accepted_variable(activeArgs, attacker));
//}
//
//void add_conflict_free_per_attacker(SATSolver_t *solver, activeArgs_t *activeArgs, uint32_t argument, uint32_t attacker)
//{
//	//create disjunction
//	nodeInt64_t *conflictfree_clause = create_list_int64(-1 * get_accepted_variable(activeArgs, argument));
//	if (argument != attacker)
//	{
//		//is not a self-attack
//		push_int64(conflictfree_clause, -1 * get_accepted_variable(activeArgs, attacker));
//	}
//	add_clause(solver, conflictfree_clause);
//}
//
//void add_admissible_per_attacker(SATSolver_t *solver, activeArgs_t *activeArgs, uint32_t argument, uint32_t attacker)
//{
//	if (argument == attacker)
//	{
//		return;
//	}
//
//	//create disjunction
//	nodeInt64_t *defense_clause = create_list_int64(-1 * get_accepted_variable(activeArgs, argument));
//	//is not a self-attack
//	push_int64(defense_clause, get_rejected_variable(activeArgs, attacker));
//	add_clause(solver, defense_clause);
//}
//
//void add_admissible(SATSolver_t *solver, argFramework_t *framework, activeArgs_t *activeArgs, uint32_t argument)
//{
//	nodeInt64_t *rejection_reason_clause = add_rejected_clauses(solver, framework, activeArgs, argument);
//
//	//models the notion of defense in an abstract argumentation framework: 
//	// if an argument is accepted to be in the admissible set, all its attackers must be rejected
//
//	//iterate through all active attackers
//	uint32_t current_attacker = 0;
//	while (has_next_in_row(framework->attackers, argument, current_attacker))
//	{
//		current_attacker = get_next_in_row(framework->attackers, argument, current_attacker);
//		if (is_active(activeArgs, current_attacker))
//		{
//			add_rejected_clauses_per_attacker(solver, activeArgs, argument, current_attacker, rejection_reason_clause);
//			add_conflict_free_per_attacker(solver, activeArgs, argument, current_attacker);
//			add_admissible_per_attacker(solver, activeArgs, argument, current_attacker);
//		}
//	}
//}