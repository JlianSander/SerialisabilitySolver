#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

static uint32_t ** create_rows(uint32_t numRows) {
	uint32_t **matrix = NULL;
	matrix = calloc(numRows, sizeof *matrix );
	if (matrix == NULL) {
		printf("Memory allocation failed\n");
		exit(1);
	}
	else {
		return matrix;
	}
}


matrix_t * create_matrix(uint32_t numRows, uint32_t numColumns) {
	matrix_t *matrix = NULL;
	matrix = malloc(sizeof *matrix );
	if (matrix == NULL) {
		printf("Memory allocation failed\n");
		exit(1);
	}
	else {
		matrix->numberRows = numRows;
		matrix->numberColumns = numColumns;
		matrix->content = create_rows(numRows);
		for (uint32_t i = 0; i < numRows; i++) {
			matrix->content[i] = create_array(numColumns);
		}
		return matrix;
	}
}

matrix_t * copy_matrix(matrix_t *matrix)
{
	matrix_t *newMatrix = create_matrix(matrix->numberRows, matrix->numberColumns);
	for (uint32_t i = 0; i < newMatrix->numberRows; i++) {
		for (uint32_t j = 0; j < newMatrix->numberColumns; j++)
		{
			newMatrix->content[i][j] = matrix->content[i][j];
		}
	}
	return newMatrix;
}

uint8_t free_matrix(matrix_t *matrix) {
	for ( uint32_t i = 0; i < matrix->numberRows; i++) {
		free(matrix->content[i]);
	}
	free(matrix->content);
	free(matrix);
	return EXIT_SUCCESS;
}

uint8_t print_matrix(matrix_t *matrix) {
	printf("\n=====================\nMatrix\nNumber of Rows: %d\nNumber of Collumns: %d\n", matrix->numberRows, matrix->numberColumns);
	for (int i = 0; i < matrix->numberRows; i++) {
		for (int j = 0; j < matrix->numberColumns; j++) {
			printf("%d\t", matrix->content[i][j]);
		}
		printf("\n");
	}
	printf("=====================\n");
}

