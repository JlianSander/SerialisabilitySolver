//#include <stdio.h>
//#include <stdint.h>
//#include <stdbool.h>
#include "Encodings.h"


uint32_t get_rejected_variable(uint32_t numberArguments, uint32_t argument)
{
	return numberArguments + argument;
}

void add_rejected_clauses(SATSolver_t *solver, argFramework_t framework, matrix_t activeArgs, uint32_t argument)
{
	/*nodeInt_t *non_simultaneity_clause = create_list(get_rejected_variable());
	push(non_simultaneity_clause, -argument*/


	/*for (uint32_t i = 0; i < af.args; i++) {
		vector<int> additional_clause = { -af.rejected_var[i], -af.accepted_var[i] };
		solver.addClause(additional_clause);
		for (uint32_t j = 0; j < af.attackers[i].size(); j++) {
			vector<int> clause = { af.rejected_var[i], -af.accepted_var[af.attackers[i][j]] };
			solver.addClause(clause);
		}
		vector<int> clause(af.attackers[i].size() + 1);
		for (uint32_t j = 0; j < af.attackers[i].size(); j++) {
			clause[j] = af.accepted_var[af.attackers[i][j]];
		}
		clause[af.attackers[i].size()] = -af.rejected_var[i];
		solver.addClause(clause);
	}*/
}