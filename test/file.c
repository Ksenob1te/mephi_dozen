#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "time.h"

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

void remove_next(Node *node) {
    Node *remove = node->next;
    node->next = remove->next;
    free(remove);
}

void process(List *list) {
    Node *cur = list->head;

    Node *tail;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    tail = cur;
    while (list->head->data == tail->data) {
        list->head = list->head->next;
    }
    cur = list->head;
    while (cur != NULL && cur->next != NULL) {
        if (cur->next->data == tail->data) remove_next(cur);
        else cur = cur->next;
    }
}

int main() {
    List list;
    srand(time(NULL));
    Node *p = malloc(sizeof(Node));
    p->data = rand() % 3;
    p->next = NULL;
    list.head = p;
    for (int i = 2; i < 10; i ++) {
        Node *node = malloc(sizeof(Node));
        node->data = rand() % 3;
        node->next = NULL;
        p->next = node;
        p = node;
    }
    Node *node = list.head;
    for (int i = 0; node->next != NULL; ++i) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("%d\n", node->data);
    process(&list);

    node = list.head;
    for (int i = 0; node->next != NULL; ++i) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("%d", node->data);
}