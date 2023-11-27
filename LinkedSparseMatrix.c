#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "LinkedSparseMatrix.h"

uint32_t getNextInRow(matrix_t *matrix, uint32_t row, uint32_t currentCell) {
	return matrix->content[row][currentCell];
}

uint8_t hasNextInRow(matrix_t *matrix, uint32_t row, uint32_t currentCell, uint8_t *resultByReference) {
	if (matrix->content[row][currentCell] == 0) {
		return EXIT_FAILURE;
	}

	if (matrix->content[row][currentCell] == -1) {
		*resultByReference = 1;
	}
	else {
		*resultByReference = 0;
	}

	return EXIT_SUCCESS;
}