#include <stdint.h>
#include "List.h"
#include "AF.h"
#pragma once

uint32_t** getReduct(uint32_t** activeArguments, argFramework_t* framework, uint32_t argument); //returns the matrix of the active arguments in the reducted framework
