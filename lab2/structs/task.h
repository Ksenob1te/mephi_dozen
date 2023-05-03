#ifndef SEM1_LAB4_TASK_H_1
#define SEM1_LAB4_TASK_H_1

#include "stdlib.h"
#include "structs.h"

typedef struct Passenger {
    char *name;
    long arriving;
    long waiting;
} Passenger;

typedef struct Terminal {
    Queue *queue;
    size_t current_time;
    long long int next_event;
} Terminal;

#endif //SEM1_LAB4_TASK_H_1
