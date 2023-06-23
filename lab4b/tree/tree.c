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

static Node *lst(Node *parent) {
    Node *child = parent->right;
    child->color = parent->color;
    child->parent = parent->parent;
    if (parent->parent->left == parent) parent->parent->left = child;
    else if (parent->parent->right == parent) parent->parent->right = child;
    parent->color = 1;
    parent->parent = child;

    parent->right = child->left;
    if (child->left != NULL) child->left->parent = parent;
    child->left = parent;
    return child;
}

static Node *rst(Node *parent) {
    Node *child = parent->left;
    child->color = parent->color;
    child->parent = parent->parent;
    if (parent->parent->left == parent) parent->parent->left = child;
    else if (parent->parent->right == parent) parent->parent->right = child;
    parent->color = 1;
    parent->parent = child;

    parent->left = child->right;
    if (child->right != NULL) child->right->parent = parent;
    child->right = parent;
    return child;
}

static Node * swap(Node *nul, Node *dst) {
    if (dst->right != nul) dst->right->color = dst->right->color == 0 ? 1 : 0;
    if (dst->left != nul) dst->left->color = dst->left->color == 0 ? 1 : 0;
    dst->color = dst->color == 0 ? 1 : 0;
    return dst;
}

static Node * fixUp(Node *nul, Node *node) {
    if (node->right->color == 1 && node->left->color == 0)
        node = lst(node);
    if (node->left->color == 1 && node->left->left->color == 1)
        node = rst(node);
    if (node->left->color == 1 && node->right->color == 1)
        node = swap(nul, node);
    return node;
}

static Node * insert_node(Node *nul, Node *dst, Node *tmp) {
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

    return fixUp(nul, dst);
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

static Node * moveRedLeft(Node *nul, Node *h) {
    swap(nul, h);
    if (h->right && h->right->left == 0) {
        h->right = rst(h->right);
        h = lst(h);
        swap(nul, h);
    }
    return h;
}

static Node * moveRedRight(Node *nul, Node *h) {
    swap(nul, h);
    if (h->left && h->left->left == 0) {
        h = rst(h);
        swap(nul, h);
    }
    return h;
}

static Node * deleteMin(Node *nul, Node *h) {
    if (h->left == nul) return nul;
    if (h->left->color == 0 && h->left->left->color == 0)
        h = moveRedLeft(nul, h);
    h->left = deleteMin(nul, h->left);
    return fixUp(nul, h);
}

static Node * delete(Node *nul, Node *current_node, Node *process_node) {
    if (process_node->key < current_node->key) {
        if (current_node->left->color == 0 && current_node->right->color == 0)
            current_node = moveRedLeft(nul, current_node);
        current_node->left = delete(nul, current_node->left, process_node);
    } else {
        if (current_node->left->color == 1)
            current_node = rst(current_node);
        if (current_node->key == process_node->key && current_node->right == nul)
            return nul;
        if (current_node->right->color == 0 && current_node->right->left->color == 0)
            current_node = moveRedRight(nul, current_node);
        if (current_node->key == process_node->key) {
            current_node->info = get_min_subtree(nul, current_node->right)->info;
            current_node->key = get_min_subtree(nul, current_node->right)->key;
            current_node->right = deleteMin(nul, current_node->right);
        }
        else current_node->right = delete(nul, current_node->right, process_node);
    }
    return fixUp(nul, current_node);
}

void remove_node(Node *nul, Tree *tree, Node *process_node) {
    Node *root = delete(nul, tree->root, process_node);
    root->color = 0;
}

//void remove_node(Node *nul, Tree *tree, Node *process_node) {
//    if (process_node->left != nul && process_node->right != nul) {
//        Node *find = get_min_subtree(nul, process_node->right);
//        process_node->key = find->key;
//        process_node->info = find->info;
//        process_node = find;
//    }
//    if ((process_node->right == nul) + (process_node->left == nul) == 1) {
//        if (process_node->right == nul) {
//            process_node->key = process_node->left->key;
//            process_node->info = process_node->left->info;
//            process_node = process_node->left;
//        } else {
//            process_node->key = process_node->right->key;
//            process_node->info = process_node->right->info;
//            process_node = process_node->right;
//        }
//    }
//    if (process_node->color == 1) {
//        if (process_node->parent->right == process_node) process_node->parent->right = nul;
//        else if (process_node->parent->left == process_node) process_node->parent->left = nul;
//        free(process_node);
//        return;
//    }
//    if (process_node->color == 0) {
//        if (process_node == tree->root) {
//            tree->root = nul;
//            clear_node(process_node);
//            return;
//        }
//        Node *parent_node = process_node->parent;
//        Node *brother_node = NULL;
//        if (parent_node->right == process_node)  {
//            parent_node->right = nul;
//            brother_node = parent_node->left;
//        }
//        else if (parent_node->left == process_node) {
//            parent_node->left = nul;
//            brother_node = parent_node->right;
//        }
//        free(process_node);
//        balance_node(nul, parent_node, brother_node, tree);
//
//    }
//}

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
