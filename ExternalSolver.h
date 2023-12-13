#ifndef EXTERNAL_SOLVER_H
#define EXTERNAL_SOLVER_H

#include <string>
#include "SatSolver.h"

/*
Class for all kinds of pre-compiled SAT solvers, e.g. cadical, cryptominisat5
SAT calls are answered by opening a pipe to an instance of the external solver with pstream
TODO some bug in pstream
*/
class ExternalSatSolver {
public:
    int solve(SATSolver_t *solver);
};

#endif
