#include "methods.h"

int main(void) {
    Table *table = create_table();
    KeySpace *key1 = create_keyspace(1);
    KeySpace *key2 = create_keyspace(2);
    table->add_key(table, key1);
    table->add_key(table, key2);

    for (int i = 0; i < 5; i++) {
        Node *node = create_node(i);
        key1->add_node(key1, node);
    }
    for (int i = 4; i < 9; i++) {
        Node *node = create_node(i);
        key2->add_node(key2, node);
    }
    print_table(table);
}