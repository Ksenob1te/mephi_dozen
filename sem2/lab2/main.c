#include "task/input.h"
#include "stdio.h"
#include "structs/structs.h"

int main(void) {
    int len = 0;
    Queue *queue = input_array();
    for (int i = 0;; ++i) {
        Node *last = queue->pop(queue);
        if (!last) break;
        Passenger *cur = (Passenger *)last->data;
        printf("%d: %s, %d, %d\n", i + 1, cur->name, cur->arriving, cur->waiting);
        free(cur->name);
        free(cur);
        free(last);
    }
    free(queue);
}
