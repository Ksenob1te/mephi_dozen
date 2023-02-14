//
// Created by Ksenob1te on 14.02.2023.
//

#include "list.h"

void remove_selected(List *list, Node *element) {
    if (!element) return;
    if (list->head == element) list->head = element->next;
    if (list->tail == element) list->tail = element->prev;

    if (element->prev) element->prev->next = element->next;
    if (element->next) element->next->prev = element->prev;
    element->prev = NULL;
    element->next = NULL;
}

void add_tail(List *list, Node *element) {
    if (!list->head) list->head = element;
    if (list->tail) {
        list->tail->next = element;
        element->prev = list->tail;
    }
    list->tail = element;
    element->next = NULL;
}

void add_next(List *list, Node *base, Node *element) {
    if (!base)  {add_tail(list, element); return;}
    if (list->tail == base) list->tail = element;
    element->prev = base;
    element->next = base->next;
    if (base->next) base->next->prev = element;
    base->next = element;
}

void add_prev(List *list, Node *base, Node *element) {
    if (!base)  {add_tail(list, element); return;}
    if (list->head == base) list->head = element;
    element->next = base;
    element->prev = base->prev;
    if (base->prev) base->prev->next = element;
    base->prev = element;
}

Node * createNode(void *data, size_t sizeOfData) {
    Node *node = malloc(sizeof(struct Node));
    node->next = NULL;
    node->prev = NULL;
    node->data = data;
    node->sizeOfData = sizeOfData;
    return node;
}

List * createList() {
    List *list = malloc(sizeof(struct List));
    list->head = NULL;
    list->tail = NULL;
    list->remove = remove_selected;
    list->add_next = add_next;
    list->add_prev = add_prev;
    return list;
}
