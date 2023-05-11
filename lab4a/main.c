#include "menu/classic_menu.h"
#include "stdlib.h"
#include "stdio.h"

#ifdef _WIN32
#include "windows.h"
#define select_settings() SetConsoleOutputCP(CP_UTF8)
#else
#define select_settings()
#endif

int main(void) {
    select_settings();
    Tree *tree = create_tree();

    Node *node1 = create_node(15, "123");
    add_node(tree, node1);
    Node *node = create_node(17, "432");
    add_node(tree, node);
    node = create_node(13, "123");
    add_node(tree, node);
//    node = create_node(8, "123");
//    add_node(tree, node);
//    node = create_node(3, "123");
//    add_node(tree, node);
//    node = create_node(18, "123");
//    add_node(tree, node);
//    node = create_node(13, "123");
//    add_node(tree, node);

    remove_node(tree, node1);
//    node = search_node(tree, 15);
//    tree_traversal(tree, 8);
//    char x[1000] = "";
//    print_root(x, tree->root, 1);
    menu(tree);


    return 0;
}
