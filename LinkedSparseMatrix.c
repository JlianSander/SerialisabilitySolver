#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "LinkedSparseMatrix.h"

matrix_t *createLinkedSparseMatrix(uint32_t row, uint32_t column) {
	// add an additional column at the left, to register beginning of linked cells
	// add an additional empty row at the top in a linked sparse matrix, to correct symmetry
	matrix_t *matrix = createMatrix(row + 1, column + 1);
	return matrix;
}

uint32_t getNextInRow(matrix_t *matrix, uint32_t row, uint32_t currentCell) {
	return matrix->content[row][currentCell];
}

bool hasNextInRow(matrix_t *matrix, uint32_t row, uint32_t currentCell) {
	if (matrix->content[row][currentCell] == 0) {
		return false;
	}

	if (matrix->content[row][currentCell] == currentCell) {
		return false;
	}
	else {
		return true;
	}
}

bool isCellFilled(matrix_t *matrix, uint32_t row, uint32_t column) {
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
	uint8_t isSet = 1;
	uint32_t lower = column - 1;
	while (isCellFilled(matrix, row, lower) == false && lower > 0) {
		lower--;
	}

	if (lower == 0) {
		//1st entry of the list
		if (matrix->content[row][0] == 0) {
			//only entry
			matrix->content[row][0] = column; //new beginning
			matrix->content[row][column] = column; //new end
		}
		else {
			matrix->content[row][column] = matrix->content[row][0];
			matrix->content[row][0] = column; // new beginning
		}
		
	}
	else if (matrix->content[row][lower] ==  lower) {
		//last entry of list
		matrix->content[row][lower] = column;
		matrix->content[row][column] = column; //new end
	}
	else {
		//between other entries
		matrix->content[row][column] = matrix->content[row][lower];
		matrix->content[row][lower] = column;
	}
	
	return EXIT_SUCCESS;
}