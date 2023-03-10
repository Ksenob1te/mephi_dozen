#ifndef MEPHI_DOZEN_DOUBLELIST_H
#define MEPHI_DOZEN_DOUBLELIST_H
#include "stdlib.h"

struct Node {
    void *data;
    size_t sizeOfData;
    struct Node *next;
    struct Node *prev;
};

struct List {
    struct Node *head;
    struct Node *tail;

    void (*remove) (struct List *list, struct Node *element);
    void (*add_next)(struct List *list, struct Node *base, struct Node *element);
    void (*add_prev)(struct List *list, struct Node *base, struct Node *element);
};

#endif //MEPHI_DOZEN_DOUBLELIST_H
