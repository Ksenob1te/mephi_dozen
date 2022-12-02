#include <stdio.h>
#include "stdlib.h"
#include "time.h"
#include "limits.h"
#define si short int

void array_input(int* array, const int* len) {
    for (int i = 0; i < *len; ++i) {
        array[i] = rand() % 20000 - 10000;
//        int status = scanf("%d", array + i);
//        while (status <= 0) {
//            if (status == EOF) exit(-1);
//            printf("Incorrect input, try again: \n");
//            scanf("%*[^\n]*c");
//            status = scanf("%d", array + i);
//        }
    }
}

void array_print(const int* array, const int* len) {
    printf("\nUr array is: \n");
    for (int i = 0; i < *len; ++i) {
        printf("%d ", array[i]);
    }
}

void array_remove_dupl(int* array, int* answer, si* checker_p, si* checker_n, int* len) {
    int ans_counter = 0;
    for (int i = 0; i < *len; ++i) {
        if (array[i] < 0 && !checker_n[abs(array[i]) - 1]) {
            checker_n[abs(array[i]) - 1] = 1;
            answer[ans_counter++] = array[i];
        }
        else if (array[i] > 0 && !checker_p[array[i] - 1]) {
            checker_p[array[i] - 1] = 1;
            answer[ans_counter++] = array[i];
        }
    }
    *len = ans_counter;
}


int main() {
    int len = 10000;
    srand(time(NULL));
    si* checker_positive = (si*)calloc(0, (10000) * sizeof(si));
    si* checker_negative = (si*)calloc(0, (10000) * sizeof(si));
    int* array = (int*)malloc(len * sizeof(int));
    int* answer = (int*)malloc(len * sizeof(int));
    if (checker_positive == NULL || checker_negative == NULL || array == NULL || answer == NULL) {
        printf("kjhfdfs");
        return 0;
    }
//    for (int i = 0; i < 100000; ++i) {
//        printf("%d ", checker_positive[i]);
//    }

    array_input(array, &len);
    clock_t start = 0, end = 0;
    start = clock();
    array_remove_dupl(array, answer, checker_positive, checker_negative, &len);
    end = clock();
    printf("\n%d\n", len);
    printf("\n%lf", (double)(end-start)/CLOCKS_PER_SEC);
    return 0;
}
