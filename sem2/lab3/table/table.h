#ifndef MEPHI_DOZEN_TABLE_H
#define MEPHI_DOZEN_TABLE_H

#define ull unsigned long long int

// Node struct
// >-=============================-<
typedef struct Node {
    ull release;
    ull info;
    struct Node *next;
    int (*remove) (struct Node *node);
} Node;

int removeNode (Node *node);
Node * create_node(ull info);
// >-=============================-<


// KeySpace struct
// >-=============================-<
typedef struct KeySpace {
    ull key;
    Node *node;
    struct KeySpace *link;

    int (*add_node) (struct KeySpace *key, Node *node);
    Node * (*find_node) (struct KeySpace *key, ull release);
    int (*remove_node) (struct KeySpace *key, Node *node);
    int (*remove) (struct KeySpace *key);
} KeySpace;

int add_node_keyspace (struct KeySpace *key, Node *node);
Node * find_node_keyspace (struct KeySpace *key, ull release);
int remove_node_keyspace (struct KeySpace *key, Node *node);
int remove_keyspace (struct KeySpace *key);
KeySpace * create_keyspace(ull key);
// >-=============================-<


// Table struct
// >-=============================-<
typedef struct Table {
    KeySpace *head;

    int (*add_key) (struct Table *table, KeySpace key);
    KeySpace (*find_key) (struct Table *table, ull key);
    int (*remove_key) (struct Table *table, ull key);
} Table;

int add_key_table (struct Table *table, KeySpace key);
KeySpace find_key_table (struct Table *table, ull key);
int remove_key_table (struct Table *table, ull key);
Table * createTable();
// >-=============================-<


#endif //MEPHI_DOZEN_TABLE_H
