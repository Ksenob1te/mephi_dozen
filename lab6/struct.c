#include "struct.h"
#include "stdlib.h"

List *initList() {
    List *list = malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void addNext(List *list, char element) {
    Node *node = malloc(sizeof(Node));
    if (!list->head) list->head = node;
    if (list->tail) {
        list->tail->next = node;
    }
    node->next = NULL;
    node->prev = list->tail;
    node->data = element;
    list->tail = node;
}

void swap(Node *node1, Node *node2) {
    char temp = node1->data;
    node1->data = node2->data;
    node2->data = temp;
}

