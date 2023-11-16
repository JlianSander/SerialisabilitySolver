#include <stdint.h>
#pragma once

uint32_t** CreateMatrix(int numRow, int numCol);
uint32_t** CreateRows(int numRows);
uint32_t* CreateOneRow(int numColumns);
uint32_t** CopyMatrix(uint32_t** matrix);
int FreeMatrix(uint32_t** matrix);
