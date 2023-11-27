#include <stdint.h>
#include <stdlib.h>
#include "List.h"


uint32_t countList(nodeInt_t *head)
{
    nodeInt_t *current = head;
     uint32_t count = 1;
    while (current->next != NULL) { // iterate to end of list
        current = current->next;
        count++;
    }

    return count;
}

uint8_t freeList(nodeInt_t *head)
{
    nodeInt_t *current = head;
    nodeInt_t *next = current->next;

    while (next != NULL)
    {
        free(current);
        current = next;
        next = current->next;
    }
    free(current);

    return EXIT_SUCCESS;
}

uint8_t push(nodeInt_t *head, uint32_t number)
{
    nodeInt_t *current = head;
    while (current -> next != NULL) { // iterate to end of list
        current = current -> next;
    }

    nodeInt_t *ptrNode = NULL;
    ptrNode = malloc(sizeof *ptrNode );
    if (ptrNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    else {
        current->next = ptrNode;
        if (current->next == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
        else {
            current = current->next;
            current->number = number;
            current->next = NULL;

            return EXIT_SUCCESS;
        }
    }
}
