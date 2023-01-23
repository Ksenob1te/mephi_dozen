#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "time.h"

char *dubl_A(char *str) {
    char *res = malloc((2 * strlen(str) + 1) * sizeof(char));
    int ans_counter = 0;
    for (int i = 0; str[i]; ++i) {
        res[ans_counter++] = str[i];
        if (str[i] == 'A') res[ans_counter++] = str[i];

    }
    res[ans_counter++] = '\0';
    res = realloc(res, ans_counter * sizeof(char));
    return res;
}


int main() {
    printf("%d", sizeof(long long ));
}