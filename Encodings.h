#ifndef ENCODINGS_H
#define ENCODINGS_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "AF.h"
#include "Actives.h"
#include "ExternalSatSolver.h"

uint32_t get_rejected_variable(uint32_t numberArguments, uint32_t argument);

void add_rejected_clauses(SATSolver_t *solver, argFramework_t framework, matrix_t activeArgs, uint32_t argument);
void add_nonempty(SATSolver_t *solver, argFramework_t framework, matrix_t activeArgs, uint32_t argument, nodeInt_t *existingClause); //extends existing clause to realize OR
void add_conflict_free(SATSolver_t *solver, argFramework_t framework, matrix_t activeArgs, uint32_t argument);
void add_admissible(SATSolver_t *solver, argFramework_t framework, matrix_t activeArgs, uint32_t argument);
void add_complete(SATSolver_t *solver, argFramework_t framework, matrix_t activeArgs, uint32_t argument);
void add_clauses_IS(SATSolver_t *solver, argFramework_t framework, matrix_t activeArgs);

#endif
