#include <stdint.h>
#include "List.h"
#pragma once

typedef struct {
    //datamodel of the framework
    uint32_t number;
    uint32_t** attackers; // 2D-matrix containing the index of arguments, not sorted
    uint32_t** victims; // 2D-matrix containing the index of arguments, not sorted
} argFramework_t;

typedef struct {
    //structure used during initialization to keep track of all attacks, 
    // which will be read one after the other from the input-file
    uint32_t number;
    nodeInt_t* listAttackers;
    nodeInt_t* listVictims;
    argumentInitTemp_t* next;
} argumentInitTemp_t;

uint32_t addAttack(argumentInitTemp_t* head,  uint32_t attacker,  uint32_t victim);
argFramework_t* initializeFramework(argumentInitTemp_t* head, uint32_t numberOfArguments);
argumentInitTemp_t* setUpInitialization(uint32_t firstArgument);

