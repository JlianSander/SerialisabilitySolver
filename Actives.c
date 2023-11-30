#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Actives.h"
#include "Matrix.h"

uint8_t deactivateArgument(matrix_t *matrix, uint32_t argument)
{
	uint32_t** activeArguments = matrix->content;

	if (activeArguments[argument][0] == argument && activeArguments[argument][1] == argument) {
		//only element in list
		activeArguments[0][1] = 0;
		activeArguments[argument][0] = 0;
		activeArguments[argument][1] = 0;
	}
	else if (activeArguments[argument][0] == argument) {
		// set new lower bound of list
		//printf("\nDEBUGGING: ausgangssituation\n"); //DEBUGGING !!!!!!!
		//printMatrix(matrix); //DEBUGGING !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		activeArguments[0][1] = activeArguments[argument][1];
		//printf("\nDEBUGGING: activeArguments[0][1] = activeArguments[argument][1]\n"); //DEBUGGING !!!!!!!
		//printMatrix(matrix); //DEBUGGING !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		activeArguments[activeArguments[argument][1]][0] = activeArguments[argument][1];
		//printf("\nDEBUGGING: activeArguments[activeArguments[argument][1]][0] = activeArguments[argument][1]\n"); //DEBUGGING !!!!!!!
		//printMatrix(matrix); //DEBUGGING !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}
	else if (activeArguments[argument][1] == argument) {
		//set new upper bound of list
		activeArguments[activeArguments[argument][0]][1] = activeArguments[argument][0];
	}
	else {
		activeArguments[activeArguments[argument][1]][0] = activeArguments[argument][0];
		activeArguments[activeArguments[argument][0]][1] = activeArguments[argument][1];
	}
	activeArguments[argument][0] = 0;
	activeArguments[argument][1] = 0;
	//printf("\nDEBUGGING: activeArguments[argument][0] = 0; activeArguments[argument][1] = 0\n"); //DEBUGGING !!!!!!!
	//printMatrix(matrix); //DEBUGGING !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	return EXIT_SUCCESS;
}

uint32_t getNext(matrix_t *activeArguments, uint32_t argument)
{
	return activeArguments->content[argument][1];
}

uint32_t getPredecessor(matrix_t *activeArguments, uint32_t argument)
{
	return activeArguments->content[argument][0];
}

matrix_t* initializeActives(uint32_t numberOfArguments)
{
	matrix_t *actives = createMatrix(numberOfArguments + 1, 2);
	actives->content[0][1] = 1;
	for (uint32_t i = 1; i < numberOfArguments + 1; i++) {
		if (i == 1)
		{
			actives->content[i][0] = 1;
		}
		else
		{
			actives->content[i][0] = i - 1;
		}
		
		if (i == numberOfArguments ) {
			actives->content[i][1] = i;
		}
		else {
			actives->content[i][1] = i + 1;
		}
	}

	return actives;
}

bool isActive(matrix_t *activeArguments, uint32_t argument)
{
	if (activeArguments->content[argument][0] == 0
		&& activeArguments->content[argument][1] == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool hasNext(matrix_t *activeArguments, uint32_t argument) {
	return activeArguments->content[argument][1] != argument;
}

bool hasPredecessor(matrix_t *activeArguments, uint32_t argument) {
	return activeArguments->content[argument][0] != argument;
}