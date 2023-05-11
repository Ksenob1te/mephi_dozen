#include "stdlib.h"
#include "tree.h"
#include "stdio.h"
#include "string.h"

Node * create_node(Node *nul, ull key, char *info) {
    Node *node = malloc(sizeof(Node));
    node->info = malloc(sizeof(Item));
    node->info->info = info;
    node->info->next = NULL;

    node->key = key;
    node->color = 0;

    node->left = nul;
    node->right = nul;

    return node;
}

void clear_node(Node *node) {
    Item *k;
    for (Item *i = node->info; i; i = k) {
        k = i->next;
        free(i->info);
        free(i);
    }
    free(node);
}

static Node * move_item(Node *dst, Node *tmp) {
    tmp->info->next = dst->info;
    dst->info = tmp->info;

    free(tmp);
    return dst;
}

static Node *lst(Node *parent, Node *child) {
    child->color = parent->color;
    parent->color = 1;
    parent->right = child->left;
    child->left = parent;
    return child;
}

static Node *rst(Node *child, Node *parent) {
    child->color = parent->color;
    parent->color = 1;
    parent->left = child->right;
    child->right = parent;
    return child;
}

static Node *swap(Node *nul, Node *dst) {
    if (dst->right != nul) dst->right->color = dst->right->color == 0 ? 1 : 0;
    if (dst->left != nul) dst->left->color = dst->left->color == 0 ? 1 : 0;
    dst->color = dst->color == 0 ? 1 : 0;
    return dst;
}

static Node *insert_node(Node *nul, Node *dst, Node *tmp) {
    if (dst == nul) return tmp;
    else if (tmp->key < dst->key) dst->left = insert_node(nul, dst->left, tmp);
    else if (tmp->key > dst->key) dst->right = insert_node(nul, dst->right, tmp);

    if (dst->right->color == 1 && dst->left->color == 0)
        dst = lst(dst, dst->right);
    if (dst->left->color == 1 && dst->left->left->color == 1)
        dst = rst(dst->left, dst);
    if (dst->left->color == 1 && dst->right->color == 1)
        dst = swap(nul, dst);
    return dst;
}

void add_node(Node *nul, Tree *tree, Node* process_node) {
    if (tree->root == nul) {
        tree->root = process_node;
        return;
    }
    process_node->color = 1;
    Node *current_root = tree->root;
    current_root = insert_node(nul, current_root, process_node);
    current_root->color = 0;
    tree->root = current_root;
}



//void remove_node(Tree *tree, Node *process_node) {
//    if (process_node->left == NULL || process_node->right == NULL) {
//        Node *branch = process_node->left != NULL ? process_node->left : process_node->right;
//        if (tree->root == process_node) {
//            tree->root = branch;
//            clear_node(process_node);
//            return;
//        }
//        Node *parent = process_node->parent;
//        if (parent->left == process_node)
//            parent->left = branch;
//        else
//            parent->right = branch;
//
//        if (branch) branch->parent = parent;
//
//        if (process_node->next) process_node->next->previous = process_node->previous;
//        if (process_node->previous) process_node->previous->next = process_node->next;
//
//        clear_node(process_node);
//        return;
//    } else {
//        Node *removal = get_min_subtree(process_node->right);
//
//        process_node->key = removal->key;
//        for (int i = 0; i < process_node->info_size; i++)
//            free((process_node->info)[i]);
//        free(process_node->info);
//        process_node->info = removal->info;
//        process_node->info_size = removal->info_size;
//
//        if (removal->next != process_node) {
//            process_node->next = removal->next;
//            if (removal->next) removal->next->previous = process_node;
//        }
//        if (removal->previous != process_node)  {
//            process_node->previous = removal->previous;
//            if (removal->previous) removal->previous->next = process_node;
//        }
//
//        if (removal->right == NULL) {
//            if (removal->parent->right == removal)
//                removal->parent->right = NULL;
//            else
//                removal->parent->left = NULL;
//            free(removal);
//        } else {
//            Node *branch = removal->right;
//            branch->parent = removal->parent;
//            removal->parent->right = branch;
//            free(removal);
//        }
//    }
//}
//
//int remove_item(Node *node, int index) {
//    if (index >= node->info_size || index < 0) return 0;
//    free((node->info)[index]);
//    (node->info)[index] = (node->info)[node->info_size - 1];
//    (node->info_size)--;
//    return 1;
//}
//
//void tree_traversal(Tree *tree, ull limit) {
//    Node *max = get_max_subtree(tree->root);
//    while (max && max->key > limit) {
//        printf("\033[1;97m%llu\033[0m: \033[1;90m", max->key);
//        for (int i = 0; i < max->info_size; i++) {
//            printf("\"%s\" ", (max->info)[i]);
//        }
//        printf("\033[0m\n");
//        max = max->previous;
//    }
//    printf("\n");
//}
//
void print_root(char *indent, Node *node, short last) {
    if (!node) {
        printf("\033[1;97m(EMPTY)\033[0m\n");
        return;
    }
    printf("\033[0;33m%s", indent);
    if (last) {
        printf("└── ");
        strcat(indent, "    ");
    }
    else {
        printf("├── ");
        strcat(indent, "│   ");
    }
    if (node->color == 0) {
        printf("\033[1;97m%llu\033[0m: \033[1;90m", node->key);
        for (Item *i = node->info; i; i = i->next) {
            printf("\"%s\" ", node->info);
        }
        printf("\033[0m\n");
    } else {
        printf("\033[91m%llu\033[0m: \033[31m", node->key);
        for (Item *i = node->info; i; i = i->next) {
            printf("\"%s\" ", node->info);
        }
        printf("\033[0m\n");
    }


    char s[1000];
    strcpy(s, indent);
    if (node->left) print_root(indent, node->left, node->right ? 0 : 1);
    if (node->right) print_root(s, node->right, 1);
}
//
//Node * search_node(Tree *tree, ull key) {
//    Node *current_root = tree->root;
//    while (current_root != NULL) {
//        if (key > current_root->key) {
//            current_root = current_root->right;
//        } else if (key < current_root->key) {
//            current_root = current_root->left;
//        } else if (key == current_root->key) {
//            return current_root;
//        }
//    }
//    return NULL;
//}
//
Tree * create_tree(Node *nul) {
    Tree *tree = malloc(sizeof(Tree));
    tree->root = nul;
    return tree;
}
//
//void clear_tree(Node *node) {
//    if (!node) return;
//    Node *left = node->left;
//    Node *right = node->right;
//    clear_node(node);
//    clear_tree(left);
//    clear_tree(right);
//}
