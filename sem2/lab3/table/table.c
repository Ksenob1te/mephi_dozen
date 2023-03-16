#include "table.h"
#include "stdlib.h"


// Node struct
// >-=============================-<
int removeNode(Node *node) {
    free(node);
    return 1;
}

Node * create_node(ull info) {
    Node *node = malloc(sizeof(Node));
    node->release = -1;
    node->info = info;
    node->next = NULL;

    node->remove = removeNode;
    return node;
}
// >-=============================-<


// KeySpace struct
// >-=============================-<
int add_node_keyspace (struct KeySpace *key, Node *node) {
    if (!key || !node) return 0;
    if (!key->node) {key->node = node; return 1;}

    Node *last_node;
    for (last_node = key->node; last_node->next; last_node = last_node->next);
    last_node->next = node;
    return 1;
}

Node * find_node_keyspace (struct KeySpace *key, ull release) {
    if (!key) return NULL;
    Node *find_node;
    for (find_node = key->node; find_node && find_node->release != release; find_node = find_node->next);
    return find_node;
}

int remove_node_keyspace (struct KeySpace *key, Node *node) {
    if (!key || !node) return 0;
    Node *find_node;
    for (find_node = key->node; find_node && find_node->next != node; find_node = find_node->next);

    if (!find_node) return 0;
    find_node->next = node->next;
    removeNode(node);
    return 1;
}

int remove_keyspace (struct KeySpace *key) {
    if (!key) return 0;
    Node *temp;
    for (Node *node = key->node; node; node = temp) {
        temp = node->next;
        removeNode(node);
    }
    free(key);
    return 1;
}

KeySpace * create_keyspace(ull key) {
    KeySpace *keyspace = malloc(sizeof(KeySpace));
    keyspace->key = key;
    keyspace->node = NULL;
    keyspace->link = NULL;

    keyspace->add_node = add_node_keyspace;
    keyspace->find_node = find_node_keyspace;
    keyspace->remove_node = remove_node_keyspace;
    keyspace->remove = remove_keyspace;

    return keyspace;
}
// >-=============================-<


// Table struct
// >-=============================-<


