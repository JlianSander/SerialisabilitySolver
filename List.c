#include <stdint.h>
#include <stdlib.h>
#include "List.h"

int countList(nodeInt_t* head)
{
    nodeInt_t* current = head;
    int count = 1;
    while (current->next != NULL) { // iterate to end of list
        current = current->next;
        count++;
    }

    return count;
}

int freeList(nodeInt_t* head)
{
    nodeInt_t* current = head;
    nodeInt_t* next = current->next;

    while (next != NULL)
    {
        free(current);
        current = next;
        next = current->next;
    }
    free(current);

    return EXIT_SUCCESS;
}

int push(nodeInt_t* head, uint32_t number) {
    nodeInt_t * current = head;
    while (current -> next != NULL) { // iterate to end of list
        current = current -> next;
    }

    current->next = (nodeInt_t*)malloc(sizeof(nodeInt_t));
    current = current->next;
    current->number = number;
    current->next = NULL;

    return EXIT_SUCCESS;
}
