#ifndef SEM1_LAB4_CYCLEQUEUE_H
#define SEM1_LAB4_CYCLEQUEUE_H
#include "stdlib.h"

// List struct
// ===============================
typedef struct Node {
    void *data;
    size_t sizeOfData;
    struct Node *next;
} Node;


typedef struct List {
    Node *tail;
} List;

Node * ccreateNode(void *data, size_t sizeOfData);
List * ccreateList();
// ===============================

// Queue struct
// ===============================
typedef struct Queue {
    List *list;
    Node * (*get_top)(struct Queue *queue);
    void (*push)(struct Queue *queue, Node *node);
    Node * (*pop)(struct Queue *queue);
} Queue;

Queue* ccreateQueue();
Node * cget_top_queue (Queue *queue);
void cpush_queue(Queue *queue, Node *node);
Node * cpop_queue(Queue *queue);
// ===============================




#endif //SEM1_LAB4_CYCLEQUEUE_H
