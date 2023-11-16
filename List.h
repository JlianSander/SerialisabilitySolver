#include <stdint.h>
#pragma once

typedef struct {
    uint32_t number;
    struct node_t * next;
} nodeInt_t;

int CountList(nodeInt_t* head);
int FreeList(nodeInt_t* head);
int Push(nodeInt_t* head, uint32_t number);
