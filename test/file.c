#include <stdio.h>
#include <stdlib.h>
#include "string.h"

void dubl_sec(char **str, size_t* len) {
    size_t new_len = 0;
    char *result = malloc(*len * 2 * sizeof(char));
    char *word = strtok(*str, " ");
    int wc = 1;
    while (word != NULL) {
        for (int i = 0; word[i]; ++i) {
            result[new_len++] = word[i];
        }
        result[new_len++] = ' ';
        if (wc % 2 == 0) {
            for (int i = 0; word[i]; ++i) {
                result[new_len++] = word[i];
            }
            result[new_len++] = ' ';
        }
        wc++;
        word = strtok(NULL, " ");
    }
    result[new_len++] = '\0';
    result = realloc(result, new_len * sizeof(char));
    free(*str);
    *str = result;
    *len = new_len;
}

int main() {
    char *str = malloc(100 * sizeof(char));
    size_t len = 100;
    fgets(str, 100, stdin);
//    scanf("%99s", str);
    dubl_sec(&str, &len);
    printf("%s", str);
    free(str);
    return 0;
}