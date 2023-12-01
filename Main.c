#include <stdlib.h >
#include <stdio.h>
#include <stdint.h>
#include "AF.h"
#include "Reduct.h"
#include "Actives.h"

int main() {
	argumentInitTemp_t* head = set_up_initialization(4);
	add_attack(head, 1, 2);
	add_attack(head, 1, 3);
	//addAttack(head, 3, 1);
	add_attack(head, 4, 1);
	argFramework_t* framework = initialize_framework(head);

	printf("Attackers");
	print_matrix(framework->attackers);
	printf("Victims");
	print_matrix(framework->victims);

	matrix_t *actives = initialize_actives(4);
	printf("\n Active Arguments: base");
	print_matrix(actives);

	matrix_t *reduct = get_reduct(actives, framework, 2);
	printf("\n Active Arguments: reducted by 2");
	print_matrix(reduct);

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