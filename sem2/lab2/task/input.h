#ifndef SEM1_LAB4_INPUT_H
#define SEM1_LAB4_INPUT_H
#include "stdlib.h"

typedef struct Passenger {
    char *name;
    size_t arriving;
    size_t waiting;
} Passenger;

void input_array();
#endif //SEM1_LAB4_INPUT_H
