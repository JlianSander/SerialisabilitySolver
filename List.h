#ifndef LIST_H
#define LIST_H

#include <stdint.h>

// This line is necessary to inform the compiler of the type, 
// which allows to recursively call the struct in it's own type definition
typedef struct nodeInt nodeInt_t;
/// <summary>
/// data structure of a simple node, containing a number
/// </summary>
typedef struct nodeInt {
    uint32_t number;
    nodeInt_t* next;
} nodeInt_t;

/// <summary>
/// Counts the elements of a specified list. 
/// </summary>
/// <param name="head">The first element of the list.</param>
/// <returns>Number of elements in the specified list.</returns>
 uint32_t countList(nodeInt_t* head);
 /// <summary>
/// Deallocates the memory space of a specified list. 
/// </summary>
/// <param name="head">The first element of the list.</param>
/// <returns>EXIT_SUCCESS iff the deallocation was successful.</returns>
 uint8_t freeList(nodeInt_t* head);
 /// <summary>
/// Adds a specified number at the end of the list. 
/// </summary>
/// <param name="head">The first element of the list.</param>
/// <param name="number">Number to add.</param>
/// <returns>EXIT_SUCCESS iff the operation was successful.</returns>
 uint8_t push(nodeInt_t* head, uint32_t number);

#endif
