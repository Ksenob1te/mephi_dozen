#include "stdio.h"
typedef long double ld;

ld next_el(const ld y, const int n, const ld a) {
    ld y2 = 1;
    for (int i = 0; i < n - 1; ++i) {
        y2 *= y;
    }
    return (1.0 / n * ((n - 1) * y + (a / y2)));
}

ld calc_res(const int n, const ld a, const int presicion) {
    ld y = a;
    for (int i = 0; i < presicion; ++i) {
        y = next_el(y, n, a);
    }
    return y;
}

int main (void) {
    ld a = 0;
    int n = 0;
    int precision = 0;
    printf("Type n and a for sqrtn(a) formula:\n");
    int status = scanf("%d%Lf", &n, &a);
    while (status <= 1) {
        if (status == EOF) return 0;
        printf("Incorrect input, try again:\n");
        scanf("%*[^\n]*c");
        status = scanf("%d%Lf", &n, &a);
    }
    printf("\nType precision (diff between ethalon result and calc):\n");
    status = scanf("%d", &precision);
    while (status <= 0) {
        if (status == EOF) return 0;
        printf("Incorrect input, try again:\n");
        scanf("%*[^\n]*c");
        status = scanf("%d", &precision);
    }
    printf("%.34Lf", calc_res(n, a, precision));
}
