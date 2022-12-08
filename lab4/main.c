#include "stdio.h"
#include "stdlib.h"

#ifndef MY_LIB
#include "methods.h"
#else
#include "readline/readline.h"
#include "string.h"
#endif


#define PROMPT "> "
#define VOWELS "aeiouAEIOU"

int checkVowel(char element) {
    char *vowels = VOWELS;
    for (int i = 0; vowels[i] != '\0'; ++i) {
        if (element == vowels[i]) return 1;
    }
    return 0;
}

int checkContinuousSpaces(const char *str, int place) {
    if (place > 0 &&
        (str[place] == '\t' || str[place] == ' ') &&
        (str[place - 1] == '\t' || str[place - 1] == ' ')) {
        return 1;
    } else {
        return 0;
    }
}

char *process(char *str) {
    int vowels_counter = 0;
    int counter = 0, ans_counter = 0, spaces_delete = 0;
    for (; str[counter] != '\0'; ++counter) {
        vowels_counter += checkVowel(str[counter]);
        spaces_delete += checkContinuousSpaces(str, counter);
    }
    for (int i = 0; str[i] == ' ' || str[i] == '\t'; i++) {spaces_delete++; str[i] = '\0';}
    for (int i = counter - 1; str[i] == ' ' || str[i] == '\t'; i--) {spaces_delete++; str[i] = '\0';}

    int new_len = counter + vowels_counter - spaces_delete + 1;
    char *ans = malloc(new_len * sizeof(char));
    ans[new_len] = '\0';

    for (int i = 0; i < counter; ++i) {
        if (str[i] != '\0' && !checkContinuousSpaces(str, i)) {
            ans[ans_counter++] = ((str[i] == '\t')?' ':str[i]);
            if (checkVowel(str[i]))
                ans[ans_counter++] = str[i];
        }
    }
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