#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "AF.h"
#include "AFReduct.h"
#include "List.h"
#include "Matrix.h"
#include "Actives.h"

matrix_t* getReduct(matrix_t* activeArguments, argFramework_t* framework, uint32_t argument)
{
	matrix_t* newActives = copyMatrix(activeArguments);
	deactivateArgument(newActives, argument);
	uint32_t* victimsOfArg = framework->victims[argument];
	for (uint32_t i = 0; i < __crt_countof(victimsOfArg); i++)
	{
		deactivateArgument(newActives, victimsOfArg[i]);
	}
	return newActives;
}







