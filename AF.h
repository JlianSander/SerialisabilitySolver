#include <stdint.h>
#include "List.h"
#pragma once

typedef struct {
    //datamodel of the framework
    uint32_t number;
    uint32_t** actives;
    uint32_t** attackers;
    uint32_t** victims;
} argFramework_t;

typedef struct {
    //structure used during initialization to keep track of all arguments and their attackers and victims, 
    // which will be read one after the other from the input-file
    uint32_t number;
    nodeInt_t* listAttackers;
    nodeInt_t* listVictims;
    argumentInitTemp_t* next;
} argumentInitTemp_t;

argumentInitTemp_t* setUpInitialization( uint32_t firstArgument);
 uint32_t addArgument(argumentInitTemp_t* head,  uint32_t argument);
 uint32_t addAttack(argumentInitTemp_t* head,  uint32_t attacker,  uint32_t victim);

argFramework_t* initializeFramework(argumentInitTemp_t* head, uint32_t numberOfArguments);

uint32_t getNext(uint32_t** activeArguments, uint32_t argument); // returns the active argument, which is located before the one specified
uint32_t getPredecessor(uint32_t** activeArguments, uint32_t argument); // returns the next active argument after the one specified

 uint32_t isActive(uint32_t** activeArguments, uint32_t argument); // returns 1 iff specified argument is active; returns 0 otherwise