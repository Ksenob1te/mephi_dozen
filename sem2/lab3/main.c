#include "methods.h"
#include "menu/classic_menu.h"
#include "stdio.h"
#ifdef _WIN32
    #define OS_WIN 1
    #include <windows.h>
#else
    #define OS_WIN 0
#endif

int main(void) {
    if (OS_WIN) SetConsoleOutputCP(CP_UTF8);
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
    menu(table);
}