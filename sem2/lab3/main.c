#include "methods.h"
#include "menu/classic_menu.h"
#include "stdio.h"
#ifdef _WIN32
    #include "windows.h"
    #define select_settings() SetConsoleOutputCP(CP_UTF8)
#else
    #define select_settings()
#endif
#include "file_worker/manager.h"

int main(void) {
    select_settings();
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

//    FILE *file = fopen("keyspaces", "w");
//    write_table(file, table);
//    fclose(file);
//
//    file = fopen("keyspaces", "r");
//    read_table(file, table);
//    fclose(file);
//    print_table(table);
//    scanf("\n");
    menu(table);
}