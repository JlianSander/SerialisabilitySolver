#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "LinkedSparseMatrix.h"

matrix_t *createLinkedSparseMatrix(uint32_t row, uint32_t column) {
	// add an additional column at the left, to register beginning of linked cells
	// add an additional empty row at the top in a linked sparse matrix, to correct symmetry
	matrix_t *matrix = createMatrix(row + 1, column + 1);
	for(uint32_t i = 1; i < row + 1; i++)
	{
		matrix->content[i][0] = -1;
	}
	//printMatrix(matrix); //DEBUG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	return matrix;
}

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

bool isCellFilled(matrix_t *matrix, uint32_t row, uint32_t column) {
	//printMatrix(matrix); //DEBUG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//printf("Looking at [%d, %d]", row, column); //DEBUG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if (matrix->content[row][column] == 0) {
		return false;
	}
	else {
		return true;
	}
}

uint8_t setCell(matrix_t *matrix, uint32_t row, uint32_t column) {
	if (row == 0 || column == 0) {
		//must not set flags in these places
		return EXIT_FAILURE;
	}

	if (matrix->content[row][column] != 0) {
		return EXIT_FAILURE;
	}
	//printMatrix(matrix); //DEBUG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	uint8_t isSet = 1;
	uint32_t lower = column - 1;
	while (isCellFilled(matrix, row, lower) == false) {
		lower--;
	}
	//printMatrix(matrix); //DEBUG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	matrix->content[row][column] = matrix->content[row][lower];
	matrix->content[row][lower] = column;
	//printMatrix(matrix); //DEBUG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	return EXIT_SUCCESS;
}