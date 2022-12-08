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

int wordlen(char *str) {
    int counter = 0;
    for (; str[counter] != ' ' && str[counter] != '\t' && str[counter] != '\0'; ++counter);
    return counter;
}

char *process(char *str) {
    int vowels_counter = 0;
    int counter = 0, words_counter = 0, ans_counter = 0, letter_counter = 0;
    char *words[wordlen(str)];
    for (; str[counter] != '\0'; ++counter) {
        vowels_counter += checkVowel(str[counter]);
        letter_counter += (str[counter] != '\t' && str[counter] != '\0')?1:0;
        if ((str[counter] == ' ' || str[counter] == '\t' || counter == 0) &&
        (str[counter + 1] != '\0' && str[counter + 1] != ' ' && str[counter + 1] != '\t')) {
            words[words_counter++] = str + counter + (counter == 0?0:1);
        }
    }
    printf("%d\n", letter_counter + words_counter + vowels_counter);
    char *ans = malloc((letter_counter + words_counter + vowels_counter) * sizeof(char));
    for (int i = 0; i < words_counter; ++i) {
        for (int j = 0; j < wordlen(words[i]); j++) {
            ans[ans_counter++] = words[i][j];
            if (checkVowel(words[i][j]))
                ans[ans_counter++] = words[i][j];
        }
        ans[ans_counter++] = (i != words_counter - 1)?' ':'\0';
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