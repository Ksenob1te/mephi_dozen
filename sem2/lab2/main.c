#include "task/input.h"
#include "stdio.h"
//#include "structs/structs.h"

int main(void) {
    int len = 0;
    Passenger ** array = input_array(&len);
    for (int i = 0; i < len; ++i) {
        printf("%d: %s, %d, %d\n", i + 1, array[i]->name, array[i]->arriving, array[i]->waiting);
        free(array[i]->name);
        free(array[i]);
    }
    free(array);
}
