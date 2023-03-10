#include "../../list.h"
#include "cycleList.h"

void * get_data(Node *node) {
    if (!node) return NULL;
    return node->data;
}

int is_last(List *list, Node *node) {
    if (!list) return 0;
    if (list->tail == node) return 1;
    return 0;
}

void printList(List *list, void (*printData)(void *)) {
    if (!list) return;
    if (!list->tail) return;
    for (Node *tracker = list->tail->next; tracker; tracker = tracker->next) {
        printData(tracker->data);
        if (is_last(list, tracker)) break;
    }
}

Node * createNode(void *data, size_t sizeOfData) {
    Node *node = malloc(sizeof(struct Node));
    node->next = NULL;
    node->data = data;
    node->sizeOfData = sizeOfData;
    return node;
}

List * createList(size_t size) {
    List *list = malloc(sizeof(List));
    list->tail = NULL;
    return list;
}
