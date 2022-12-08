#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "readline/readline.h"

#define PROMPT "> "
#define VOWELS "aeiouAEIOU"

//char * strcat(char * destptr, const char * srcptr) {
//    int destLen, i;
//    for (destLen = 0; destptr[destLen] != '\0'; ++destLen);
//    for (i = destLen; srcptr[i - destLen] != '\0'; ++i) {
//        destptr[i] = srcptr[i - destLen];
//    }
//    destptr[i] = '\0';
//    return destptr;
//}

//char *readline(char *prompt) {
//    printf("%s", prompt);
//    char *ptr = (char *) malloc(sizeof(char));
//    char buf[81];
//    int n, len = 0, bufLen;
//    *ptr = '\0';
//    do {
//        n = scanf("%80[^\n]%n", buf, &bufLen);
//        if (n < 0) {
//            free(ptr);
//            ptr = NULL;
//            continue;
//        }
//        if (n == 0)
//            scanf("%*c");
//        else {
//            len += bufLen;
//            ptr = (char *) realloc(ptr, len + 1);
//            strcat(ptr, buf);
//        }
//    } while (n > 0);
//    return ptr;
//}

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
    char *ans = malloc((counter + vowels_counter) * sizeof(char));
    for (int i = 0; i < counter; ++i) {
        ans[ans_counter++] = str[i];
        if (checkVowel(str[i]))
            ans[ans_counter++] = str[i];
    }
    return ans;
}

int main(void) {
    char *str = readline(PROMPT);
    printf("\"%s\"\n", str);
    char *ans = process(str);
    printf("\"%s\"\n", ans);
    free(str);
    free(ans);
    return 0;
}