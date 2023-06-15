#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "methods.h"

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


void print_tree(Node *nul, Tree *tree) {
    char x[1000] = "";
    print_root(nul, x, tree->root, 1);
}

void add_node_tree(Node *nul, Tree *tree) {
    printf("Type in key value (int): ");
    ull key = input_ull();
    printf("Type in item value (string): ");
    scanf("\n");
    char *value = readline();
    if (!value) return;
    Node *node = create_node(nul, key, value);
    add_node(nul, tree, node);
    printf("Done!\n");
}

void search_node_tree(Node *nul, Tree *tree) {
    printf("Type in key value (int): ");
    ull key = input_ull();
    Node *node = search_node(nul, tree, key);
    if (!node) {
        fprintf(stderr, "\033[0;31mNo key has been found\033[0m\n");
        return;
    }
    if (node->color == 0) {
        printf("\033[1;97m%llu\033[0m: \033[1;90m", node->key);
        for (Item *i = node->info; i; i = i->next) {
            printf("\"%s\" ", i->info);
        }
    } else {
        printf("\033[91m%llu\033[0m: \033[31m", node->key);
        for (Item *i = node->info; i; i = i->next) {
            printf("\"%s\" ", i->info);
        }
    }
    printf("\033[0m\n");
}

void traversal_limit_tree(Node *nul, Tree *tree) {
    printf("Type in limitations (unsigned int): ");
    ull key = input_ull();
    preorder_traversal(nul, tree->root, (int) key);
}

void remove_node_tree(Node *nul, Tree *tree) {
    printf("Type in search value (int): ");
    ull key = input_ull();
    Node *node = search_node(nul, tree, key);
    if (!node) {
        fprintf(stderr, "\033[0;31mNo key has been found\033[0m\n");
        return;
    }
    if (node->info->next) {
        if (node->color == 0) {
            printf("\033[1;97m%llu\033[0m: \033[1;90m\n", node->key);
            int counter = 1;
            for (Item *i = node->info; i; i = i->next, counter++) {
                printf("%d: \"%s\"\n", counter, i->info);
            }
        } else {
            printf("\033[91m%llu\033[0m: \033[31m\n", node->key);
            int counter = 1;
            for (Item *i = node->info; i; i = i->next, counter++) {
                printf("%d: \"%s\"\n", counter, i->info);
            }
        }
        printf("\033[0m\n");
        printf("There is more than 1 item, select which one u wanna delete: ");
        ull index = input_ull();
        remove_item(node, (int) index - 1);
    } else {
        remove_node(nul, tree, node);
    }
    printf("Done!\n");
}

void sp_search_node_tree(Node *nul, Tree *tree) {
    printf("Type in search value (int): ");
    ull key = input_ull();
    if (tree->root == nul) {
        fprintf(stderr, "\033[0;31mNo key has been found\033[0m\n");
        return;
    }
    Node *current_root = find_min_limit(nul, tree, key);
    if (!current_root) {
        fprintf(stderr, "\033[0;31mNo key has been found\033[0m\n");
        return;
    }
    if (current_root->color == 0) {
        printf("\033[1;97m%llu\033[0m: \033[1;90m\n", current_root->key);
        int counter = 1;
        for (Item *i = current_root->info; i; i = i->next, counter++) {
            printf("%d: \"%s\"\n", counter, i->info);
        }
    } else {
        printf("\033[91m%llu\033[0m: \033[31m\n", current_root->key);
        int counter = 1;
        for (Item *i = current_root->info; i; i = i->next, counter++) {
            printf("%d: \"%s\"\n", counter, i->info);
        }
    }
    printf("\033[0m\n");
}

