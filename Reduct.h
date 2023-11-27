#ifndef AFREDUCT_H
#define AFREDUCT_H

#include <stdint.h>
#include "AF.h"
#include "List.h"
#include "Matrix.h"
#pragma once

/// <summary>
/// Reduces the specified framework, using the specified set of active arguments by the specified argument.
/// </summary>
/// <param name="activeArguments">Set of arguments, which are active in the current transition state.</param>
/// <param name="framework">The framework to reduce.</param>
/// <param name="argument">The argument, by which the framework will be reduced.</param>
/// <returns>Set of active arguments in the new transition state after the reduction.</returns>
matrix_t * getReduct(matrix_t *activeArguments, argFramework_t *framework, uint32_t argument);

#endif
