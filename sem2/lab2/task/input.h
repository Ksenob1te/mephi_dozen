#ifndef SEM1_LAB4_INPUT_H
#define SEM1_LAB4_INPUT_H
#include "stdlib.h"
#include "../structs/structs.h"

typedef struct Passenger {
    char *name;
    size_t arriving;
    size_t waiting;
} Passenger;

Queue * input_array();
#endif //SEM1_LAB4_INPUT_H
