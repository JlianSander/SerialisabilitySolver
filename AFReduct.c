#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "AF.h"
#include "AFReduct.h"
#include "List.h"
#include "Matrix.h"

argFramework_t* getReduct(argFramework_t* framework, uint32_t argument)
{
	argFramework_t* newFramework = copyFramework(framework);
	
	uint32_t* victimsOfArg = framework->victims[argument];
	uint32_t* attackersOfArg = framework->attackers[argument];

	for (uint32_t i = 0; i < __crt_countof(attackersOfArg); i++)
	{
		uint32_t* victimsOfAttacker = newFramework->victims[attackersOfArg[i]];
		victimsOfAttacker = createOneRow(__crt_countof(victimsOfAttacker) - sizeof(uint32_t));

		//TODO set new array of victims, without the argument to reduct
	}

	deactivateArgument(newFramework->actives, argument);
	for (uint32_t i = 0; i < __crt_countof(victimsOfArg); i++)
	{
		deactivateArgument(newFramework->actives, victimsOfArg[i]);
	}
	
}

static argFramework_t* copyFramework(argFramework_t* framework)
{
	uint32_t** newActives = copyMatrix(framework->actives);
	uint32_t** newAttackers = copyMatrix(framework->attackers);
	uint32_t** newVictims = copyMatrix(framework->victims);
}



static  uint32_t deactivateArgument(uint32_t** activeArguments, uint32_t argument)
{
	activeArguments[activeArguments[argument][0]][1] = activeArguments[argument][1];
	activeArguments[activeArguments[argument][1]][0] = activeArguments[argument][0];
	activeArguments[argument][0] = NULL;
	activeArguments[argument][1] = NULL;

	return EXIT_SUCCESS;
}



