//
// Created by Ksenob1te on 12.05.2023.
//

#include "methods.h"

void print_tree(Tree *tree) {
    char x[1000] = "";
    print_root(x, tree->root, 1);
}