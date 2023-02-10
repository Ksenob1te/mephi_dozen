#include "stdio.h"
#include "stdlib.h"


int inIntArray(int *array, int sizeOfArray) {
    int status;
    int *ptr = array;
    for (int i = 0; i < sizeOfArray; i++) {
        status = scanf("%d", ptr);
        if (status <= 0) {printf("Error in input\n"); return 1;}
        ++ptr;
    }
    return 0;
}

void clearPtrArr(int **array, int sizeOfArray) {
    int **ptr = array;
    for (int i = 0; i < sizeOfArray; i++) {
        free(*ptr);
        ++ptr;
    }
}

void printArray(int *array, int sizeOfArray) {
    int *ptr = array;
    for (int i = 0; i < sizeOfArray; ++i) {
        printf("%d ", *ptr);
        ++ptr;
    }
}

void printMatrix(int **matrix, int *sizes, int sizeOfArray) {
    int **ptr_arr = matrix;
    int *ptr = sizes;
    for (int i = 0; i < sizeOfArray; ++i) {
        printf("%d: ", i + 1);
        printArray(*ptr_arr, *ptr);
        printf("\n");
        ++ptr;
        ++ptr_arr;
    }
}

void swap(int *first, int *second) {
    int temp = *first;
    *first = *second;
    *second = temp;
}

void operate(int *array, int sizeOfArray) {
    int *first = NULL, *second = NULL, *ptr = array + 1;
    for (int i = 1; i < sizeOfArray; ++i, ++ptr) {
        if (*ptr - *(ptr - 1) > 0 && !first)
            first = ptr;
        if (*ptr - *(ptr - 1) < 0)
            second = ptr;
    }
    if (first && second)
        swap(first, second);
}

int ** inputPtrArray(int *sizes, int n) {
    int **array = malloc(n * sizeof(int *));
    int *ptr = sizes;
    int **ptr_arr = array;
    int status;
    for (int i = 0; i < n; ++i, ++ptr_arr, ++ptr) {
        *ptr_arr = malloc(*ptr * sizeof(int));
        status = inIntArray(*ptr_arr, *ptr);
        if (status) {clearPtrArr(ptr_arr, i); free(array); free(sizes); return NULL;}
    }
    return array;
}

int main(void) {
    int n = 0, status;
    status = scanf("%d", &n);
    if (status <= 0) return 0;
    int *sizes = malloc(n * sizeof(int));

    status = inIntArray(sizes, n);
    if (status) {free(sizes); return 1;}

    int ** array = inputPtrArray(sizes, n);
    if (!array) return 1;
    printf("Input Matrix:\n");
    printMatrix(array, sizes, n);

    int **ptr_arr = array;
    int *ptr = sizes;
    for (int i = 0; i < n; ++i, ++ptr_arr, ++ptr)
        operate(*ptr_arr, *ptr);
    printf("Output Matrix:\n");
    printMatrix(array, sizes, n);
    clearPtrArr(array, n); free(array); free(sizes);
    return 0;
}
