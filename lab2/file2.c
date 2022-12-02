#include "stdio.h"
#include "math.h"
typedef long double ld;

ld next_el(const ld y, const int n, const ld a) {
    ld y2 = 1;
    for (int i = 0; i < n - 1; ++i) {
        y2 *= y;
    }
    return (1.0 / n * ((n - 1) * y + (a / y2)));
}

ld calc_res(const int n, const ld a, const float precision, int* counter) {
    double x = 1./n;
    ld eth_res = powl(a, (1.0/n));
    printf("Ethalon (math) result: %.34Lf\n", eth_res);
    ld y = a;
    for (*counter = 0; *counter < 1e5; ++*counter) {
        y = next_el(y, n, a);
        if (fabsl(y - eth_res) <= precision) {
            return y;
        }
    }
    return y;
}

int main (void) {
    ld a = 0;
    int n = 0;
    float precision = 0;
    printf("Type n and a for sqrtn(a) formula:\n");
    int status = scanf("%d%Lf", &n, &a);
    while (status <= 1) {
	if (status == EOF) return 0;
        printf("Incorrect input, try again:\n");
        scanf("%*[^\n]*c");
        status = scanf("%d%Lf", &n, &a);
    }
    printf("\nType precision (diff between ethalon result and calc):\n");
    status = scanf("%f", &precision);
    while (status <= 0) {
	if (status == EOF) return 0;
        printf("Incorrect input, try again:\n");
        scanf("%*[^\n]*c");
	status = scanf("%f", &precision);
    }
    int counter = 0;
    printf("My result: %.34Lf\n", calc_res(n, a, precision, &counter));
    printf("Number of iterations: %d", counter + 1);

}

