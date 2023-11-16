#include <stdint.h>
#include "List.h"
#pragma once

typedef struct {
    //datamodel of the framework, which is created once after the initialization and will not be changed afterwards
    //this datamodel is used in every parallel process to determine the initial sets
    uint32_t number;
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

argumentInitTemp_t* setUpInitialization(int firstArgument);
int addArgument(argumentInitTemp_t* head, int argument);
int addAttack(argumentInitTemp_t* head, int attacker, int victim);

uint32_t** initializeActives(uint32_t numberOfArguments);
argFramework_t* initializeFramework(argumentInitTemp_t* head, uint32_t numberOfArguments);

uint32_t** getReduct(argFramework_t* framework, uint32_t** activeArguments, uint32_t argument); //returns the matix framework.actives for the reducted framework