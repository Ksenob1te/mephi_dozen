#include "methods.h"
#include "table/table.h"
#include "stdio.h"

void print_table(Table *table) {
    printf(".\n");
    KeySpace *current = table->head;
    for (; current; current = current->link) {
        if (current->link) printf("├"); else printf("└");
        printf("── %llu\n", current->key);
        Node *node = current->node;
        for (; node; node = node->next) {
            if (current->link) printf("│"); else printf(" ");
            printf("   ");
            if (node->next) printf("├"); else printf("└");
            printf("── %llu\n", node->info);
        }
    }
}
