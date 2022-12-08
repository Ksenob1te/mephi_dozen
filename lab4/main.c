#include "methods.h"
#include "stdio.h"
#include "stdlib.h"

#define PROMPT "> "
#define VOWELS "aeiouAEIOU"

int checkVowel(char element) {
    char *vowels = VOWELS;
    for (int i = 0; vowels[i] != '\0'; ++i) {
        if (element == vowels[i]) return 1;
    }
    return 0;
}

char *process(char *str) {
    int vowels_counter = 0;
    int counter = 0, ans_counter = 0;
    for (; str[counter] != '\0'; ++counter)
        vowels_counter += checkVowel(str[counter]);
    char *ans = malloc((counter + vowels_counter + 1) * sizeof(char));
    ans[counter + vowels_counter] = '\0';
    for (int i = 0; i < counter; ++i) {
        ans[ans_counter++] = str[i];
        if (checkVowel(str[i]))
            ans[ans_counter++] = str[i];
    }
    return ans;
}

int main(void) {
    char *str;
    do {
        str = readline(PROMPT);
        if (!str) continue;
        printf("\"%s\"\n", str);
        char *ans = process(str);
        printf("\"%s\"\n", ans);
        free(str);
        free(ans);
    } while (str);
    return 0;
}