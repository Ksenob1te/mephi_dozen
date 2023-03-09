#include "task/input.h"
#include "stdio.h"
#include "task/task.h"

int main(void) {
    int n = 0, status;
    start:
    status = scanN(&n);
    if (status == 0) { printf("Try again\n"); scanf("%*[^\n]*c"); goto start;}
    if (status == EOF) return 0;
    Queue *queue = input_array();

    Terminal ** array = initTerminals(n);

    printf("Time: 0\n=------------------=\n");
    printStatus(array, n);
    printf("=------------------=\n\n");
    while (handleTask(queue, array, n));

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
