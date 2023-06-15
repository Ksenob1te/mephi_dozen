#include "methods.h"
#include "string.h"

static ull input_ull() {
    ull key;
    int status;
    input:
    status = scanf("%llu", &key);
    if (status == EOF || status < 0) return -1;
    if (status == 0) {
        fprintf(stderr, "\033[0;31mError in input, try again\033[0m\n");
        scanf("%*[^\n]");
        goto input;
    }
    return key;
}

static char *readline() {
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

void print_table (Table *table) {
    printf("\033[0;33m");
    for (int i = 0; i < table->msize; i++) {
        KeySpace current = (table->keys)[i];
        if (current.key) {
            char *s;
            if (current.busy == 1)
                s = "LIVE";
            else
                s = "DEAD";
            printf("(%d) %s - %s: %llu\n", i, current.key, s, current.info);
        } else
            printf("(%d) EMPTY\n", i);
    }
    printf("\033[0m");
}

void add_key(Table *table) {
    printf("Type in key value (string): ");
    scanf("\n");
    char *key = readline();
    if (!key) return;
    printf("Type in item value (int): ");
    ull value = input_ull();
    int status = insert_element(table, key, value);
    if (status == 2) {
        fprintf(stderr, "\033[0;31mThis key already exists\033[0m\n");
        return;
    }
    if (status == 1) {
        fprintf(stderr, "\033[0;31mCan't execute operation due to overflow\033[0m\n");
        return;
    }
    printf("Done!\n");
}

void search_key(Table *table) {
    printf("Type in key value (string): ");
    scanf("\n");
    char *key = readline();
    if (!key) return;
    KeySpace *keyspace = find_element(table, key);
    free(key);
    if (!keyspace) {
        fprintf(stderr, "\033[0;31mNo key has been found\033[0m\n");
        return;
    }
    printf("%s: %llu\n", keyspace->key, keyspace->info);
}

void delete_key(Table *table) {
    printf("Type in key value (string): ");
    scanf("\n");
    char *key = readline();
    if (!key) return;
    int status = remove_element(table, key);
    free(key);
    if (status)
        fprintf(stderr, "\033[0;31mNo key has been found\033[0m\n");
    else
        printf("Done!\n");
}
