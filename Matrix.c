#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

static uint32_t * createOneRow(uint32_t numColumns) {
	uint32_t *row = NULL;
	row = calloc(numColumns, sizeof *row );
	if (row == NULL) {
		printf("Memory allocation failed\n");
		exit(1);
	}
	else {
		return row;
	}
}

static uint32_t ** createRows(uint32_t numRows) {
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


matrix_t * createMatrix(uint32_t numRows, uint32_t numColumns) {
	matrix_t *matrix = NULL;
	matrix = malloc(sizeof *matrix );
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

matrix_t * copyMatrix(matrix_t *matrix)
{
	matrix_t *newMatrix = createMatrix(matrix->numberRows, matrix->numberColumns);
	for (uint32_t i = 0; i < newMatrix->numberRows; i++) {
		for (uint32_t j = 0; j < newMatrix->numberColumns; j++)
		{
			newMatrix->content[i][j] = matrix->content[i][j];
		}
	}
	return newMatrix;
}

uint8_t freeMatrix(matrix_t *matrix) {
	for ( uint32_t i = 0; i < matrix->numberRows; i++) {
		free(matrix->content[i]);
	}
	free(matrix->content);
	free(matrix);
	return EXIT_SUCCESS;
}

uint8_t printMatrix(matrix_t *matrix) {
	printf("\n=====================\nMatrix\nNumber of Rows: %d\nNumber of Collumns: %d\n", matrix->numberRows, matrix->numberColumns);
	for (int i = 0; i < matrix->numberRows; i++) {
		for (int j = 0; j < matrix->numberColumns; j++) {
			printf("%d\t", matrix->content[i][j]);
		}
		printf("\n");
	}
	printf("=====================\n");
}

