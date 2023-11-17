#include <stdint.h>
#pragma once

uint32_t** createMatrix( uint32_t numRow,  uint32_t numCol);
uint32_t** createRows( uint32_t numRows);
uint32_t* createOneRow( uint32_t numColumns);
uint32_t** copyMatrix(uint32_t** matrix);
 uint32_t freeMatrix(uint32_t** matrix);
