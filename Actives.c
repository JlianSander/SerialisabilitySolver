#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "Actives.h"
#include "Matrix.h"

uint32_t deactivateArgument(uint32_t** activeArguments, uint32_t argument)
{
	activeArguments[activeArguments[argument][0]][1] = activeArguments[argument][1];
	activeArguments[activeArguments[argument][1]][0] = activeArguments[argument][0];
	activeArguments[argument][0] = NULL;
	activeArguments[argument][1] = NULL;

	return EXIT_SUCCESS;
}

uint32_t getPredecessor(uint32_t** activeArguments, uint32_t argument)
{
	return activeArguments[argument][0];
}

uint32_t getNext(uint32_t** activeArguments, uint32_t argument)
{
	return activeArguments[argument][1];
}

uint32_t** initializeActives(uint32_t numberOfArguments)
{
	uint32_t** actives = createMatrix(numberOfArguments, 2);
	for (uint32_t i = 0; i < numberOfArguments; i++) {
		if (i == 0)
		{
			actives[i][0] = -1;
		}
		else
		{
			actives[i][0] = i - 1;
		}
		
		if (i == numberOfArguments - 1) {
			actives[i][1] = -1;
		}
		else {
			actives[i][1] = i + 1;
		}
	}

	return actives;
}

uint32_t isActive(uint32_t** activeArguments, uint32_t argument)
{
	if (activeArguments[argument][0] != NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}