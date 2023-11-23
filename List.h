#ifndef LIST_H
#define LIST_H

#include <stdint.h>

typedef struct nodeInt nodeInt_t;
typedef struct nodeInt {
    uint32_t number;
    nodeInt_t* next;
} nodeInt_t;

 uint32_t countList(nodeInt_t* head);
 uint32_t freeList(nodeInt_t* head);
 uint32_t push(nodeInt_t* head, uint32_t number);

#endif
