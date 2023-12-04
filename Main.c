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
	//add_attack(head, 3, 1);
	add_attack(head, 4, 1);
	argFramework_t* framework = initialize_framework(head);

	printf("Attackers");
	print_matrix(framework->attackers);
	printf("Victims");
	print_matrix(framework->victims);

	activeArgs_t *actives = initialize_actives(4);
	printf("\n Active Arguments: base");
	print_active_arguments(actives);

	activeArgs_t *reduct = get_reduct(actives, framework, 2);
	printf("\n Active Arguments: reducted by 2");
	print_active_arguments(reduct);

	activeArgs_t *reduct2 = get_reduct(reduct, framework, 3);
	printf("\n Active Arguments: reducted by 3");
	print_active_arguments(reduct2);
	/*
	activeArgs_t *reduct3 = get_reduct(reduct2, framework, 1);
	printf("\n Active Arguments: reducted by 1");
	print_active_arguments(reduct3);

	activeArgs_t *reduct4 = get_reduct(reduct3, framework, 4);
	printf("\n Active Arguments: reducted by 4");
	print_active_arguments(reduct4);*/

	
}