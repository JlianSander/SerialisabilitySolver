#include <stdlib.h >
#include <stdio.h>
#include <stdint.h>
#include "AF.h"
#include "Reduct.h"
#include "Actives.h"

int main() {
	argumentInitTemp_t* head = setUpInitialization(4);
	addAttack(head, 1, 2);
	addAttack(head, 1, 3);
	//addAttack(head, 3, 1);
	addAttack(head, 4, 1);
	argFramework_t* framework = initializeFramework(head);

	printf("Attackers");
	printMatrix(framework->attackers);
	printf("Victims");
	printMatrix(framework->victims);

	matrix_t *actives = initializeActives(4);
	printf("\n Active Arguments: base");
	printMatrix(actives);

	matrix_t *reduct = getReduct(actives, framework, 2);
	printf("\n Active Arguments: reducted by 2");
	printMatrix(reduct);

	/*matrix_t *reduct2 = getReduct(reduct, framework, 3);
	printf("\n Active Arguments: reducted by 3");
	printMatrix(reduct2);

	matrix_t *reduct3 = getReduct(reduct2, framework, 1);
	printf("\n Active Arguments: reducted by 1");
	printMatrix(reduct3);

	matrix_t *reduct4 = getReduct(reduct3, framework, 4);
	printf("\n Active Arguments: reducted by 4");
	printMatrix(reduct4);*/

	
}