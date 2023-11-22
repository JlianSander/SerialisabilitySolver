#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "AF.h"
#include "AFReduct.h"
#include "List.h"
#include "Matrix.h"
#include "Actives.h"

uint32_t** getReduct(uint32_t** activeArguments, argFramework_t* framework, uint32_t argument)
{
	uint32_t** newActives = copyMatrix(activeArguments);
	deactivateArgument(newActives, argument);
	uint32_t* victimsOfArg = framework->victims[argument];
	for (uint32_t i = 0; i < __crt_countof(victimsOfArg); i++)
	{
		deactivateArgument(newActives, victimsOfArg[i]);
	}
	return newActives;
}







