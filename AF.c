#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "AF.h"
#include "Actives.h"
#include "List.h"
#include "Matrix.h"
#include "LinkedSparseMatrix.h"

static uint8_t goToArgument(argumentInitTemp_t *head, uint32_t argument, argumentInitTemp_t **resultByRef)
{
	argumentInitTemp_t *current = head;
	while (current->number != argument) { // iterate to the argument
		current = current->next;

		if (current == NULL) { //argument not found in the list
			return EXIT_FAILURE;
		}
	}
	*resultByRef = current;
	return EXIT_SUCCESS;
}

static uint8_t updateVictim(argumentInitTemp_t *head, uint32_t attacker, uint32_t victim)
{
	argumentInitTemp_t **ptrCurrent = NULL;
	ptrCurrent = malloc( sizeof *ptrCurrent );
	if (ptrCurrent == NULL) {
		printf("Memory allocation failed\n");
		exit(1);
	}
	else {
		if (goToArgument(head, victim, ptrCurrent) == EXIT_FAILURE)
		{
			return EXIT_FAILURE;
		}
		argumentInitTemp_t *current = *ptrCurrent;
		free(ptrCurrent);

		if (current->listAttackers == NULL) {
			//initialize list of attackers
			nodeInt_t *firstAttacker = NULL;
			firstAttacker = malloc( sizeof *firstAttacker );
			if (firstAttacker == NULL) {
				printf("Memory allocation failed\n");
				exit(1);
			}
			else {
				firstAttacker->next = NULL;
				firstAttacker->number = attacker;
				current->listAttackers = firstAttacker;
			}
		}
		else {
			push(current->listAttackers, attacker);
		}
		return EXIT_SUCCESS;
	}
	
}

static uint8_t updateAttacker(argumentInitTemp_t *head, uint32_t attacker, uint32_t victim)
{
	argumentInitTemp_t **ptrCurrent = NULL;
	ptrCurrent = malloc( sizeof *ptrCurrent );
	if (ptrCurrent == NULL) {
		printf("Memory allocation failed\n");
		exit(1);
	}
	else {
		if (goToArgument(head, attacker, ptrCurrent) == EXIT_FAILURE) {
			return EXIT_FAILURE;
		}
		argumentInitTemp_t *current = *ptrCurrent;
		free(ptrCurrent);

		if (current->listVictims == NULL) {
			//initialize list of victims
			nodeInt_t *firstVictim = NULL;
			firstVictim = malloc(sizeof *firstVictim);
			if (firstVictim == NULL) {
				printf("Memory allocation failed\n");
				exit(1);
			}
			else {
				firstVictim->next = NULL;
				firstVictim->number = victim;
				current->listVictims = firstVictim;
			}
		}
		else {
			push(current->listVictims, victim);
		}
		return EXIT_SUCCESS;
	}
}

uint8_t add_attack(argumentInitTemp_t *head, uint32_t attacker, uint32_t victim) {
	uint8_t retVal = updateAttacker(head, attacker, victim);
	retVal = retVal || updateVictim(head, attacker, victim);
	return retVal;
}

static uint32_t countArguments(argumentInitTemp_t *head)
{
	argumentInitTemp_t *current = head;
	uint32_t count = 1;
	while (current->next != NULL) { // iterate to end of list
		current = current->next;
		count++;
	}

	return count;
}

static matrix_t* initializeAttackers(argumentInitTemp_t *head, uint32_t numberOfArguments)
{
	argumentInitTemp_t *current = head;
	matrix_t *matrix = create_linked_sparse_matrix(numberOfArguments, numberOfArguments);

	while(current != NULL)
	{
		nodeInt_t *currentAttacker = current->listAttackers;
		while(currentAttacker != NULL)
		{
			set_cell(matrix, current->number, currentAttacker->number);
			currentAttacker = currentAttacker->next;
		}

		current = current->next;
	}

	return matrix;
}

static matrix_t* initializeVictims(argumentInitTemp_t *head, uint32_t numberOfArguments) {
	argumentInitTemp_t *current = head;
	matrix_t *matrix = create_linked_sparse_matrix(numberOfArguments, numberOfArguments);

	while (current != NULL)
	{
		nodeInt_t *currentVictim = current->listVictims;

		while (currentVictim != NULL)
		{
			set_cell(matrix, current->number, currentVictim->number);
			currentVictim = currentVictim->next;
		}

		current = current->next;
	}

	return matrix;
}

static uint8_t freeContent(argumentInitTemp_t *argument)
{
	uint8_t retVal = EXIT_SUCCESS;
	if (argument->listAttackers != NULL) {
		retVal = free_list(argument->listAttackers);
	}

	if (argument->listVictims != NULL) {
		retVal = retVal || free_list(argument->listVictims);
	}

	return retVal;
}

static  uint32_t freeInitializationMemory(argumentInitTemp_t *head)
{
	argumentInitTemp_t *current = head;
	if (current == NULL) {
		return EXIT_SUCCESS;
	}
	else {
		argumentInitTemp_t *next = current->next;

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
}

argFramework_t* initialize_framework(argumentInitTemp_t *head)
{
	argFramework_t *framework = NULL;
	framework = malloc(sizeof *framework);
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

static argumentInitTemp_t* addArgument(argumentInitTemp_t *predecessor, uint32_t argument) 
{
	//create new argument
	argumentInitTemp_t *current = NULL;
	current = malloc(sizeof *current);
	if (current == NULL) {
		printf("Memory allocation failed\n");
		exit(1);
	}
	else {
		//initialize argument
		current->next = NULL;
		current->number = argument;
		current->listAttackers = NULL;
		current->listVictims = NULL;

		predecessor->next = current;

		return current;
	}
}

argumentInitTemp_t* set_up_initialization(uint32_t numberArguments)
{
	uint32_t firstArgument = 1;
	argumentInitTemp_t *head = NULL;
	head = malloc(sizeof *head);
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

		argumentInitTemp_t *current = head;
		for (uint32_t i = 2; i <= numberArguments; i++)
		{
			current = addArgument(current, i);
		}

		return head;
	}
}