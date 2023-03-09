#include "../../list.h"
#include "cycleList.h"

Node * get_head(List *list) {
    if (!list) return NULL;
    if (list->tail)
        return list->tail->next;
    else
        return list->tail;
}

Node * get_tail(List *list) {
    if (!list) return NULL;
    return list->tail;
}


Node * get_next(Node *node) {
    if (!node) return NULL;
    return node->next;
}

void * get_data(Node *node) {
    if (!node) return NULL;
    return node->data;
}

void set_next(Node *start, Node *node) {
    if (!start) return;
    start->next = node;
}

void set_tail(List *list, Node *node) {
    if (!list) return;
    list->tail = node;
}

int is_last(List *list, Node *node) {
    if (!list) return 0;
    if (list->tail == node) return 1;
    return 0;
}

Node * createNode(void *data, size_t sizeOfData) {
    Node *node = malloc(sizeof(struct Node));
    node->next = NULL;
    node->data = data;
    node->sizeOfData = sizeOfData;
    return node;
}

List * createList() {
    List *list = malloc(sizeof(List));
    list->tail = NULL;
    return list;
}
