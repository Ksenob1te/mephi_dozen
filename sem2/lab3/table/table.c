#include "table.h"
#include "stdlib.h"
#include "../file_worker/manager.h"
#include "string.h"


// Node struct
// >-=============================-<
static int removeNode(Node *node) {
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
KeySpace * create_keyspace(ull key) {
    KeySpace *keyspace = malloc(sizeof(KeySpace));
    keyspace->key = key;
    keyspace->link_offset = -1;
    keyspace->first_offset = -1;
    keyspace->last_release = -1;

    keyspace->add_node = write_node;
    keyspace->find_node = find_node_keyspace;
    keyspace->remove_node = remove_node_keyspace;
    keyspace->remove = remove_keyspace;

    return keyspace;
}

void select_funcs(KeySpace *key) {
    key->add_node = write_node;
    key->find_node = find_node_keyspace;
    key->remove_node = remove_node_keyspace;
    key->remove = remove_keyspace;
}

static int find_node_keyspace(FILE *file, const KeySpace *key, Node *node, ull release) {
    if (!key) return 1;
    int status;
    for (
            status = read_node(file, key->first_offset, node);
            !status && node->release != release;
            status = read_node(file, node->next_offset, node)
            );
    return status;
}

static int remove_node_keyspace (FILE *file, struct KeySpace *key, ull release) {
    if (!key) return 0;
    Node find_node;
    Node prev_node;
    long prev_block = key->first_offset;
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

static int remove_keyspace (FILE *file, long key_offset, KeySpace const *key) {
    if (!key) return 0;
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
    return 1;
}
// >-=============================-<


// Table struct
// >-=============================-<
static int find_key_table(FILE *file, const struct Table *table, KeySpace *keyspace, ull key) {
    if (!table) return 1;
    int status;
    for (
            status = read_keyspace(file, table->key_offset, keyspace);
            !status && keyspace->key != key;
            status = read_keyspace(file, keyspace->link_offset, keyspace)
            );
    return status;
}

long find_key_address(FILE *file, Table *table, KeySpace const *key) {
    if (!table) return 1;
    long result = -1;
    KeySpace keyspace;
    int status = read_keyspace(file, table->key_offset, &keyspace);
    if (keyspace.key == key->key) return table->key_offset;
    for (;
            !status && keyspace.key != key->key;
            status = read_keyspace(file, keyspace.link_offset, &keyspace)
            ) {
        result = keyspace.link_offset;
    }
    if (status) return -1;
    return result;
}


//int add_key_table (const char *input, struct Table *table, KeySpace *key) {
//    if (find_key_table(input, table, key->key)) return 0;
//    key->link = table->head;
//    table->head = key;
//    return 1;
//}


static int remove_key_table (FILE *file, struct Table *table, ull key) {
    if (!key) return 0;
    KeySpace find_key;
    KeySpace prev_key;
    long prev_block = table->key_offset;
    read_keyspace(file, table->key_offset, &find_key);
    if (find_key.key == key) {
        remove_keyspace(file, table->key_offset, &find_key);
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
    remove_keyspace(file, prev_key.link_offset, &find_key);
    prev_key.link_offset = find_key.link_offset;
    update_keyspace(file, prev_block, &prev_key);
    return 1;
}

static int remove_table(const char *input, Table *table) {
    if (!table) return 0;
    FILE *file = fopen(input, "rb");
    KeySpace key;
    int status = read_keyspace(file, table->key_offset, &key);
    remove_block(table->key_offset);
    for (;!status; status = read_keyspace(file, key.link_offset, &key)) {
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
Table * find_key_range_table(FILE *file, const char *tmp_filename, Table *table, ull start, ull end) {
    Table *result = create_table();
    FILE *tmp_file = fopen(tmp_filename, "wb");
    if (!table) return NULL;
    KeySpace current;
    int status = read_keyspace(file, table->key_offset, &current);
    write_table(tmp_file, result);
    long current_offset = 1;
    for (; !status; status = read_keyspace(file, current.link_offset, &current))
        if (current.key >= start && current.key <= end) {
            Node node;
            int status_node = read_node(file, current.first_offset, &node);

            fseek(tmp_file, 0, SEEK_END);
            long end_offset = ftell(tmp_file);
            end_offset = (end_offset % BLOCK_SIZE != 0 ? BLOCK_SIZE : 0) +
                    ((long) (end_offset / BLOCK_SIZE)) * BLOCK_SIZE;
            fseek(tmp_file, end_offset, SEEK_SET);
            current_offset = end_offset / BLOCK_SIZE;
            current.link_offset = result->key_offset;
            result->key_offset = end_offset / BLOCK_SIZE;
            current.first_offset = -1;
            current.last_release = -1;
            fwrite(&(current.key), sizeof(ull), 1, tmp_file);
            fwrite(&(current.first_offset), sizeof(long), 1, tmp_file);
            fwrite(&(current.link_offset), sizeof(long), 1, tmp_file);
            fwrite(&(current.last_release), sizeof(ull), 1, tmp_file);

            for (;!status_node; status_node = read_node(file, node.next_offset, &node)) {
                fseek(tmp_file, 0, SEEK_END);
                end_offset = ftell(tmp_file);
                end_offset = (end_offset % BLOCK_SIZE != 0 ? BLOCK_SIZE : 0) +
                             ((long) (end_offset / BLOCK_SIZE)) * BLOCK_SIZE;
                fseek(tmp_file, end_offset, SEEK_SET);
                (current.last_release)++;
                node.release = current.last_release;
                fwrite(&(node.info), sizeof(ull), 1, tmp_file);
                fwrite(&(current.first_offset), sizeof(long), 1, tmp_file);
                fwrite(&(node.release), sizeof(ull), 1, tmp_file);
                current.first_offset = end_offset / BLOCK_SIZE;
            }
            update_keyspace(tmp_file, current_offset, &current);
        }
    write_table(tmp_file, result);
    fclose(tmp_file);
    return result;
}

Table * create_table() {
    Table *table = malloc(sizeof(Table));
    table->key_offset = -1;

    table->add_key = write_keyspace;
    table->find_key = find_key_table;
    table->find_key_range = find_key_range_table;
    table->remove_key = remove_key_table;
    table->remove = remove_table;
    return table;
}

// >-=============================-<
