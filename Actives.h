#include <stdint.h>
#pragma once

uint32_t deactivateArgument(uint32_t** activeArguments, uint32_t argument); // set the specified argument as inactive
uint32_t getNext(uint32_t** activeArguments, uint32_t argument); // returns the active argument, which is located before the one specified
uint32_t getPredecessor(uint32_t** activeArguments, uint32_t argument); // returns the next active argument after the one specified
uint32_t** initializeActives(uint32_t numberOfArguments);
uint32_t isActive(uint32_t** activeArguments, uint32_t argument); // returns 1 iff specified argument is active; returns 0 otherwise
