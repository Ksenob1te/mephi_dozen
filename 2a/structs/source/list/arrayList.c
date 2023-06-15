#include "arrayList.h"
#include "../../list.h"
#include "stdio.h"

Node * get_tail(List *list) {
    if (!is_empty(list))
        return (list->array)[(list->start + list->counter - 1) % list->max_size];
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
    if (list->counter >= list->max_size) return 1;
    return 0;
}

int is_empty(List *list) {
    if (list->counter == 0) return 1;
    return 0;
}

void printList(List *list, void (*printData)(void *)) {
    if (is_empty(list)) return;
    for (size_t i = list->start; i < (list->counter + list->start); ++i) {
        printData((list->array)[i % list->max_size]->data);
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
    list->counter = 0;
    return list;
}

void clearList(List *list) {
    free(list->array);
    free(list);
}
