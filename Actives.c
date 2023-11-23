#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "Actives.h"
#include "Matrix.h"

uint8_t deactivateArgument(matrix_t* matrix, uint32_t argument)
{
	uint32_t** activeArguments = matrix->content;
	activeArguments[activeArguments[argument][0]][1] = activeArguments[argument][1];
	activeArguments[activeArguments[argument][1]][0] = activeArguments[argument][0];
	activeArguments[argument][0] = NULL;
	activeArguments[argument][1] = NULL;

	return EXIT_SUCCESS;
}

uint32_t getNext(matrix_t* activeArguments, uint32_t argument)
{
	return activeArguments->content[argument][1];
}

uint32_t getPredecessor(matrix_t* activeArguments, uint32_t argument)
{
	return activeArguments->content[argument][0];
}

matrix_t* initializeActives(uint32_t numberOfArguments)
{
	matrix_t* actives = createMatrix(numberOfArguments, 2);
	for (uint32_t i = 0; i < numberOfArguments; i++) {
		if (i == 0)
		{
			actives->content[i][0] = -1;
		}
		else
		{
			actives->content[i][0] = i - 1;
		}
		
		if (i == numberOfArguments - 1) {
			actives->content[i][1] = -1;
		}
		else {
			actives->content[i][1] = i + 1;
		}
	}

	return actives;
}

uint8_t isActive(matrix_t* activeArguments, uint32_t argument)
{
	if (activeArguments->content[argument][0] != NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}