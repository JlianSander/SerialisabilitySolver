
#include "Actives.h"

activeArgs_t *create_active_arguments(uint32_t numberArguments, uint32_t numberActiveArguments)
{
	activeArgs_t *activeArgs = NULL;
	activeArgs = malloc(sizeof * activeArgs);
	if (activeArgs == NULL) {
		printf("Memory allocation failed\n");
		exit(1);
	}
	else {
		activeArgs->numberActiveArguments = numberArguments;
		activeArgs->matrix = create_matrix(numberArguments + 1, 3);
		activeArgs->encodingToArgument = create_array(numberActiveArguments + 1);
		return activeArgs;
	}
}

activeArgs_t *copy_active_arguments(activeArgs_t *original)
{
	activeArgs_t *activeArgs = create_active_arguments(original->matrix->numberRows, original->numberActiveArguments);

	activeArgs->matrix->content[0][1] = original->matrix->content[0][1];
	uint32_t idxArgument = 0;
	while (has_next(original, idxArgument))
	{
		idxArgument = get_next(original, idxArgument);
		activeArgs->matrix->content[idxArgument][0] = original->matrix->content[idxArgument][0];
		activeArgs->matrix->content[idxArgument][1] = original->matrix->content[idxArgument][1];
		activeArgs->matrix->content[idxArgument][2] = original->matrix->content[idxArgument][3];
	}

	activeArgs->encodingToArgument = copy_array(original->encodingToArgument);

	return activeArgs;
}

uint8_t deactivate_argument(activeArgs_t *activeArguments, uint32_t argument)
{
	uint32_t** matrix = activeArguments->matrix->content;

	if (matrix[argument][0] == argument && matrix[argument][1] == argument) {
		//only element in list
		matrix[0][1] = 0;
		matrix[argument][0] = 0;
		matrix[argument][1] = 0;
	}
	else if (matrix[argument][0] == argument) {
		// set new lower bound of list
		matrix[0][1] = matrix[argument][1];
		matrix[matrix[argument][1]][0] = matrix[argument][1];
	}
	else if (matrix[argument][1] == argument) {
		//set new upper bound of list
		matrix[matrix[argument][0]][1] = matrix[argument][0];
	}
	else {
		matrix[matrix[argument][1]][0] = matrix[argument][0];
		matrix[matrix[argument][0]][1] = matrix[argument][1];
	}
	matrix[argument][0] = 0;
	matrix[argument][1] = 0;
	matrix[argument][2] = 0;

	arrayInt_t *newEncoding = create_array(activeArguments->numberActiveArguments - 1);
	for (int i = 1; i < activeArguments->numberActiveArguments - 1 + 1; i++)
	{
		if (activeArguments->encodingToArgument->elements[i] < argument)
		{
			//arguments before the argument to deactivate
			newEncoding->elements[i] = activeArguments->encodingToArgument->elements[i];
		}
		else if (activeArguments->encodingToArgument->elements[i] > argument)
		{
			//arguments after the argument to deactivate
			newEncoding->elements[i - 1] = activeArguments->encodingToArgument->elements[i]; //i - 1 since gap of argument to deactive gets filled
			matrix[activeArguments->encodingToArgument->elements[i]][2] = i - 1;
		}
	}
	free_array(activeArguments->encodingToArgument);
	activeArguments->encodingToArgument = newEncoding;

	return EXIT_SUCCESS;
}

uint8_t free_activeArguments(activeArgs_t *activeArguments)
{
	if (free_matrix(activeArguments->matrix) == EXIT_FAILURE)
	{
		return EXIT_FAILURE;
	}

	free(activeArguments);
	return EXIT_SUCCESS;
}

uint32_t get_next(activeArgs_t *activeArguments, uint32_t argument)
{
	return activeArguments->matrix->content[argument][1];
}

uint32_t get_predecessor(activeArgs_t *activeArguments, uint32_t argument)
{
	return activeArguments->matrix->content[argument][0];
}

activeArgs_t* initialize_actives(uint32_t numberOfArguments)
{
	activeArgs_t *activeArgs = create_active_arguments(numberOfArguments, numberOfArguments);
	matrix_t *matrix = activeArgs->matrix;
	matrix->content[0][1] = 1;
	for (uint32_t i = 1; i < numberOfArguments + 1; i++) {
		if (i == 1)
		{
			matrix->content[i][0] = i;
		}
		else
		{
			matrix->content[i][0] = i - 1;
		}
		
		if (i == numberOfArguments ) {
			matrix->content[i][1] = i;
		}
		else {
			matrix->content[i][1] = i + 1;
		}

		matrix->content[i][2] = i;
		activeArgs->encodingToArgument->elements[i] = i;
	}

	return activeArgs;
}

bool is_active(activeArgs_t *activeArguments, uint32_t argument)
{
	if (activeArguments->matrix->content[argument][0] == 0
		&& activeArguments->matrix->content[argument][1] == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool has_next(activeArgs_t *activeArguments, uint32_t argument) {
	return activeArguments->matrix->content[argument][1] != argument;
}

bool has_predecessor(activeArgs_t *activeArguments, uint32_t argument) {
	return activeArguments->matrix->content[argument][0] != argument;
}