#include <stdint.h>
#pragma once

uint32_t** createMatrix(int numRow, int numCol);
uint32_t** createRows(int numRows);
uint32_t* createOneRow(int numColumns);
uint32_t** copyMatrix(uint32_t** matrix);
int freeMatrix(uint32_t** matrix);
