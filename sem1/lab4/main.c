#include "stdio.h"
#include "stdlib.h"

#ifndef MY_LIB
#include "methods.h"
#else
#include "readline/readline.h"
#include "string.h"
#endif


#define PROMPT "> "
#define DELIM "\t "
#define VOWELS "aeiouAEIOU"

int checkVowel(char element) {
    char *vowels = VOWELS;
    for (int i = 0; vowels[i] != '\0'; ++i) {
        if (element == vowels[i]) return 1;
    }
    return 0;
}


char *process(char *str) {
    int vowels_counter = 0, ans_counter = 0;
    int counter, size = 1;
    char *ans = malloc(0), *res = strtok(str, DELIM);
    while (res != NULL) {
        for (counter = 0; res[counter] != '\0'; ++counter) {
//            printf("'%c': %d\n", res[counter], counter);
            vowels_counter += checkVowel(res[counter]);
        }
        size += vowels_counter + counter + 1;
        ans = realloc(ans, size * sizeof(int));
        for (counter = 0; res[counter] != '\0'; ++counter) {
            ans[ans_counter++] = res[counter];
            if (checkVowel(res[counter])) ans[ans_counter++] = res[counter];
        }
        ans[ans_counter++] = ' ';
        res = strtok(NULL, DELIM);
    }
    if (ans_counter == 0) return calloc(1, sizeof(char));
    ans[ans_counter - 1] = '\0';
    return ans;
}

int main(void) {
    char *str;
    do {
        str = readline(PROMPT);
        if (!str) continue;
        printf("Input data: \"%s\"\n", str);
        char *ans = process(str);
        printf("Result data: \"%s\"\n", ans);
        free(str);
        free(ans);
    } while (str);
    return 0;
}