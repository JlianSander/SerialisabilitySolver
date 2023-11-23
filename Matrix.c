#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

matrix_t* createMatrix(uint32_t numRows, uint32_t numColumns) {
	matrix_t* matrix = malloc(sizeof(matrix_t));
	if (matrix == NULL) {
		printf("Memory allocation failed\n");
		exit(1);
	}
	else {
		matrix->numberRows = numRows;
		matrix->numberColumns = numColumns;
		matrix->content = createRows(numRows);
		for (uint32_t i = 0; i < numRows; i++) {
			matrix->content[i] = createOneRow(numColumns);
		}
		return matrix;
	}
}

uint32_t** createRows( uint32_t numRows) {
	uint32_t** matrix = malloc(numRows * sizeof(uint32_t*));
	if (matrix == NULL) {
		printf("Memory allocation failed\n");
		exit(1);
	}
	else {
		return matrix;
	}
}

uint32_t* createOneRow( uint32_t numColumns) {
	uint32_t* row = malloc(numColumns * sizeof(uint32_t));
	if (row == NULL) {
		printf("Memory allocation failed\n");
		exit(1);
	}
	else {
		return row;
	}
}

matrix_t* copyMatrix(matrix_t* matrix)
{
	matrix_t* newMatrix = createMatrix(matrix->numberRows, matrix->numberColumns);
	for (uint32_t i = 0; i < newMatrix->numberRows; i++) {
		for (uint32_t j = 0; j < newMatrix->numberColumns; j++)
		{
			newMatrix->content[i][j] = matrix->content[i][j];
		}
	}
	return newMatrix;
}

 uint8_t freeMatrix(matrix_t* matrix) {
	for ( uint32_t i = 0; i < matrix->numberRows; i++) {
		free(matrix->content[i]);
	}
	free(matrix->content);
	free(matrix);
	return EXIT_SUCCESS;
}

