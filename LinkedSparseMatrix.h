#ifndef LINKED_SPARSE_MATRIX_H
#define LINKED_SPARSE_MATRIX_H

#include "Matrix.h"

/// <summary>
/// Creates a matrix according the definition of the linked sparse matrices.
/// </summary>
/// <param name="row">Number of rows in the matrix.</param>
/// <param name="column">Number of columns in the matrix</param>
/// <returns>A new linked sparse matrix, which entries are all 0;</returns>
matrix_t *createLinkedSparseMatrix(uint32_t row, uint32_t column);
/// <summary>
/// Returns the index of the next cell which is not 0 in the specified row or -1 if no further cell is set.
/// </summary>
/// <param name="matrix">The linked sparse matrix-</param>
/// <param name="row">Index to access the specified row in the matrix.</param>
/// <param name="currentCell">The currently pointed cell. For initial call use '0'.</param>
/// <returns>Index of the next cell which is != 0</returns>
uint32_t getNextInRow(matrix_t *matrix, uint32_t row, uint32_t currentCell);
/// <summary>
/// Signals if there is a cell in the specified row further right than the one specified, which is set to non 0. 
/// </summary>
/// <param name="matrix">The linked sparse matrix-</param>
/// <param name="row">Index to access the specified row in the matrix.</param>
/// <param name="currentCell">The currently pointed cell. For initial call use '0'.</param>
/// <param name="resultByReference"> 0 iff there is a next cell. 1 otherwise</param>
/// <returns>EXIT_SUCCESS the operation was successful. EXIT_FAILURE if there was an error.</returns>
uint8_t hasNextInRow(matrix_t *matrix, uint32_t row, uint32_t currentCell, uint8_t *resultByReference);
/// <summary>
/// Methods checks if a cell in a specified row and specified collumn is set or not.
/// </summary>
/// <param name="matrix">A linked sparse matrix.</param>
/// <param name="row">Index of a row.</param>
/// <param name="collumn">Index of a column.</param>
/// <returns>TRUE iff the cell is set. FALSE otherwise.</returns>
bool isCellFilled(matrix_t *matrix, uint32_t row, uint32_t column);
/// <summary>
/// Sets the flag in a cell of a specified matrix.
/// </summary>
/// <param name="matrix">A linked sparse matrix.</param>
/// <param name="row">Index of a row.</param>
/// <param name="collumn">Index of a column.</param>
/// <returns>EXIT_SUCCESS the operation was successful. EXIT_FAILURE if there was an error.</returns>
uint8_t setCell(matrix_t *matrix, uint32_t row, uint32_t column);


#endif