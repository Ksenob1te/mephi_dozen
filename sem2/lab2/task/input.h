#ifndef SEM1_LAB4_INPUT_H
#define SEM1_LAB4_INPUT_H
#include "stdlib.h"

typedef struct Passenger {
    char *name;
    size_t arriving;
    size_t waiting;
} Passenger;

Passenger ** input_array(int *array_sizes);
#endif //SEM1_LAB4_INPUT_H
