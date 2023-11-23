#ifndef ACTIVES_H
#define ACTIVES_H

#include <stdint.h>

uint8_t deactivateArgument(matrix_t* matrix, uint32_t argument); // set the specified argument as inactive
uint32_t getNext(matrix_t* activeArguments, uint32_t argument); // returns the active argument, which is located before the one specified
uint32_t getPredecessor(matrix_t* activeArguments, uint32_t argument); // returns the next active argument after the one specified
matrix_t* initializeActives(uint32_t numberOfArguments);
uint8_t isActive(matrix_t* activeArguments, uint32_t argument); // returns 1 iff specified argument is active; returns 0 otherwise

#endif
