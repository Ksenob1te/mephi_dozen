//#include "menu/classic_menu.h"
#include "methods.h"
#include "stdlib.h"
#include "stdio.h"
#include "menu/classic_menu.h"

#ifdef _WIN32
#include "windows.h"
#define select_settings() SetConsoleOutputCP(CP_UTF8)
#else
#define select_settings()
#endif

Node create_nul() {
    Node nul;
    nul.color = 0;
    nul.right = NULL;
    nul.left = NULL;
    nul.key = 0;
    nul.info = NULL;
    return nul;
}

int main(void) {
    select_settings();
    Node nul = create_nul();
    Tree *tree = create_tree(&nul);
    char *x = malloc(4); strcat(x, "123");
    Node *node1 = create_node(&nul, 24, x);
    add_node(&nul, tree, node1);
    x = malloc(4); strcat(x, "123");
    Node *node = create_node(&nul, 5, x);
    add_node(&nul, tree, node);
    x = malloc(4); strcat(x, "123");
    node1 = create_node(&nul, 1, x);
    add_node(&nul, tree, node1);
    x = malloc(4); strcat(x, "123");
    node = create_node(&nul, 15, x);
    add_node(&nul, tree, node);
    x = malloc(4); strcat(x, "123");
    node = create_node(&nul, 3, x);
    add_node(&nul, tree, node);
    x = malloc(4); strcat(x, "123");
    node = create_node(&nul, 8, x);
    add_node(&nul, tree, node);

//    print_tree(&nul, tree);

//    preorder_traversal(&nul, tree->root, 1);
//    node1 = search_node(&nul, tree, 3);
//    remove_node(&nul, tree, node1);

//    remove_node(tree, node1);
//    node = search_node(tree, 15);
//    tree_traversal(tree, 8);
//    char x[1000] = "";
//    print_root(x, tree->root, 1);
    menu(&nul, tree);
//    print_tree(&nul, tree);
//    scanf("\n");

    return 0;
}
