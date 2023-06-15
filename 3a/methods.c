#include "methods.h"
#include "table/table.h"
#include "stdio.h"
#include "stdlib.h"

ull input_ull() {
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
            printf("── \033[1;90m%llu:\033[0m%llu\n", node->release, node->info);
        }
    }
}

void add_key(Table *table) {
    printf("Type in key value (int): ");
    ull key = input_ull();
    if (key == -1) return;
    KeySpace *keyspace = create_keyspace(key);
    int status = table->add_key(table, keyspace);
    if (!status) {
        fprintf(stderr, "\033[0;31mThis keyspace already exists\033[0m\n");
        keyspace->remove(keyspace);
        return;
    }
    printf("Done!\n");
}

void add_element_key(Table *table) {
    printf("Type in key value (int): ");
    ull key = input_ull();
    if (key == -1) return;
    KeySpace *keyspace = table->find_key(table, key);
    if (!keyspace) {
        fprintf(stderr, "\033[0;31mNo key has been found\033[0m\n");
        return;
    }
    printf("Type in element value (int): ");
    ull value = input_ull();
    if (value == -1) return;
    Node *node = create_node(value);
    keyspace->add_node(keyspace, node);
    printf("Done!\n");
}

void search_interval(Table *table) {
    printf("Type in left interval value (int): ");
    ull left = input_ull();
    if (left == -1) return;
    printf("Type in right interval value (int): ");
    ull right = input_ull();
    if (right == -1) return;

    Table *result = table->find_key_range(table, left, right);
    printf("Result of the search: \n");
    print_table(result);
    result->remove(result);
}

void search_key(Table *table) {
    printf("Type in key value (int): ");
    ull key = input_ull();
    if (key == -1) return;
    KeySpace *keyspace = table->find_key(table, key);
    if (!keyspace) {
        fprintf(stderr, "\033[0;31mNo key has been found\033[0m\n");
        return;
    }
    printf("\033[0;33m%llu\033[0m\n", keyspace->key);
    Node *node = keyspace->node;
    for (; node; node = node->next) {
        if (node->next) printf("├"); else printf("└");
        printf("── \033[1;90m%llu:\033[0m%llu\n", node->release, node->info);
    }
}

void search_element_version(Table *table) {
    printf("Type in key value (int): ");
    ull key = input_ull();
    if (key == -1) return;
    KeySpace *keyspace = table->find_key(table, key);
    if (!keyspace) {
        fprintf(stderr, "\033[0;31mNo key has been found\033[0m\n");
        return;
    }
    printf("Type in release version (int): ");
    ull release = input_ull();
    if (release == -1) return;
    Node *node = keyspace->find_node(keyspace, release);
    if (!node) {
        fprintf(stderr, "\033[0;31mNo node has been found\033[0m\n");
        return;
    }
    printf("Found node:\n\033[1;90m%llu:\033[0m%llu\n", node->release, node->info);
}

void delete_key(Table *table) {
    printf("Type in key value (int): ");
    ull key = input_ull();
    if (key == -1) return;
    int status = table->remove_key(table, key);
    if (!status)
        fprintf(stderr, "\033[0;31mNo key has been found\033[0m\n");
    else
        printf("Done!\n");
}

void delete_element_version(Table *table) {
    printf("Type in key value (int): ");
    ull key = input_ull();
    if (key == -1) return;
    KeySpace *keyspace = table->find_key(table, key);
    if (!keyspace) {
        fprintf(stderr, "\033[0;31mNo key has been found\033[0m\n");
        return;
    }
    printf("Type in release version (int): ");
    ull release = input_ull();
    if (release == -1) return;
    int status = keyspace->remove_node(keyspace, keyspace->find_node(keyspace, release));
    if (!status) {
        fprintf(stderr, "\033[0;31mNo node has been found\033[0m\n");
        return;
    }
    printf("Done!\n");
}