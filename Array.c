#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "Array.h"

static uint32_t* create_elements(uint32_t length)
{
	uint32_t *elements = NULL;
	elements = calloc(length, sizeof * elements);
	if (elements == NULL) {
		printf("Memory allocation failed\n");
		exit(1);
	}
	else {
		return elements;
	}
}

uint32_t *copy_array(uint32_t *original, uint32_t length)
{
	
}
