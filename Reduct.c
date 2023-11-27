#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "AF.h"
#include "Reduct.h"
#include "List.h"
#include "Matrix.h"
#include "Actives.h"

matrix_t* getReduct(matrix_t* activeArguments, argFramework_t* framework, uint32_t argument)
{
	matrix_t *newActives = copyMatrix(activeArguments);
	deactivateArgument(newActives, argument);
	uint32_t *rowVictims = framework->victims->content[argument];
	uint32_t idxNxtVictim = rowVictims[0];

	//when idxNxtVictim == -1 stopp; when idxNxtVictim == 0 ERROR
	while (idxNxtVictim > 0) {
		deactivateArgument(newActives, idxNxtVictim);
		idxNxtVictim = rowVictims[idxNxtVictim];
	}

	if (idxNxtVictim == 0) {
		printf("ERROR in data model of framework->victims: Expected next entry not '0'");
		exit(1);
	}

	return newActives;
}







