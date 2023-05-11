//
// Created by Ksenob1te on 12.05.2023.
//

#include "methods.h"

void print_tree(Node *nul, Tree *tree) {
    char x[1000] = "";
    print_root(nul, x, tree->root, 1);
}