#include <stdint.h>
#include <stdio.h>
#include "Matrix.h"

uint32_t** createMatrix( uint32_t numRows,  uint32_t numColumns) {
	uint32_t** matrix = createRows(numRows);
	for ( uint32_t i = 0; i < numRows; i++) {
		matrix[i] = createOneRow(numColumns);
	}
	return matrix;
}

uint32_t** createRows( uint32_t numRows) {
	uint32_t** matrix = (uint32_t**)malloc(numRows * sizeof(uint32_t*));
	return matrix;
}

uint32_t* createOneRow( uint32_t numColumns) {
	return (uint32_t*)malloc(numColumns * sizeof(uint32_t));
}

uint32_t** copyMatrix(uint32_t** matrix)
{
	uint32_t** newMatrix = createRows(_countof(matrix));
	for ( uint32_t i = 0; i < countRows(matrix); i++) {
		newMatrix[i] = createOneRow(__crt_countof(matrix[i]));
		for ( uint32_t j = 0; j < __crt_countof(matrix[i]); j++)
		{
			newMatrix[i][j] = matrix[i][j];
		}
	}

	return newMatrix;
}

 uint32_t freeMatrix(uint32_t** matrix) {
	for ( uint32_t i = 0; i < countRows(matrix); i++) {
		free(matrix[i]);
	}

	return free(matrix);
}

static  uint32_t countRows(uint32_t** matrix)
{
	return sizeof(matrix) / sizeof(uint32_t);
}