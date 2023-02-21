//
// Created by Ksenob1te on 08.12.2022.
//
#include "stdlib.h"
#include "stdio.h"
#include "methods.h"

char * strcat(char * destptr, const char * srcptr) {
    int destLen, i;
    for (destLen = 0; destptr[destLen] != '\0'; ++destLen);
    for (i = destLen; srcptr[i - destLen] != '\0'; ++i) {
        destptr[i] = srcptr[i - destLen];
    }
    destptr[i] = '\0';
    return destptr;
}

char * strtok(char *string, const char *delim) {
    static char *last;
    if (string == NULL && (string = last) == NULL) return (NULL);
    char c, sc, *span, *temp;
    cont:
    c = *string++;
    for (span = (char *)delim; (sc = *span++) != '\0';)
        if (c == sc)
            goto cont;
    if (string[-1] == '\0') {
        last = NULL;
        return (NULL);
    }
    temp = string - 1;
    for (c = *string++;;c = *string++) {
        span = (char *)delim;
        do {
            if ((sc = *span++) == c) {
                if (c == 0)
                    string = NULL;
                else
                    string[-1] = 0;
                last = string;
                return (temp);
            }
        } while (sc != '\0');
    }
}

char *readline(char *prompt) {
    printf("%s", prompt);
    char *ptr = (char *) malloc(sizeof(char));
    char buf[81];
    int n, len = 0, bufLen;
    *ptr = '\0';
    do {
        n = scanf("%80[^\n]%n", buf, &bufLen);
        if (n < 0) {
            free(ptr);
            ptr = NULL;
            continue;
        }
        if (n == 0)
            scanf("%*c");
        else {
            len += bufLen;
            ptr = (char *) realloc(ptr, len + 1);
            strcat(ptr, buf);
        }
    } while (n > 0);
    return ptr;
}

