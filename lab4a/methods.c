#include "methods.h"
#include "stdio.h"
#include "stdlib.h"
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

void print_tree(Tree *tree) {
    char x[1000] = "";
    print_root(x, tree->root, 1);
}

void add_node_tree(Tree *tree) {
    printf("Type in key value (int): ");
    ull key = input_ull();
    printf("Type in item value (string): ");
    scanf("\n");
    char *value = readline();
    if (!value) return;
    Node *node = create_node(key, value);
    add_node(tree, node);
    printf("Done!\n");
}

void search_node_tree(Tree *tree) {
    printf("Type in key value (int): ");
    ull key = input_ull();
    Node *node = search_node(tree, key);
    if (!node) {
        fprintf(stderr, "\033[0;31mNo key has been found\033[0m\n");
        return;
    }
    printf("\033[1;97m%llu\033[0m: \033[1;90m", node->key);
    for (int i = 0; i < node->info_size; i++) {
        printf("\"%s\" ", (node->info)[i]);
    }
    printf("\033[0m\n");
}

void traversal_limit_tree(Tree *tree) {
    printf("Type in limitations (unsigned int): ");
    ull key = input_ull();
    tree_traversal(tree, key);
}

void remove_node_tree(Tree *tree) {
    printf("Type in key value (int): ");
    ull key = input_ull();
    Node *node = search_node(tree, key);
    if (!node) {
        fprintf(stderr, "\033[0;31mNo key has been found\033[0m\n");
        return;
    }
    if (node->info_size > 1) {
        printf("\033[1;97m%llu\033[0m: \033[1;90m", node->key);
        for (int i = 0; i < node->info_size; i++) {
            printf("\"%s\" ", (node->info)[i]);
        }
        printf("\033[0m\n");
        printf("There is more than 1 item, select which one u wanna delete (1 - %d): ", node->info_size);
        ull index = input_ull();
        remove_item(node, (int) index);
    } else {
        remove_node(tree, node);
    }
    printf("Done!\n");
}

void sp_search_node_tree(Tree *tree) {
    Node *current_root = tree->root;
    if (!tree->root) {
        fprintf(stderr, "\033[0;31mNo key has been found\033[0m\n");
        return;
    }
    while (current_root->left != NULL)
        current_root = current_root->left;
    printf("\033[1;97m%llu\033[0m: \033[1;90m", current_root->key);
    for (int i = 0; i < current_root->info_size; i++) {
        printf("\"%s\" ", (current_root->info)[i]);
    }
    printf("\033[0m\n");
}
