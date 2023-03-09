#ifndef MEPHI_DOZEN_DOUBLELIST_H
#define MEPHI_DOZEN_DOUBLELIST_H

struct Node {
    void *data;
    size_t sizeOfData;
    struct Node *next;
    struct Node *prev;
};

struct List {
    Node *head;
    Node *tail;

    void (*remove) (struct List *list, Node *element);
    void (*add_next)(struct List *list, Node *base, Node *element);
    void (*add_prev)(struct List *list, Node *base, Node *element);
};

#endif //MEPHI_DOZEN_DOUBLELIST_H
