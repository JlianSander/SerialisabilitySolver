#include <stdint.h>
#pragma once

typedef struct {
    uint32_t number;
    struct node_t * next;
} nodeInt_t;

 uint32_t countList(nodeInt_t* head);
 uint32_t freeList(nodeInt_t* head);
 uint32_t push(nodeInt_t* head, uint32_t number);
