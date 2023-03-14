#include "../../structs.h"
#include "../list/arrayList.h"

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
    if (!is_empty(list))
        return (list->array)[list->start];
    return NULL;
}

int push_queue(Queue *queue, Node *node) {
    List *list = queue->list;
    if (!is_full(list)) {
        list->array[(list->start + list->counter) % list->max_size] = node;
        (list->counter)++;
        return 1;
    }
    return 0;
}

Node * pop_queue(Queue *queue) {
    List *list = queue->list;
    if (!is_empty(list)) {
        Node *node = list->array[list->start];
        list->start = (list->start + 1) % list->max_size;
        (list->counter)--;
        return node;
    }
    return NULL;
}
