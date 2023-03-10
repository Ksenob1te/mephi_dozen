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
    if (!is_empty(queue->list))
        return *(queue->list->array);
    return NULL;
}

int push_queue(Queue *queue, Node *node) {
    List *list = queue->list;
    if (!is_full(list)) {
        list->array[(list->end + list->max_size - 1) % list->max_size] = node;
        list->end = (list->end + 1) % list->max_size;
        return 1;
    }
    return 0;
}

Node * pop_queue(Queue *queue) {
    List *list = queue->list;
    if (!is_empty(list)) {
        Node *node = list->array[list->start];
        list->start = (list->start + 1) % list->max_size;
        return node;
    }
    return NULL;
}
