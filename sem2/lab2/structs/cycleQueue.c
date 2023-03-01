//
// Created by Ksenob1te on 22.02.2023.
//

#include "cycleQueue.h"

// List struct methods
// ===============================
Node * ccreateNode(void *data, size_t sizeOfData) {
    Node *node = malloc(sizeof(struct Node));
    node->next = NULL;
    node->data = data;
    node->sizeOfData = sizeOfData;
    return node;
}

List * ccreateList() {
    List *list = malloc(sizeof(List));
    list->tail = NULL;
    return list;
}
// ===============================

// Queue struct methods
// ===============================
Queue * ccreateQueue() {
    Queue *queue = malloc(sizeof(Queue));
    queue->list = ccreateList();
    queue->get_top = cget_top_queue;
    queue->pop = cpop_queue;
    queue->push = cpush_queue;
    return queue;
}

Node * cget_top_queue(Queue *queue) {
    Node *tail = queue->list->tail;
    if (tail) return queue->list->tail->next;
    return tail;
}

void cpush_queue(Queue *queue, Node *node) {
    List *list = queue->list;
    Node *tail = list->tail;
    if (!tail) {
        list->tail = node;
        node->next = node;
    } else {
        node->next = tail->next;
        tail->next = node;
        list->tail = node;
    }
}

Node * cpop_queue(Queue *queue) {
    List *list = queue->list;
    Node *tail = list->tail;
    if (!tail) return NULL;

    Node *head = tail->next;
    if (head == tail) {list->tail = NULL; return tail;}

    tail->next = head->next;
    return head;
}
// ===============================
