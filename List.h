#include <stdint.h>
#pragma once

typedef struct {
    uint32_t number;
    struct node_t * next;
} nodeInt_t;

int countList(nodeInt_t* head);
int freeList(nodeInt_t* head);
int push(nodeInt_t* head, uint32_t number);
