#include "stdlib.h"
#include "tree.h"
#include "stdio.h"
#include "string.h"

Node * create_node(ull key, char *info) {
    Node *node = malloc(sizeof(Node));
    node->info = malloc(sizeof(char *));

    node->info_size = 1;
    (node->info)[0] = info;
    node->key = key;

    node->next = NULL;
    node->previous = NULL;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;

    return node;
}

void clear_node(Node *node) {
//    for (int i = 0; i < node->info_size; i++) {
//        free((node->info)[i]);
//    }
    free(node->info);
    free(node);
}

static Node * move_item(Node *dst, Node *tmp) {
    (dst->info_size)++;
    dst->info = realloc(dst->info, sizeof(char *) * (dst->info_size));
    (dst->info)[dst->info_size - 1] = (tmp->info)[tmp->info_size - 1];

    free(tmp->info);
    free(tmp);
    return dst;
}

static Node * get_max_subtree (Node *current_root) {
    if (current_root == NULL)
        return NULL;
    while (current_root->right != NULL)
        current_root = current_root->right;
    return current_root;
}

static Node * get_min_subtree (Node *current_root) {
    if (current_root == NULL)
        return NULL;
    while (current_root->left != NULL)
        current_root = current_root->left;
    return current_root;
}

static Node * find_previous (Node *process_node) {
    Node *ptr = NULL;
    if (process_node->left == NULL) {
        ptr = process_node->parent;
        while (ptr && ptr->left == process_node) {
            process_node = ptr;
            ptr = process_node->parent;
        }
        return ptr;
    } else return get_max_subtree(process_node->left);
}

static Node * find_next (Node *process_node) {
    Node *ptr = NULL;
    if (process_node->right == NULL) {
        ptr = process_node->parent;
        while (ptr && ptr->right == process_node) {
            process_node = ptr;
            ptr = process_node->parent;
        }
        return ptr;
    } else return get_min_subtree(process_node->right);
}

void add_node(Tree *tree, Node* process_node) {
    if (tree->root == NULL) {
        tree->root = process_node;
        return;
    }
    Node *current_root = tree->root;
    while (current_root != NULL) {
        if (process_node->key > current_root->key) {
            if (current_root->right != NULL)
                current_root = current_root->right;
            else {
                process_node->parent = current_root;
                current_root->right = process_node;
                break;
            }
        } else if (process_node->key < current_root->key) {
            if (current_root->left != NULL)
                current_root = current_root->left;
            else {
                process_node->parent = current_root;
                current_root->left = process_node;
                break;
            }
        }
        else if (process_node->key == current_root->key) {
            process_node = move_item(current_root, process_node);
            current_root = NULL;
        }
    }
    if (current_root == NULL) return;
    Node *prev_tmp = find_previous(process_node);
    Node *next_tmp = find_next(process_node);
    process_node->previous = prev_tmp;
    process_node->next = next_tmp;
    if (prev_tmp) prev_tmp->next = process_node;
    if (next_tmp) next_tmp->previous = process_node;
}

void remove_node(Tree *tree, Node *process_node) {
    if (process_node->left == NULL || process_node->right == NULL) {
        Node *branch = process_node->left != NULL ? process_node->left : process_node->right;
        if (tree->root == process_node) {
            tree->root = branch;
            clear_node(process_node);
            return;
        }
        Node *parent = process_node->parent;
        if (parent->left == process_node)
            parent->left = branch;
        else
            parent->right = branch;

        if (branch) branch->parent = parent;

        if (process_node->next) process_node->next->previous = process_node->previous;
        if (process_node->previous) process_node->previous->next = process_node->next;

        clear_node(process_node);
        return;
    } else {
        Node *removal = get_min_subtree(process_node->right);

        process_node->key = removal->key;
//        for (int i = 0; i < process_node->info_size; i++)
//            free((process_node->info)[i]);
        free(process_node->info);
        process_node->info = removal->info;
        process_node->info_size = removal->info_size;

        if (removal->next != process_node) {
            process_node->next = removal->next;
            if (removal->next) removal->next->previous = process_node;
        }
        if (removal->previous != process_node)  {
            process_node->previous = removal->previous;
            if (removal->previous) removal->previous->next = process_node;
        }

        if (removal->right == NULL) {
            removal->parent->left = NULL;
            free(removal);
        } else {
            Node *branch = removal->right;
            branch->parent = removal->parent;
            removal->parent->right = branch;
            free(removal);
        }
    }
}

void tree_traversal(Tree *tree, ull limit) {
    Node *max = get_max_subtree(tree->root);
    while (max && max->key > limit) {
        printf("%llu ", max->key);
        max = max->previous;
    }
    printf("\n");
}

void print_root(char *indent, Node *node, short last) {
    printf("\033[0;33m%s", indent);
    if (last) {
        printf("└── ");
        strcat(indent, "    ");
    }
    else {
        printf("├── ");
        strcat(indent, "│   ");
    }
    printf("\033[1;90m%llu\033[0m\n", node->key);

    char s[1000];
    strcpy(s, indent);
    if (node->left) print_root(indent, node->left, node->right ? 0 : 1);
    if (node->right) print_root(s, node->right, 1);
}

Tree * create_tree() {
    Tree *tree = malloc(sizeof(Tree));
    tree->root = NULL;
    return tree;
}
