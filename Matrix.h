#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>

typedef struct matrix {
    uint32_t** content;
    uint32_t numberRows;
    uint32_t numberColumns;
} matrix_t;

matrix_t* createMatrix( uint32_t numRows,  uint32_t numColumns);
uint32_t** createRows( uint32_t numRows);
uint32_t* createOneRow( uint32_t numColumns);
matrix_t* copyMatrix(matrix_t* matrix);
uint8_t freeMatrix(matrix_t* matrix);

#endif
