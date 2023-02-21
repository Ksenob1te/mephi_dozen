#include "task/input.h"
#include "stdio.h"
#include "structs/structs.h"
#include "task/task.h"

int main(void) {
    int n = 0, status;
    start:
    status = scanf("%d", &n);
    if (status == 0) { printf("Try again\n"); goto start;}
    if (status == EOF) return 0;
    Queue *queue = input_array();

    Terminal **array = malloc(n * sizeof(Terminal*));
    for (int i = 0; i < n; ++i) {
        Terminal *t = malloc(sizeof(Terminal));
        t->next_event = 0;
        t->current_time = 0;
        t->queue = createQueue();
        array[i] = t;
    }

    int checker = 1;
    printf("Time: 0\n=------------------=\n");
    printStatus(array, n);
    printf("=------------------=\n\n");

    while (checker) {
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
        checker = 0;
        for (int i = 0; i < n; ++i, ++arr_ptr)
            if ((*arr_ptr)->next_event != -1) checker = 1;
        if (!checker) continue;

        arr_ptr = array;
        for (int i = 0; i < n; ++i, ++arr_ptr)
            if (min_time == (*arr_ptr)->next_event) leaveTerminal(*arr_ptr);

        for (int i = 0; top && ((Passenger*)top->data)->arriving == min_time; ++i) {
            Node *top_node = queue->pop(queue);
            joinTerminal(selectTerminal(array, n), top_node);
            top = queue->get_top(queue);
        }

        printf("Time: %d\n=------------------=\n", min_time);
        printStatus(array, n);
        printf("=------------------=\n\n");


    }
    return 0;
//    for (int i = 0;; ++i) {
//        Node *last = queue->pop(queue);
//        if (!last) break;
//        Passenger *cur = (Passenger *)last->data;
//        printf("%d: %s, %d, %d\n", i + 1, cur->name, cur->arriving, cur->waiting);
//        free(cur->name);
//        free(cur);
//        free(last);
//    }
//    free(queue->list);
//    free(queue);
}
