#ifndef ACTIVES_H
#define ACTIVES_H

#include <stdint.h>
#include "Matrix.h"

/// <summary>
/// Modifies the specified matrix, so that the specified argument is deactivated.
/// </summary>
/// <param name="matrix">Matrix of all active arguments.</param>
/// <param name="argument">The argument to deactivate.</param>
/// <returns>EXIT_SUCCESS iff the operation was successful.</returns>
uint8_t deactivateArgument(matrix_t *matrix, uint32_t argument);
/// <summary>
/// Returns the next active argument.
/// </summary>
/// <param name="activeArguments">Matrix registering, which argument is active.</param>
/// <param name="argument">The currently pointed to active argument.</param>
/// <returns>The next active argument.</returns>
uint32_t getNext(matrix_t *activeArguments, uint32_t argument);
/// <summary>
/// Returns the active argument, which was located before the one specified in the matrix specified.
/// </summary>
/// <param name="activeArguments">Matrix registering, which argument is active.</param>
/// <param name="argument">The currently pointed to active argument.</param>
/// <returns>The active argument, which was located before the argument specified.</returns>
uint32_t getPredecessor(matrix_t *activeArguments, uint32_t argument);
/// <summary>
/// Creates a 2D-matrix, allowing direct access to and efficient iterating through the active arguments of 
/// a framework. <br> - </br> The structure is the following: 1st column points to the last active predecessor; 
/// 2nd column points to the next active successor. <br> - </br>
/// Initially all arguments are registered to be active.
/// </summary>
/// <param name="numberOfArguments">The number of arguments in total.</param>
/// <returns>2D matrix of all indicating active arguments.</returns>
matrix_t* initializeActives(uint32_t numberOfArguments);
/// <summary>
/// Check if a specified argument is registered to be active in a specified matrix.
/// </summary>
/// <param name="activeArguments">Matrix registering, which argument is active.</param>
/// <param name="argument">The argument to be checked.</param>
/// <returns>Returns EXIT_SUCCESS iff specified argument is active; Returns EXIT_FAILURE otherwise</returns>
uint8_t isActive(matrix_t *activeArguments, uint32_t argument);

#endif
