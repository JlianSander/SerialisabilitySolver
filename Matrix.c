#include <stdint.h>
#include <stdio.h>
#include "Matrix.h"

uint32_t** CreateMatrix(int numRows, int numColumns) {
	uint32_t** matrix = CreateRows(numRows);
	for (int i = 0; i < numRows; i++) {
		matrix[i] = CreateOneRow(numColumns);
	}
	return matrix;
}

uint32_t** CreateRows(int numRows) {
	uint32_t** matrix = (uint32_t**)malloc(numRows * sizeof(uint32_t*));
	return matrix;
}

uint32_t* CreateOneRow(int numColumns) {
	return (uint32_t*)malloc(numColumns * sizeof(uint32_t));
}

int FreeMatrix(uint32_t** matrix) {
	for (int i = 0; i < _countof(matrix); i++) {
		free(matrix[i]);
	}

	return free(matrix);
}