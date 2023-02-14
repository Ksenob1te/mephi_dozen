#ifndef SEM1_LAB4_LIST_H
#define SEM1_LAB4_LIST_H
#include "stdlib.h"

typedef struct Node {
    void *data;
    size_t sizeOfData;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct List {
    Node *head;
    Node *tail;

    void (*remove) (struct List *list, Node *element);
    void (*add_next)(struct List *list, Node *base, Node *element);
    void (*add_prev)(struct List *list, Node *base, Node *element);
    } List;

void remove(List *list, Node *element);
void add(List *list, Node *element);
void add_next(List *list, Node *base, Node *element);
void add_prev(List *list, Node *base, Node *element);
Node * createNode(void *data, size_t sizeOfData);
List * createList();

#endif //SEM1_LAB4_LIST_H
