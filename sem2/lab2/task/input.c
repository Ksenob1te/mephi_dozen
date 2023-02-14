#include "input.h"
#include "stdio.h"
#include "string.h"
#include "ctype.h"

char *readline() {
    char *ptr = (char *) malloc(sizeof(char));
    char buf[81];
    int n, bufLen, len = 0;
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

int isInt(const char *s) {
    for (int i = 0; s[i]; ++i)
        if (!isdigit(s[i])) return 0;
    return 1;
}

size_t strToInt(const char *s) {
    size_t result = 0;
    for (int i = 0; s[i]; ++i) {
        result *= 10;
        result += (size_t)(s[i] - '0');
    }
    return result;
}

Passenger ** input_array(int *array_size) {
    int i;
    struct Passenger **array = malloc(0);

    char *s = readline();
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
            sp = strtok(NULL, " ");
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
            sp = strtok(NULL, " ");
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
        wait = realloc(wait, (wait_counter + 1) * sizeof(char));
        wait[wait_counter] = '\0';
        // ===============================

        size_t i_time, i_wait;
        if (isInt(time) && isInt(wait)){
            i_time = strToInt(time);
            free(time);
            i_wait = strToInt(wait);
            free(wait);
        } else {
            free(name); free(time); free(wait);
            sp = strtok(NULL, " ");
            continue;
        }

        Passenger *p = malloc(sizeof(Passenger));
        p->name = name;
        p->arriving = i_time;
        p->waiting = i_wait;

        array = realloc(array, ++(*array_size) * sizeof(struct Passenger *));

        array[*array_size - 1] = p;
        sp = strtok(NULL, " ");
    }
    free(s);
    return array;
}