#include "methods.h"
#include "table/table.h"
#include "stdio.h"

void print_table(Table *table) {
    printf("\033[0;33m.\033[0m\n");
    KeySpace *current = table->head;
    for (; current; current = current->link) {
        if (current->link) printf("├"); else printf("└");
        printf("── \033[0;33m%llu\033[0m\n", current->key);
        Node *node = current->node;
        for (; node; node = node->next) {
            if (current->link) printf("│"); else printf(" ");
            printf("   ");
            if (node->next) printf("├"); else printf("└");
            printf("── %llu\n", node->info);
        }
    }
}

void add_key(Table *table) {
    printf("Type in key value (int): ");
    ull key;
    int status;
    input:
        status = scanf("%llu", &key);
    if (status == EOF) return;
    if (status == 0) {
        printf("\033[0;31mError in input, try again\033[0m\n");
        goto input;
    }

}
