#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "AF.h"
#include "List.h"
#include "Matrix.h"

argumentInitTemp_t* SetUpInitialization(int firstArgument)
{
	argumentInitTemp_t* current = (argumentInitTemp_t*)malloc(sizeof(argumentInitTemp_t));

	//initialize argument
	current->next = NULL;
	current->number = firstArgument;
	current->listAttackers = NULL;
	current->listVictims = NULL;

	return current;
}

int AddArgument(argumentInitTemp_t* head, int argument) {
	argumentInitTemp_t* current = head;
	while (current->next != NULL) { // iterate to end of list
		current = current->next;
	}

	//create new argument
	current->next = (argumentInitTemp_t*)malloc(sizeof(argumentInitTemp_t));
	current = current->next;
	
	//initialize argument
	current->next = NULL;
	current->number = argument;
	current->listAttackers = NULL;
	current->listVictims = NULL;

	return EXIT_SUCCESS;
}

int AddAttack(argumentInitTemp_t* head, int attacker, int victim) {
	int retVal = UpdateAttacker(head, attacker, victim);
	retVal = retVal || UpdateVictim(head, attacker, victim);
	return retVal;
}

static int UpdateVictim(argumentInitTemp_t* head, int attacker, int victim)
{
	argumentInitTemp_t* current = GoToArgument(head, victim);

	if (current->listAttackers == NULL) {
		//initialize list of attackers
		current->listAttackers = (nodeInt_t*)malloc(sizeof(nodeInt_t));
		current->listAttackers->next = NULL;
		current->listAttackers->number = attacker;
	}
	else {
		Push(current->listAttackers, attacker);
	}
	return EXIT_SUCCESS;
}

static int UpdateAttacker(argumentInitTemp_t* head, int attacker, int victim)
{
	argumentInitTemp_t* current = GoToArgument(head, attacker);

	if (current->listVictims == NULL) {
		//initialize list of victims
		current->listVictims = (nodeInt_t*)malloc(sizeof(nodeInt_t));
		current->listVictims->next = NULL;
		current->listVictims->number = victim;
	}
	else {
		Push(current->listVictims, victim);
	}
	return EXIT_SUCCESS;
}

static argumentInitTemp_t* GoToArgument(argumentInitTemp_t* head, int argument)
{
	argumentInitTemp_t* current = head;
	while (current->number != argument) { // iterate to the argument
		current = current->next;

		if (current == NULL) { //argument not found in the list
			return EXIT_FAILURE;
		}
	}

	return current;
}

argFramework_t* InitializeFramework(argumentInitTemp_t* head, uint32_t numberOfArguments)
{
	argFramework_t* framework = (argFramework_t*)malloc(sizeof(argFramework_t));
	framework->number = numberOfArguments;
	framework->attackers = InitializeAttackers(head, framework->number);
	framework->victims = InitializeVictims(head, framework->number);

	FreeInitializationMemory(head);

	return framework;
}

uint32_t** InitializeActives(uint32_t numberOfArguments)
{
	uint32_t** actives = CreateMatrix(numberOfArguments, 2);
	for (int i = 1; i < numberOfArguments; i++) {
		actives[i][0] = i -1;
		if (i == numberOfArguments - 1) {
			actives[i][1] = -1;
		} 
		else {
			actives[i][1] = i + 1;
		}
	}

	return actives;
}

static uint32_t** InitializeAttackers(argumentInitTemp_t* head, uint32_t numberOfArguments)
{
	argumentInitTemp_t* current = head;
	uint32_t** matrix = CreateRows(numberOfArguments);

	for (int i = 0; i < numberOfArguments; i++)
	{
		int numArgs = CountList(current->listAttackers);
		matrix[i] = CreateOneRow(numArgs);
		nodeInt_t* currentAttacker = current->listAttackers;
		for (int j = 0; j < numArgs; j++)
		{
			matrix[i][j] = currentAttacker->number;

			currentAttacker = currentAttacker->next;
		}

		current = current->next;
	}

	return matrix;
}

static uint32_t** InitializeVictims(argumentInitTemp_t* head, uint32_t numberOfArguments) {
	argumentInitTemp_t* current = head;
	uint32_t** matrix = CreateRows(numberOfArguments);

	for (int i = 0; i < numberOfArguments; i++)
	{
		int numArgs = CountList(current->listVictims);
		matrix[i] = CreateOneRow(numArgs);
		nodeInt_t* currentVictim = current->listVictims;
		for (int j = 0; j < numArgs; j++)
		{
			matrix[i][j] = currentVictim->number;

			currentVictim = currentVictim->next;
		}

		current = current->next;
	}

	return matrix;
}

static int FreeInitializationMemory(argumentInitTemp_t* head)
{
	argumentInitTemp_t* current = head;
	argumentInitTemp_t* next = current->next;

	while (next != NULL)
	{
		FreeContent(current);
		free(current);
		current = next;
		next = current->next;
	}
	FreeContent(current);
	free(current);

	return EXIT_SUCCESS;
}

static int FreeContent(argumentInitTemp_t* argument)
{
	int retVal = FreeList(argument->listAttackers);
	retVal = retVal || FreeList(argument->listVictims);
}

uint32_t** GetReduct(argFramework_t* framework, uint32_t** activeArguments, uint32_t argument)
{
	uint32_t** newActives = CopyMatrix(activeArguments);
	DeactivateArgument(newActives, argument);

	uint32_t* victims = framework->victims[argument];
	for (int i = 0; i < _countof(victims); i++)
	{
		DeactivateArgument(newActives, victims[i]);
	}

	return newActives;
}

static int DeactivateArgument(uint32_t** activeArguments, uint32_t argument)
{
	activeArguments[activeArguments[argument][0]][1] = activeArguments[argument][1];
	activeArguments[activeArguments[argument][1]][0] = activeArguments[argument][0];
	activeArguments[argument][0] = NULL;
	activeArguments[argument][1] = NULL;

	return EXIT_SUCCESS;
}
