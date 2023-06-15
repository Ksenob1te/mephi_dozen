//#include "methods.h"
#include "menu/classic_menu.h"
#include "stdio.h"
#ifdef _WIN32
    #include "windows.h"
    #define select_settings() SetConsoleOutputCP(CP_UTF8)
#else
    #define select_settings()
#endif
#include "file_worker/manager.h"
//#include "table/table.h"


int main(void) {
//    printf("%llu\n", sizeof(NodePointer));
//    printf("%llu", sizeof(ull) + sizeof(ull) + sizeof(long) + sizeof(long));
    select_settings();
//    Table *table = create_table();
//    KeySpace *key1 = create_keyspace(1);
//    KeySpace *key2 = create_keyspace(2a);
//    table->add_key(table, key1);
//    table->add_key(table, key2);
//
//    for (int i = 0; i < 5; i++) {
//        Node *node = create_node(i);
//        key1->add_node(key1, node);
//    }
//    for (int i = 4; i < 9; i++) {
//        Node *node = create_node(i);
//        key2->add_node(key2, node);
//    }

    Table* table = create_table();
    FILE *file = fopen("keyspaces", "rb+");
    read_table(file, table);
    fclose(file);
//    KeySpace key = {123, -1, -1, -1};
//    printf("%llu\n", sizeof(ull) * 2a + sizeof(long) * 2a);
//    write_keyspace(file, table, &key);
//    for (int i = 1; i < 5; i++) {
//        key.key = i;
//        write_keyspace(file, table, &key);
//    }
//    read_keyspace(file, 0, &key);
//    Node node = {123, 0, -1};
//    write_node(file, &key, &node);
//    for (int i = 1; i < 5; i++) {
//        node.info = i;
//        write_node(file, &key, &node);
//    }
//    update_keyspace(file, 0, &key);
//    fclose(file);
//
//    print_table("keyspaces", table);
//    file = fopen("keyspaces", "rb+");
//    read_keyspace(file, 1, &key);
//
//    table->remove_key(file, table, 123);
//
//    key.key = 98;
//    table->add_key(file, table, &key);
//    fclose(file);
//    print_table("keyspaces", table);
//
//    scanf("\n");
//    KeySpace key_test;
//    Node node_test;

//    file = fopen("keyspaces", "rb");
//    read_keyspace(file, 0, &key_test);
//    fclose(file);
//
//    find_node_keyspace("keyspaces", &key_test, &node_test, 2a);
//    file = fopen("keyspaces", "r");
//    read_table(file, table);
//    print_table(table);
//    scanf("\n");
    menu(table);
    return 0;
}