#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int * A = calloc(100, sizeof(int));
    int * B = malloc(100 * sizeof(int));
    printf("Addr A %p\n", A);
    for (int i = 0; i < 100; ++i)
        printf("%d ", A[i]);
    printf("\nAddr B %p\n", B);
    for (int i = 0; i < 100; ++i)
        printf("%d ", B[i]);
    A = realloc(A, 50 * sizeof(int) );
    B = realloc(B, 200 * sizeof(int) );
    printf("\nAddr A %p\n", A);
    A[50] = 1;
    printf("Addr B %p\n", B);
    return 0;

}