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

KeySpace * find_key_table (struct Table *table, ull key) {
    if (!table) return NULL;
    KeySpace *current = table->head;
    for (; current && current->key != key; current = current->link);
    return current; // it'll return null if we reach end of array
}

int add_key_table (struct Table *table, KeySpace *key) {
    if (find_key_table(table, key->key)) return 0;
    key->link = table->head;
    table->head = key;
    return 1;
}


int remove_key_table (struct Table *table, ull key) {
    if (!table) return 0;
    KeySpace *prev_ptr = table->head;
    if (prev_ptr->key == key) {
        KeySpace *temp_ptr = prev_ptr->link;
        prev_ptr->remove(prev_ptr);
        table->head = temp_ptr;
        return 1;
    }
    for (; prev_ptr->link && prev_ptr->link->key != key; prev_ptr = prev_ptr->link);
    if (!prev_ptr->link) return 0;

    KeySpace *temp_ptr = (prev_ptr->link)->link;
    (prev_ptr->link)->remove(prev_ptr->link);
    prev_ptr->link = temp_ptr;
    return 1;
}

int remove_table(Table *table) {
    if (!table) return 0;
    KeySpace *ptr = table->head, *temp;
    for (;ptr; ptr = temp) {
        temp = ptr->link;
        ptr->remove(ptr);
    }
    free(table);
    return 1;
}

Table * find_key_range_table(Table *table, ull start, ull end) {
    Table * result = create_table();
    if (!table) return NULL;
    KeySpace *current = table->head;
    for (; current; current = current->link)
        if (current->key >= start && current->key <= end)
            result->add_key(result, current);
    return result;
}

Table * create_table() {
    Table *table = malloc(sizeof(Table));
    table->head = NULL;

    table->add_key = add_key_table;
    table->find_key = find_key_table;
    table->remove_key = remove_key_table;
    table->remove = remove_table;
    return table;
}

// >-=============================-<
