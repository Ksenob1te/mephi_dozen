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
    node->parent = nul;

    return node;
}

void clear_node(Node *node) {
    Item *k;
    for (Item *i = node->info; i; i = k) {
        k = i->next;
//        free(i->info);
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
    child->parent = parent->parent;
    if (parent->parent->left == parent) parent->parent->left = child;
    else if (parent->parent->right == parent) parent->parent->right = child;
    parent->color = 1;
    parent->parent = child;

    parent->right = child->left;
    if (child->left->parent != NULL) child->left->parent = parent;
    child->left = parent;
    return child;
}

static Node *rst(Node *child, Node *parent) {
    child->color = parent->color;
    child->parent = parent->parent;
    if (parent->parent->left == parent) parent->parent->left = child;
    else if (parent->parent->right == parent) parent->parent->right = child;
    parent->color = 1;
    parent->parent = child;

    parent->left = child->right;
    if (child->right->parent != NULL) child->right->parent = parent;
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
    else if (tmp->key < dst->key) {
        if (dst->left == nul) tmp->parent = dst;
        dst->left = insert_node(nul, dst->left, tmp);
    }
    else if (tmp->key > dst->key){
        if (dst->right == nul) tmp->parent = dst;
        dst->right = insert_node(nul, dst->right, tmp);
    }
    else if (tmp->key == dst->key) {
        dst = move_item(dst, tmp);
    }

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

static Node * get_min_subtree (Node *nul, Node *current_root) {
    if (current_root == nul)
        return nul;
    while (current_root->left != nul)
        current_root = current_root->left;
    return current_root;
}

void balance_node(Node* nul, Node *parent_node, Node *brother_node, Tree *tree) {
    if (parent_node == nul) return;
    if (
            parent_node->color == 1 &&
            brother_node->color == 0 &&
            brother_node->left->color == 0 &&
            brother_node->right->color == 0
            ) {
        parent_node->color = 0;
        brother_node->color = 1;
        return;
    }
    if (
            parent_node->color == 1 &&
            brother_node->color == 0 &&
            brother_node->left->color == 1
            ) {
        if (parent_node->parent != nul && parent_node->parent->left == parent_node)
            parent_node->parent->left = rst(brother_node, parent_node);
        else if (parent_node->parent != nul && parent_node->parent->right == parent_node)
            parent_node->parent->right = rst(brother_node, parent_node);
        else if (parent_node == tree->root)
            tree->root = rst(brother_node, parent_node);
        parent_node->color = 0;

//        if (brother_node->left->color == 1 && brother_node->right->color == 1)
//            swap(nul, brother_node);
        return;
    }
    if (
            parent_node->color == 0 &&
            brother_node->color == 1 &&
            brother_node->right != nul &&
            brother_node->right->right->color == 0 &&
            brother_node->right->left->color == 0
            ) {
        if (parent_node->parent != nul && parent_node->parent->left == parent_node)
            parent_node->parent->left = rst(brother_node, parent_node);
        else if (parent_node->parent != nul && parent_node->parent->right == parent_node)
            parent_node->parent->right = rst(brother_node, parent_node);
        else if (parent_node == tree->root)
            tree->root = rst(brother_node, parent_node);

        parent_node->color = 0;
//        if (brother_node->left->color == 1 && brother_node->right->color == 1)
//             swap(nul, parent_node);
        return;
    }
    if (
            parent_node->color == 0 &&
            brother_node->color == 1 &&
            brother_node->right != nul &&
            brother_node->right->left->color == 1
            ) {
        brother_node->right->left->color = 0;
        if (parent_node->left == brother_node)
            parent_node->left = lst(brother_node, brother_node->right);
        if (parent_node->right == brother_node)
            parent_node->right = lst(brother_node, brother_node->right);

        if (parent_node->parent != nul && parent_node->parent->left == parent_node)
            parent_node->parent->left = rst(brother_node, parent_node);
        else if (parent_node->parent != nul && parent_node->parent->right == parent_node)
            parent_node->parent->right = rst(brother_node, parent_node);
        else if (parent_node == tree->root)
            tree->root = rst(brother_node, parent_node);
        parent_node->color = 0;
//        if (brother_node->left->color == 1 && brother_node->right->color == 1)
//            swap(nul, brother_node);
        return;
    }
    if (
            parent_node->color == 0 &&
            brother_node->color == 0 &&
            brother_node->right->color == 1
            ) {
        brother_node->right->color = 0;
        if (parent_node->left == brother_node)
            parent_node->left = lst(brother_node, brother_node->right);
        else if (parent_node->right == brother_node)
            parent_node->right = lst(brother_node, brother_node->right);

        if (parent_node->parent != nul && parent_node->parent->left == parent_node)
            parent_node->parent->left = rst(brother_node, parent_node);
        else if (parent_node->parent != nul && parent_node->parent->right == parent_node)
            parent_node->parent->right = rst(brother_node, parent_node);
        else if (parent_node == tree->root)
            tree->root = rst(brother_node, parent_node);
        swap(nul, brother_node);
        return;
    }
    if (
            parent_node->color == 0 &&
            brother_node->color == 0 &&
            brother_node->right->color == 0 &&
            brother_node->left->color == 0
            ) {
        brother_node->color = 1;
        if (parent_node->parent != nul && parent_node->parent->left == parent_node)
            balance_node(nul, parent_node->parent, parent_node->parent->right, tree);
        else if (parent_node->parent != nul && parent_node->parent->right == parent_node)
            balance_node(nul, parent_node->parent, parent_node->parent->left, tree);
        return;
    }
}

void remove_node(Node *nul, Tree *tree, Node *process_node) {
    if (process_node->left != nul && process_node->right != nul) {
        Node *find = get_min_subtree(nul, process_node->right);
        process_node->key = find->key;
        process_node->info = find->info;
        process_node = find;
    }
    if ((process_node->right == nul) + (process_node->left == nul) == 1) {
        if (process_node->right == nul) {
            process_node->key = process_node->left->key;
            process_node->info = process_node->left->info;
            process_node = process_node->left;
        } else {
            process_node->key = process_node->right->key;
            process_node->info = process_node->right->info;
            process_node = process_node->right;
        }
    }
    if (process_node->color == 1) {
        if (process_node->parent->right == process_node) process_node->parent->right = nul;
        else if (process_node->parent->left == process_node) process_node->parent->left = nul;
        clear_node(process_node);
        return;
    }
    if (process_node->color == 0) {
        if (process_node == tree->root) {
            tree->root = nul;
            clear_node(process_node);
        }
        Node *parent_node = process_node->parent;
        Node *brother_node = NULL;
        if (parent_node->right == process_node)  {
            parent_node->right = nul;
            brother_node = parent_node->left;
        }
        else if (parent_node->left == process_node) {
            parent_node->left = nul;
            brother_node = parent_node->right;
        }
        free(process_node);
        balance_node(nul, parent_node, brother_node, tree);

    }
}

int remove_item(Node *node, int index) {
    Item *insert_prev, *tmp;
    int search = 1;
    if (index == 0) {
        tmp = node->info->next;
        free(node->info);
        node->info = tmp;
    }
    for (insert_prev = node->info; insert_prev->next && search != index; insert_prev = insert_prev->next, search++);

    if (!insert_prev->next) return 0;
//    free(insert_prev->next->info);
    tmp = insert_prev->next->next;
    free(insert_prev->next);
    insert_prev->next = tmp;
    return 1;
}

void print_root(Node *nul, char *indent, Node *node, short last) {
    if (node == nul) {
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
            printf("\"%s\" ", i->info);
        }
        printf("\033[0m\n");
    } else {
        printf("\033[91m%llu\033[0m: \033[31m", node->key);
        for (Item *i = node->info; i; i = i->next) {
            printf("\"%s\" ", i->info);
        }
        printf("\033[0m\n");
    }


    char s[1000];
    strcpy(s, indent);
    if (node->right != nul) print_root(nul, indent, node->right, node->left != nul ? 0 : 1);
    if (node->left != nul) print_root(nul, s, node->left, 1);
}

static int count_decimals(ull data) {
    int result = 0;
    while (data > 0) {
        data /= 10;
        result += 1;
    }
    return result;
}

void preorder_traversal(Node *nul, Node *root, int limit) {
    if (root != nul) {
        int deci = count_decimals(root->key);
        if (deci == limit) {
            if (root->color == 0) {
                printf("\033[1;97m%llu\033[0m: \033[1;90m", root->key);
                for (Item *i = root->info; i; i = i->next) {
                    printf("\"%s\" ", i->info);
                }
                printf("\033[0m\n");
            } else {
                printf("\033[91m%llu\033[0m: \033[31m", root->key);
                for (Item *i = root->info; i; i = i->next) {
                    printf("\"%s\" ", i->info);
                }
                printf("\033[0m\n");
            }
        }
        if (deci >= limit)
            preorder_traversal(nul, root->left, limit);
        if (deci <= limit)
            preorder_traversal(nul, root->right, limit);
    }
}

Node * find_min_limit (Node *nul, Tree *tree, ull limit) {
    Node *current_root = tree->root;
    Node *last_root = nul;
    while (current_root != nul) {
        if (limit < current_root->key) {
            last_root = current_root;
            current_root = current_root->left;
        } else if (limit >= current_root->key) {
            current_root = current_root->right;
        }
    }
    if (last_root == nul) return NULL;
    return last_root;
}

Node * search_node(Node *nul, Tree *tree, ull key) {
    Node *current_root = tree->root;
    while (current_root != nul) {
        if (key > current_root->key) {
            current_root = current_root->right;
        } else if (key < current_root->key) {
            current_root = current_root->left;
        } else if (key == current_root->key) {
            return current_root;
        }
    }
    return NULL;
}

Tree * create_tree(Node *nul) {
    Tree *tree = malloc(sizeof(Tree));
    tree->root = nul;
    return tree;
}

void clear_tree(Node *nul, Node *node) {
    if (node == nul) return;
    Node *left = node->left;
    Node *right = node->right;
    clear_node(node);
    clear_tree(nul, left);
    clear_tree(nul, right);
}
