#include "task/input.h"
#include "stdio.h"
#include "task/task.h"
#define SIZE_OF_QUEUE 10

int main(void) {
    int n = 0, status;
    start:
    status = scanN(&n);
    if (status == 0) { printf("Try again\n"); scanf("%*[^\n]*c"); goto start;}
    if (status == EOF) return 0;
    Queue *queue = input_array(SIZE_OF_QUEUE);

    Terminal ** array = initTerminals(n, SIZE_OF_QUEUE);

    printf("Time: 0\n=------------------=\n");
    printStatus(array, n);
    printf("=------------------=\n\n");
    while (handleTask(queue, array, n));

    clearList(queue->list);
    free(queue);

    for (int i = 0; i < n; i++) {
        Terminal *cur = array[i];
        clearList(cur->queue->list);
        free(cur->queue);
        free(cur);
    }
    free(array);

    return 0;
}
