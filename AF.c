#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "AF.h"
#include "List.h"
#include "Matrix.h"

argumentInitTemp_t* setUpInitialization(int firstArgument)
{
	argumentInitTemp_t* current = (argumentInitTemp_t*)malloc(sizeof(argumentInitTemp_t));

	//initialize argument
	current->next = NULL;
	current->number = firstArgument;
	current->listAttackers = NULL;
	current->listVictims = NULL;

	return current;
}

int addArgument(argumentInitTemp_t* head, int argument) {
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

int addAttack(argumentInitTemp_t* head, int attacker, int victim) {
	int retVal = updateAttacker(head, attacker, victim);
	retVal = retVal || updateVictim(head, attacker, victim);
	return retVal;
}

static int updateVictim(argumentInitTemp_t* head, int attacker, int victim)
{
	argumentInitTemp_t* current = goToArgument(head, victim);

	if (current->listAttackers == NULL) {
		//initialize list of attackers
		current->listAttackers = (nodeInt_t*)malloc(sizeof(nodeInt_t));
		current->listAttackers->next = NULL;
		current->listAttackers->number = attacker;
	}
	else {
		push(current->listAttackers, attacker);
	}
	return EXIT_SUCCESS;
}

static int updateAttacker(argumentInitTemp_t* head, int attacker, int victim)
{
	argumentInitTemp_t* current = goToArgument(head, attacker);

	if (current->listVictims == NULL) {
		//initialize list of victims
		current->listVictims = (nodeInt_t*)malloc(sizeof(nodeInt_t));
		current->listVictims->next = NULL;
		current->listVictims->number = victim;
	}
	else {
		push(current->listVictims, victim);
	}
	return EXIT_SUCCESS;
}

static argumentInitTemp_t* goToArgument(argumentInitTemp_t* head, int argument)
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

argFramework_t* initializeFramework(argumentInitTemp_t* head, uint32_t numberOfArguments)
{
	argFramework_t* framework = (argFramework_t*)malloc(sizeof(argFramework_t));
	framework->number = numberOfArguments;
	framework->attackers = initializeAttackers(head, framework->number);
	framework->victims = initializeVictims(head, framework->number);

	freeInitializationMemory(head);

	return framework;
}

uint32_t** initializeActives(uint32_t numberOfArguments)
{
	uint32_t** actives = createMatrix(numberOfArguments, 2);
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

static uint32_t** initializeAttackers(argumentInitTemp_t* head, uint32_t numberOfArguments)
{
	argumentInitTemp_t* current = head;
	uint32_t** matrix = createRows(numberOfArguments);

	for (int i = 0; i < numberOfArguments; i++)
	{
		int numArgs = countList(current->listAttackers);
		matrix[i] = createOneRow(numArgs);
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

static uint32_t** initializeVictims(argumentInitTemp_t* head, uint32_t numberOfArguments) {
	argumentInitTemp_t* current = head;
	uint32_t** matrix = createRows(numberOfArguments);

	for (int i = 0; i < numberOfArguments; i++)
	{
		int numArgs = countList(current->listVictims);
		matrix[i] = createOneRow(numArgs);
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

static int freeInitializationMemory(argumentInitTemp_t* head)
{
	argumentInitTemp_t* current = head;
	argumentInitTemp_t* next = current->next;

	while (next != NULL)
	{
		freeContent(current);
		free(current);
		current = next;
		next = current->next;
	}
	freeContent(current);
	free(current);

	return EXIT_SUCCESS;
}

static int freeContent(argumentInitTemp_t* argument)
{
	int retVal = freeList(argument->listAttackers);
	retVal = retVal || freeList(argument->listVictims);
}

uint32_t** getReduct(argFramework_t* framework, uint32_t** activeArguments, uint32_t argument)
{
	uint32_t** newActives = copyMatrix(activeArguments);
	deactivateArgument(newActives, argument);

	uint32_t* victims = framework->victims[argument];
	for (int i = 0; i < _countof(victims); i++)
	{
		deactivateArgument(newActives, victims[i]);
	}

	return newActives;
}

static int deactivateArgument(uint32_t** activeArguments, uint32_t argument)
{
	activeArguments[activeArguments[argument][0]][1] = activeArguments[argument][1];
	activeArguments[activeArguments[argument][1]][0] = activeArguments[argument][0];
	activeArguments[argument][0] = NULL;
	activeArguments[argument][1] = NULL;

	return EXIT_SUCCESS;
}
