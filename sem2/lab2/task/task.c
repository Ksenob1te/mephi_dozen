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
    Node *top = queue->get_top(queue);
    if (top) terminal->next_event += ((Passenger *) top->data)->waiting; else terminal->next_event = -1;
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

int scanN(int *n) {
    int status = scanf("%d", n);
    if (status && *n >= 0) return 1;
    else return 0;
}

void printStatus(Terminal **array, int len) {
    Terminal *t = *array;
    for (int i = 0; i < len; ++i, ++t) {
        List *list = array[i]->queue->list;
        printf("T%d: ", i + 1);
        for (Node *tracker = list->; tracker; tracker = tracker->next)
            printf("%s ", ((Passenger *) tracker->data)->name);
        printf("\n");
    }
}

Terminal ** initTerminals(int n) {
    Terminal **array = malloc(n * sizeof(Terminal*));
    for (int i = 0; i < n; ++i) {
        Terminal *t = malloc(sizeof(Terminal));
        t->next_event = -1;
        t->current_time = 0;
        t->queue = ccreateQueue();
        array[i] = t;
    }
    return array;
}

int handleTask(Queue* queue, Terminal **array, int n) {
    Node *top = queue->get_top(queue);
    size_t min_time;
    Passenger *current = NULL;
    if (top) {
        current = (Passenger *)(top->data);
        min_time = current->arriving;
    } else {
        min_time = (int)1e9;
    }
    Terminal **arr_ptr = array;
    for (int i = 0; i < n; ++i, ++arr_ptr)
        if (min_time > (*arr_ptr)->next_event && (*arr_ptr)->next_event > 0) min_time = (*arr_ptr)->next_event;

    arr_ptr = array;
    int checker = 0;
    for (int i = 0; i < n; ++i, ++arr_ptr)
        if ((*arr_ptr)->next_event != -1 || top) checker = 1;
    if (!checker) return 0;

    arr_ptr = array;
    for (int i = 0; i < n; ++i, ++arr_ptr)
        if (min_time == (*arr_ptr)->next_event) leaveTerminal(*arr_ptr);

    for (int i = 0; top && ((Passenger*)top->data)->arriving == min_time; ++i) {
        Node *top_node = queue->pop(queue);
        joinTerminal(selectTerminal(array, n), top_node);
        top = queue->get_top(queue);
    }

    printf("Time: %lld\n=------------------=\n", min_time);
    printStatus(array, n);
    printf("=------------------=\n\n");
    return 1;
}




