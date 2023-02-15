#include "task.h"
#include "stdio.h"

void joinTerminal(Terminal *terminal, Node *node) {
    Passenger *p = (Passenger *) node->data;
    if (terminal->current_time <= 0) terminal->current_time += p->arriving;
    terminal->current_time += p->waiting;
    Queue *queue = terminal->queue;
    queue->push(queue, node);
    if (queue->get_top(queue) == node) terminal->next_event = p->arriving + p->waiting;
}

Node * leaveTerminal(Terminal *terminal) {
    Queue *queue = terminal->queue;
    Node *node = queue->pop(queue);
    Passenger *p = (Passenger *) queue->get_top(queue);
    if (p) terminal->next_event += p->waiting; else terminal->next_event = -1;
    return node;
}

Terminal * selectTerminal(Terminal **array, int len) {
    if (len <= 0) return NULL;
    Terminal *min = array[0];
    for (int i = 1; i < len; ++i) {
        if (array[i]->current_time < min->current_time) min = array[i];
    }
    return min;
}

void printStatus(Terminal **array, int len) {
    Terminal *t = *array;
    for (int i = 0; i < len; ++i, ++t) {
        List *list = array[i]->queue->list;
        printf("T%d: ", i + 1);
        for (Node *tracker = list->head; tracker; tracker = tracker->next)
            printf("%s ", ((Passenger *) tracker->data)->name);
        printf("\n");
    }
}




