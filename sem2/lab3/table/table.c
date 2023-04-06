#include "table.h"
#include "stdlib.h"
#include "../file_worker/manager.h"


// Node struct
// >-=============================-<
int removeNode(Node *node) {
    free(node);
    return 1;
}

Node * create_node(ull info) {
    Node *node = malloc(sizeof(Node));
    node->release = 0;
    node->info = info;
    node->next_offset = -1;

    node->remove = removeNode;
    return node;
}
// >-=============================-<


// KeySpace struct
// >-=============================-<
//int add_node_keyspace (char *input, struct KeySpace *key, Node *node) {
//    if (!key || !node) return 0;
//    FILE *file = fopen(input, "r+b");
//    if (key->first_offset == -1) {
//        long offset = write_node(file, key, node);
//        key->first_offset = offset;
//        return 2;
//    }
//
//    node->next = key->node;
//    key->node = node;
//    (key->last_release)++;
//    node->release = key->last_release;
//    return 1;
//}

int find_node_keyspace(const char *input, const KeySpace *key, Node *node, ull release) {
    if (!key) return 1;
    FILE *file = fopen(input, "rb");
    int status;
    for (
            status = read_node(file, key->first_offset, node);
            !status && node->release != release;
            status = read_node(file, node->next_offset, node)
            );
    fclose(file);
    return status;
}

int remove_node_keyspace (const char *input, struct KeySpace *key, ull release) {
    if (!key) return 0;
    FILE *file = fopen(input, "r+b");
    Node find_node;
    Node prev_node;
    ull prev_block = key->first_offset;
    read_node(file, key->first_offset, &find_node);
    if (find_node.release == release) {
        remove_block(key->first_offset);
        key->first_offset = find_node.next_offset;
        return 2;
    }
    prev_node = find_node;
    int status = read_node(file, find_node.next_offset, &find_node);
    while (!status && find_node.release != release) {
        prev_block = prev_node.next_offset;
        prev_node = find_node;
        status = read_node(file, find_node.next_offset, &find_node);
    }
    if (status) return 0;
    remove_block(prev_node.next_offset);
    prev_node.next_offset = find_node.next_offset;
    update_node(file, prev_block, &prev_node);
    return 1;
}

int remove_keyspace (const char *input, long key_offset, struct KeySpace *key) {
    if (!key) return 0;
    FILE *file = fopen(input, "rb");
    int status;
    Node node;
    remove_block(key->first_offset);
    for (
            status = read_node(file, key->first_offset, &node);
            !status;
            status = read_node(file, node.next_offset, &node)
            ) {
        remove_block(node.next_offset);
    }
    remove_block(key_offset);
    fclose(file);
    return 1;
}

KeySpace * create_keyspace(ull key) {
    KeySpace *keyspace = malloc(sizeof(KeySpace));
    keyspace->key = key;
    keyspace->first_offset = -1;
    keyspace->last_release = -1;
    keyspace->link_offset = -1;

//    keyspace->add_node = add_node_keyspace;
//    keyspace->find_node = find_node_keyspace;
//    keyspace->remove_node = remove_node_keyspace;
//    keyspace->remove = remove_keyspace;

    return keyspace;
}
// >-=============================-<


// Table struct
// >-=============================-<
int find_key_table(const char *input, const struct Table *table, KeySpace *keyspace, const ull key) {
    if (!table) return 0;
    FILE *file = fopen(input, "rb");
    int status;
    for (
            status = read_keyspace(file, table->key_offset, keyspace);
            !status && keyspace->key != key;
            status = read_keyspace(file, keyspace->link_offset, keyspace)
            );
    fclose(file);
    return 1;
}

//int add_key_table (const char *input, struct Table *table, KeySpace *key) {
//    if (find_key_table(input, table, key->key)) return 0;
//    key->link = table->head;
//    table->head = key;
//    return 1;
//}


int remove_key_table (const char *input, struct Table *table, ull key) {
    if (!key) return 0;
    FILE *file = fopen(input, "r+b");
    KeySpace find_key;
    KeySpace prev_key;
    ull prev_block = table->key_offset;
    read_keyspace(file, table->key_offset, &find_key);
    if (find_key.key == key) {
        remove_block(table->key_offset);
        table->key_offset = find_key.link_offset;
        return 2;
    }
    prev_key = find_key;
    int status = read_keyspace(file, find_key.link_offset, &find_key);
    while (!status && find_key.key != key) {
        prev_block = prev_key.link_offset;
        prev_key = find_key;
        status = read_keyspace(file, find_key.link_offset, &find_key);
    }
    if (status) return 0;
    remove_block(prev_key.link_offset);
    prev_key.link_offset = find_key.link_offset;
    update_keyspace(file, prev_block, &prev_key);
    return 1;
}

int remove_table(const char *input, Table *table) {
    if (!table) return 0;
    FILE *file = fopen(input, "rb");
    KeySpace key;
    int status = read_keyspace(file, table->key_offset, &key);
    remove_block(table->key_offset);
    for (;status; status = read_keyspace(file, key.link_offset, &key)) {
        int status_key;
        Node node;
        remove_block(key.first_offset);
        for (
                status_key = read_node(file, key.first_offset, &node);
                !status_key;
                status_key = read_node(file, node.next_offset, &node)
                ) {
            remove_block(node.next_offset);
        }
        remove_block(key.link_offset);
    }
    free(table);
    return 1;
}

//KeySpace * copy_keyspace(KeySpace *key) {
//    KeySpace *key_cpy = create_keyspace(key->key);
//    Node *last_node = NULL;
//    ull release = key->last_release;
//    for (Node *find_node = key->node; find_node; find_node = find_node->next) {
//        Node *node = create_node(find_node->info);
//        if (!key_cpy->node) key_cpy->node = node;
//        if (last_node) last_node->next = node;
//        last_node = node;
//        node->release = release;
//        release--;
//    }
//    return key_cpy;
//}
//
//Table * find_key_range_table(Table *table, ull start, ull end) {
//    Table * result = create_table();
//    if (!table) return NULL;
//    KeySpace *current = table->head;
//    for (; current; current = current->link)
//        if (current->key >= start && current->key <= end) {
//            result->add_key(result, copy_keyspace(current));
//        }
//    return result;
//}
//
//Table * create_table() {
//    Table *table = malloc(sizeof(Table));
//    table->head = NULL;
//
//    table->add_key = add_key_table;
//    table->find_key = find_key_table;
//    table->find_key_range = find_key_range_table;
//    table->remove_key = remove_key_table;
//    table->remove = remove_table;
//    return table;
//}

// >-=============================-<
