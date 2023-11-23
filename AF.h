#ifndef AF_H
#define AF_H

#include <stdint.h>
#include "List.h"

typedef struct argumentInitTemp argumentInitTemp_t;
typedef struct argumentInitTemp {
    //structure used during initialization to keep track of all attacks, 
    // which will be read one after the other from the input-file
    uint32_t number;
    nodeInt_t* listAttackers;
    nodeInt_t* listVictims;
    argumentInitTemp_t* next;
} argumentInitTemp_t;

typedef struct argFramework {
    //datamodel of the framework
    uint32_t number;
    matrix_t* attackers; // 2D-matrix containing the index of arguments
    matrix_t* victims; // 2D-matrix containing the index of arguments
} argFramework_t;

uint8_t addAttack(argumentInitTemp_t* head,  uint32_t attacker,  uint32_t victim);
argFramework_t* initializeFramework(argumentInitTemp_t* head);
argumentInitTemp_t* setUpInitialization(uint32_t numberArguments);

#endif

