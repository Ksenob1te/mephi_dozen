#ifndef MEPHI_DOZEN_TABLE_H
#define MEPHI_DOZEN_TABLE_H

#define ull unsigned long long int
#include "stdio.h"

// Node struct
// >-=============================-<
typedef struct Node {
    ull info;
    ull release;
    long next_offset;
    int (*remove) (struct Node *node);
} Node;

static int removeNode (Node *node);
Node * create_node(ull info);
// >-=============================-<


// KeySpace struct
// >-=============================-<
typedef struct KeySpace {
    ull key;
    long first_offset;
    long link_offset;
    ull last_release;

    long (*add_node) (FILE *file, struct KeySpace *key, Node *node);
    int (*find_node) (FILE *file, const struct KeySpace *key, Node *node, ull release);
    int (*remove_node) (FILE *file, struct KeySpace *key, ull release);
    int (*remove) (FILE *file, long key_offset, struct KeySpace const *key);
} KeySpace;

static int find_node_keyspace(FILE *file, const KeySpace *key, Node *node, ull release);
static int remove_node_keyspace (FILE *file, struct KeySpace *key, ull release);
static int remove_keyspace (FILE *file, long key_offset, KeySpace const *key);
void select_funcs(KeySpace *key);
KeySpace * create_keyspace(ull key);
// >-=============================-<


// Table struct
// >-=============================-<
typedef struct Table {
    long key_offset;

    long (*add_key) (FILE *file, struct Table *table, KeySpace *key);
    int (*find_key) (FILE *file, const struct Table *table, KeySpace *keyspace, ull key);
    struct Table * (*find_key_range) (FILE *file, const char *tmp_filename, struct Table *table, ull start, ull end);
    int (*remove_key) (FILE *file, struct Table *table, ull key);
    int (*remove) (const char *input, struct Table *table);
} Table;

static int find_key_table(FILE *file, const struct Table *table, KeySpace *keyspace, ull key);
long find_key_address(FILE *file, Table *table, KeySpace const *key);
Table * find_key_range_table(FILE *file, const char *tmp_filename, struct Table *table, ull start, ull end);
static int remove_key_table (FILE *file, struct Table *table, ull key);
static int remove_table(const char *input, Table *table);
Table * create_table();
// >-=============================-<


#endif //MEPHI_DOZEN_TABLE_H
