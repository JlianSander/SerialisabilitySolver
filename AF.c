#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "AF.h"
#include "Actives.h"
#include "List.h"
#include "Matrix.h"

static uint8_t goToArgument(argumentInitTemp_t* head, uint32_t argument, argumentInitTemp_t** resultRef)
{
	argumentInitTemp_t* current = head;
	while (current->number != argument) { // iterate to the argument
		current = current->next;

		if (current == NULL) { //argument not found in the list
			return EXIT_FAILURE;
		}
	}
	*resultRef = current;
	return EXIT_SUCCESS;
}

static uint8_t updateVictim(argumentInitTemp_t* head, uint32_t attacker, uint32_t victim)
{
	argumentInitTemp_t** ptrCurrent = malloc(sizeof(argumentInitTemp_t*));
	if (ptrCurrent == NULL) {
		printf("Memory allocation failed\n");
		exit(1);
	}
	else {
		if (goToArgument(head, victim, ptrCurrent) == EXIT_FAILURE)
		{
			return EXIT_FAILURE;
		}
		argumentInitTemp_t* current = *ptrCurrent;
		free(ptrCurrent);

		if (current->listAttackers == NULL) {
			//initialize list of attackers
			current->listAttackers = malloc(sizeof(nodeInt_t));
			if (current->listAttackers == NULL) {
				printf("Memory allocation failed\n");
				exit(1);
			}
			else {

				current->listAttackers->next = NULL;
				current->listAttackers->number = attacker;
			}
		}
		else {
			push(current->listAttackers, attacker);
		}
		return EXIT_SUCCESS;
	}
	
}

static uint8_t updateAttacker(argumentInitTemp_t* head, uint32_t attacker, uint32_t victim)
{
	argumentInitTemp_t** ptrCurrent = malloc(sizeof(argumentInitTemp_t*));
	if (ptrCurrent == NULL) {
		printf("Memory allocation failed\n");
		exit(1);
	}
	else {
		if (goToArgument(head, attacker, ptrCurrent) == EXIT_FAILURE) {
			return EXIT_FAILURE;
		}
		argumentInitTemp_t* current = *ptrCurrent;
		free(ptrCurrent);

		if (current->listVictims == NULL) {
			//initialize list of victims
			current->listVictims = malloc(sizeof(nodeInt_t));
			if (current->listVictims == NULL) {
				printf("Memory allocation failed\n");
				exit(1);
			}
			else {
				current->listVictims->next = NULL;
				current->listVictims->number = victim;
			}
		}
		else {
			push(current->listVictims, victim);
		}
		return EXIT_SUCCESS;
	}
}

uint8_t addAttack(argumentInitTemp_t* head,  uint32_t attacker,  uint32_t victim) {
	uint8_t retVal = updateAttacker(head, attacker, victim);
	retVal = retVal || updateVictim(head, attacker, victim);
	return retVal;
}

static uint32_t countArguments(argumentInitTemp_t* head)
{
	argumentInitTemp_t* current = head;
	uint32_t count = 1;
	while (current->next != NULL) { // iterate to end of list
		current = current->next;
		count++;
	}

	return count;
}

static uint32_t** initializeAttackers(argumentInitTemp_t* head, uint32_t numberOfArguments)
{
	argumentInitTemp_t* current = head;
	uint32_t** matrix = createRows(numberOfArguments);

	for (uint32_t i = 0; i < numberOfArguments; i++)
	{
		uint32_t numArgs = countList(current->listAttackers);
		matrix[i] = createOneRow(numArgs);
		nodeInt_t* currentAttacker = current->listAttackers;
		for (uint32_t j = 0; j < numArgs; j++)
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

	for (uint32_t i = 0; i < numberOfArguments; i++)
	{
		uint32_t numArgs = countList(current->listVictims);
		matrix[i] = createOneRow(numArgs);
		nodeInt_t* currentVictim = current->listVictims;
		for (uint32_t j = 0; j < numArgs; j++)
		{
			matrix[i][j] = currentVictim->number;

			currentVictim = currentVictim->next;
		}

		current = current->next;
	}

	return matrix;
}

static uint32_t freeContent(argumentInitTemp_t* argument)
{
	uint32_t retVal = freeList(argument->listAttackers);
	retVal = retVal || freeList(argument->listVictims);
	return EXIT_SUCCESS;
}

static  uint32_t freeInitializationMemory(argumentInitTemp_t* head)
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

argFramework_t* initializeFramework(argumentInitTemp_t* head)
{
	argFramework_t* framework = malloc(sizeof(argFramework_t));
	if (framework == NULL) {
		printf("Memory allocation failed\n");
		exit(1);
	}
	else {
		framework->number = countArguments(head);
		framework->attackers = initializeAttackers(head, framework->number);
		framework->victims = initializeVictims(head, framework->number);
		freeInitializationMemory(head);

		return framework;
	}
}

static argumentInitTemp_t* addArgument(argumentInitTemp_t* predecessor, uint32_t argument) {
	argumentInitTemp_t* current = predecessor;

	//create new argument
	current->next = malloc(sizeof(argumentInitTemp_t));
	if (current->next == NULL) {
		printf("Memory allocation failed\n");
		exit(1);
	}
	else {
		current = current->next;

		//initialize argument
		current->next = NULL;
		current->number = argument;
		current->listAttackers = NULL;
		current->listVictims = NULL;

		return current;
	}
}

argumentInitTemp_t* setUpInitialization(uint32_t numberArguments)
{
	uint32_t firstArgument = 1;
	argumentInitTemp_t* head = malloc(sizeof(argumentInitTemp_t));
	if (head == NULL) {
		printf("Memory allocation failed\n");
		exit(1);
	}
	else {
		//initialize argument
		head->next = NULL;
		head->number = firstArgument;
		head->listAttackers = NULL;
		head->listVictims = NULL;

		argumentInitTemp_t* current = head;
		for (uint32_t i = 2; i < numberArguments; i++)
		{
			current = addArgument(current, i);
		}

		return head;
	}
}