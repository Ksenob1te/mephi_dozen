#include "../../structs.h"


// Queue struct methods
// ===============================
Queue * createQueue() {
    Queue *queue = malloc(sizeof(Queue));
    queue->list = createList();
    queue->get_top = get_top_queue;
    queue->pop = pop_queue;
    queue->push = push_queue;
    queue->is_full = is_full_queue;
    return queue;
}

int is_full_queue(Queue *queue) {
    return 0;
}

Node * get_top_queue(Queue *queue) {
    Node *tail = get_tail(queue->list);
    if (tail) return get_next(get_tail(queue->list));
    return tail;
}

void push_queue(Queue *queue, Node *node) {
    List *list = queue->list;
    Node *tail = get_tail(list);
    if (!tail) {
        set_tail(list, node);
        set_next(node, node);
    } else {
        set_next(node, get_next(tail));
        set_next(tail, node);
        set_tail(list, node);
    }
}

Node * pop_queue(Queue *queue) {
    List *list = queue->list;
    Node *tail = get_tail(list);
    if (!tail) return NULL;

    Node *head = get_next(tail);
    if (head == tail) { set_tail(list, NULL); return tail;}

    set_next(tail, get_next(head));
    return head;
}
// ===============================
