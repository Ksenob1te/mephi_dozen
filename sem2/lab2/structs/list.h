#ifndef MEPHI_DOZEN_LIST_H
#define MEPHI_DOZEN_LIST_H
#include "stdlib.h"

typedef struct Node Node;
typedef struct List List;

void * get_data(Node *node);
int is_last(List *list, Node *node);
int is_full(List *list);
int is_empty(List *list);
void printList(List *list, void (*printData)(void *));
void remove_selected(List *list, Node *element);
void add_next(List *list, Node *base, Node *element);
void add_prev(List *list, Node *base, Node *element);
Node * createNode(void *data, size_t sizeOfData);
List * createList(size_t size);

#endif //MEPHI_DOZEN_LIST_H
