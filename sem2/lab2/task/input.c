#include "input.h"
#include "stdio.h"
#include "string.h"

char *readline(int *len) {
    char *ptr = (char *) malloc(sizeof(char));
    char buf[81];
    int n, bufLen;
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
            ptr = (char *) realloc(ptr, *len + 1);
            strcat(ptr, buf);
        }
    } while (n > 0);
    *len += 1;
    return ptr;
}

void input_array() {
    int len, i;
    char *s = readline(&len);
    char *sp = strtok(s, " ");
    while (sp) {
        size_t len_part = strlen(sp);

        // Name handle
        // ===============================
        char *name = malloc(len_part * sizeof(char));
        for (i = 0; sp[i] && sp[i] != '/'; ++i)
            name[i] = sp[i];
        if (!sp[i]) {
            free(name);
            continue;
        }
        name = realloc(name, (i + 1) * sizeof(char));
        name[i] = '\0';
        // ===============================

        // Time handle
        // ===============================
        char *time = malloc(len_part * sizeof(char));
        int time_counter = 0;
        for (i++; sp[i] && sp[i] != '/'; ++i)
            time[time_counter++] = sp[i];
        if (!sp[i]) {
            free(name); free(time);
            continue;
        }
        time = realloc(time, (time_counter + 1) * sizeof(char));
        time[time_counter] = '\0';
        // ===============================

        // Wait handle
        // ===============================
        char *wait = malloc(len_part * sizeof(char));
        int wait_counter = 0;
        for (i++; sp[i] && sp[i] != ' '; ++i)
            wait[wait_counter++] = sp[i];
        if (!sp[i]) {
            free(name); free(time);
            continue;
        }
        time = realloc(time, (time_counter + 1) * sizeof(char));
        time[time_counter] = '\0';
        // ===============================

        for (i = 0; sp[i] && sp[i] != '/'; ++i)
            name[i] = sp[i];
        if (!sp[i]) {
            free(p); free(name);
            continue;
        }
        char *sp = strtok(NULL, " ");
    }
}