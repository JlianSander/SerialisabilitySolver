#include <stdint.h>
#include <stdio.h>
#include "Matrix.h"

uint32_t** createMatrix(int numRows, int numColumns) {
	uint32_t** matrix = createRows(numRows);
	for (int i = 0; i < numRows; i++) {
		matrix[i] = createOneRow(numColumns);
	}
	return matrix;
}

uint32_t** createRows(int numRows) {
	uint32_t** matrix = (uint32_t**)malloc(numRows * sizeof(uint32_t*));
	return matrix;
}

uint32_t* createOneRow(int numColumns) {
	return (uint32_t*)malloc(numColumns * sizeof(uint32_t));
}

int freeMatrix(uint32_t** matrix) {
	for (int i = 0; i < _countof(matrix); i++) {
		free(matrix[i]);
	}

	return free(matrix);
}