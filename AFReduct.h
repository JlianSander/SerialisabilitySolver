#ifndef AFREDUCT_H
#define AFREDUCT_H

#include <stdint.h>
#include "List.h"
#include "AF.h"
#pragma once

//returns the matrix of the active arguments in the reducted framework
matrix_t* getReduct(matrix_t* activeArguments, argFramework_t* framework, uint32_t argument);

#endif
