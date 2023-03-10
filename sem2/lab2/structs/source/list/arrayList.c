#include "arrayList.h"
#include "../../list.h"
#include "stdio.h"

Node * get_tail(List *list) {
    if (!is_empty(list))
        return (list->array)[(list->end + list->max_size - 1) % list->max_size];
    return NULL;
}

void * get_data(Node *node) {
    return node->data;
}

int is_last(List *list, Node *node) {
    if (get_tail(list) == node) return 1;
    return 0;
}

int is_full(List *list) {
    if (list->start == list->end) {return 1;}
    return 0;
}

int is_empty(List *list) {
    if (list->start + 1 == list->end) {return 1;}
    return 0;
}

void printList(List *list, void (*printData)(void *)) {
    if (!is_empty(list)) return;
    for (Node **tracker = list->array; *tracker; ++tracker) {
        printData((*tracker)->data);
        if (is_last(list, (*tracker))) break;
    }
}

Node * createNode(void *data, size_t sizeOfData) {
    Node *node = malloc(sizeof(struct Node));
    node->data = data;
    node->sizeOfData = sizeOfData;
    return node;
}

List * createList(size_t size) {
    List *list = malloc(sizeof(List));
    list->array = malloc(sizeof(Node *) * size);
    list->max_size = size;
    list->start = 0;
    list->end = 1;
    return list;
}
