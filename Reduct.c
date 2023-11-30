#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "AF.h"
#include "Reduct.h"
#include "List.h"
#include "Matrix.h"
#include "Actives.h"
#include "LinkedSparseMatrix.h"

matrix_t* getReduct(matrix_t* activeArguments, argFramework_t* framework, uint32_t argument)
{
	matrix_t *newActives = copyMatrix(activeArguments);
	deactivateArgument(newActives, argument);
	uint32_t currentVictim = 0;
	if (!hasNextInRow(framework->victims, argument, currentVictim)){
		return newActives;
	}

	do {
		currentVictim = getNextInRow(framework->victims, argument, currentVictim);
		if (isActive(newActives, currentVictim)){
			deactivateArgument(newActives, currentVictim);
		}
	} while (hasNextInRow(framework->victims, argument, currentVictim));

	return newActives;
}







