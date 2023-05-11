#ifndef SEM1_LAB4_TREE_H
#define SEM1_LAB4_TREE_H

#define ull unsigned long long

typedef struct Node {
    ull key;
    struct Node *left;
    struct Node *right;

    struct Node *next;
    struct Node *previous;
    struct Node *parent;

    char ** info;
    int info_size;
} Node;

Node * create_node(ull key, char *info);

typedef struct Tree {
    Node *root;
} Tree;

Tree * create_tree();
void clear_tree(Node *node);
void add_node(Tree *tree, Node* process_node);
void remove_node(Tree *tree, Node *process_node);
int remove_item(Node *node, int index);
Node * search_node(Tree *tree, ull key);
void tree_traversal(Tree *tree, ull limit);
void print_root(char *indent, Node *node, short last);

#endif //SEM1_LAB4_TREE_H
