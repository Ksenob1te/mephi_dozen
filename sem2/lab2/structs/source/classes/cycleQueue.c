#include "../../structs.h"
#include "../list/cycleList.h"


// Queue struct methods
// ===============================
Queue * createQueue(size_t size) {
    Queue *queue = malloc(sizeof(Queue));
    queue->list = createList(size);
    queue->get_top = get_top_queue;
    queue->pop = pop_queue;
    queue->push = push_queue;
    return queue;
}

Node * get_top_queue(Queue *queue) {
    List *list = queue->list;
    if (!list) return NULL;
    Node *tail = list->tail;
    if (tail) return tail->next;
    return tail;
}

int push_queue(Queue *queue, Node *node) {
    List *list = queue->list;
    if (!list) return 0;
    Node *tail = list->tail;
    if (!tail) {
        list->tail = node;
        node->next = node;
    } else {
        node->next = tail->next;
        tail->next = node;
        list->tail = node;
    }
    return 1;
}

Node * pop_queue(Queue *queue) {
    List *list = queue->list;
    if (!list) return NULL;
    Node *tail = list->tail;
    if (!tail) return NULL;

    Node *head = tail->next;
    if (head == tail) {list->tail = NULL; return tail;}

    tail->next = head->next;
    return head;
}
// ===============================
