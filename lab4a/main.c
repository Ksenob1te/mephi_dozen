#include "tree/tree.h"
#include "stdlib.h"
#include "stdio.h"

int main(void) {
    Tree *tree = create_tree();
    Node *node = create_node(15, "123");
    add_node(tree, node);
    node = create_node(15, "432");
    add_node(tree, node);
    Node *node1 = create_node(6, "123");
    add_node(tree, node1);
    node = create_node(8, "123");
    add_node(tree, node);
    node = create_node(3, "123");
    add_node(tree, node);
    node = create_node(18, "123");
    add_node(tree, node);
    node = create_node(13, "123");
    add_node(tree, node);

    remove_node(tree, node1);

    tree_traversal(tree, 8);
    char x[1000] = "";
    print_root(x, tree->root, 1);
    scanf("\n");

    return 0;
}
