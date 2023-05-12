#ifndef SEM1_LAB4_TREE_H
#define SEM1_LAB4_TREE_H

#define ull unsigned long long

typedef struct Item {
    char *info;
    struct Item *next;
} Item;

typedef struct Node {
    ull key;
    int color;
    struct Node *left;
    struct Node *right;
    struct Node *parent;

    Item *info;
} Node;

Node * create_node(Node *nul, ull key, char *info);

typedef struct Tree {
    Node *root;
} Tree;

Tree * create_tree(Node *nul);
//void clear_tree(Node *node);
void add_node(Node *nul, Tree *tree, Node* process_node);
//void remove_node(Tree *tree, Node *process_node);
//int remove_item(Node *node, int index);
//Node * search_node(Tree *tree, ull key);
//void tree_traversal(Tree *tree, ull limit);
void print_root(Node *nul, char *indent, Node *node, short last);

#endif //SEM1_LAB4_TREE_H
