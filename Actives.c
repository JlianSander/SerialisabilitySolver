#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "Actives.h"
#include "Matrix.h"

uint8_t deactivateArgument(matrix_t *matrix, uint32_t argument)
{
	uint32_t idxArgument = argument - 1;
	uint32_t** activeArguments = matrix->content;
	activeArguments[activeArguments[idxArgument][0]][1] = activeArguments[idxArgument][1];
	activeArguments[activeArguments[idxArgument][1]][0] = activeArguments[idxArgument][0];
	activeArguments[idxArgument][0] = NULL;
	activeArguments[idxArgument][1] = NULL;

	return EXIT_SUCCESS;
}

uint32_t getNext(matrix_t *activeArguments, uint32_t argument)
{
	uint32_t idxArgument = argument - 1;
	return activeArguments->content[idxArgument][1];
}

uint32_t getPredecessor(matrix_t *activeArguments, uint32_t argument)
{
	uint32_t idxArgument = argument - 1;
	return activeArguments->content[idxArgument][0];
}

matrix_t* initializeActives(uint32_t numberOfArguments)
{
	matrix_t *actives = createMatrix(numberOfArguments, 2);
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

uint8_t isActive(matrix_t *activeArguments, uint32_t argument)
{
	uint32_t idxArgument = argument - 1;
	if (activeArguments->content[idxArgument][0] != NULL)
	{
		return EXIT_SUCCESS;
	}
	else
	{
		return EXIT_FAILURE;
	}
}