#ifndef ARRAY_H
#define ARRAY_H

typedef struct arrayInt {
    uint32_t length;
    uint32_t *elements;
} arrayInt_t;

arrayInt_t *create_array(uint32_t length);

arrayInt_t *copy_array(arrayInt_t *original);

uint8_t free_array(arrayInt_t *array);

void print_array(arrayInt_t *array);

#endif
