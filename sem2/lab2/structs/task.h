#ifndef SEM1_LAB4_TASK_H_1
#define SEM1_LAB4_TASK_H_1

#include "stdlib.h"
#include "cycleQueue.h"

typedef struct Passenger {
    char *name;
    size_t arriving;
    size_t waiting;
} Passenger;

typedef struct Terminal {
    Queue *queue;
    size_t current_time;
    size_t next_event;
} Terminal;

#endif //SEM1_LAB4_TASK_H_1
