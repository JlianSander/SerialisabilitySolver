#include <stdlib.h >
#include <stdio.h>
#include <stdint.h>
#include "AF.h"
#include "Reduct.h"

int main() {
	argumentInitTemp_t* head = setUpInitialization(4);
	addAttack(head, 1, 2);
	addAttack(head, 1, 3);
	addAttack(head, 3, 1);
	addAttack(head, 4, 1);
	argFramework_t* framework = initializeFramework(head);

	printf("Attackers");
	printMatrix(framework->attackers);
	printf("Victims");
	printMatrix(framework->victims);
	//printf("Number of Arguments: %d", framework->number);
}