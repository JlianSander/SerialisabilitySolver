#ifndef LIST_H
#define LIST_H

#include <stdint.h>

// This line is necessary to inform the compiler of the type, 
// which allows to recursively call the struct in it's own type definition
typedef struct nodeInt nodeInt_t;
/// <summary>
/// Data structure of a list, with each node containing a number
/// </summary>
typedef struct nodeInt {
    uint32_t number;
    nodeInt_t* next;
} nodeInt_t;

/// <summary>
/// Data structure of a list, with each node containing a list of integers
/// </summary>
typedef struct listInt listInt_t;
typedef struct listInt {
    nodeInt_t *element;
    listInt_t *next;
} listInt_t;

/// <summary>
/// Counts the nodes of a specified list. 
/// </summary>
/// <param name="head">The first node of the list.</param>
/// <returns>Number of nodes in the specified list.</returns>
 uint32_t count_list(nodeInt_t* head);
 /// <summary>
/// Deallocates the memory space of a specified list. 
/// </summary>
/// <param name="head">The first node of the list.</param>
/// <returns>EXIT_SUCCESS iff the deallocation was successful.</returns>
 uint8_t free_list(nodeInt_t* head);
 /// <summary>
/// Deallocates the memory space of a specified list. 
/// </summary>
/// <param name="head">The first node of the list.</param>
/// <returns>EXIT_SUCCESS iff the deallocation was successful.</returns>
 uint8_t free_list_of_list(listInt_t *head);
 /// <summary>
/// Adds a specified number at the end of the list. 
/// </summary>
/// <param name="head">The first node of the list.</param>
/// <param name="number">Number to add.</param>
/// <returns>EXIT_SUCCESS iff the operation was successful.</returns>
 uint8_t push(nodeInt_t* head, uint32_t number);
 /// <summary>
 /// Adds a specified element at the end of the list
 /// </summary>
 /// <param name="head">The first node of the list.</param>
/// <param name="number">Element to add.</param>
/// <returns>EXIT_SUCCESS iff the operation was successful.</returns>
 uint8_t push_list(listInt_t *head, nodeInt_t *element);

#endif
