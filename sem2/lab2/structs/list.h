#ifndef MEPHI_DOZEN_LIST_H
#define MEPHI_DOZEN_LIST_H
#include "stdlib.h"

typedef struct Node Node;
typedef struct List List;

Node * get_head(List *list);
Node * get_tail(List *list);
Node * get_next(Node *node);
void * get_data(Node *node);
void set_next(Node *start, Node *node);
void set_tail(List *list, Node *node);
int is_last(List *list, Node *node);
void remove_selected(List *list, Node *element);
void add_next(List *list, Node *base, Node *element);
void add_prev(List *list, Node *base, Node *element);
Node * createNode(void *data, size_t sizeOfData);
List * createList();

#endif //MEPHI_DOZEN_LIST_H
