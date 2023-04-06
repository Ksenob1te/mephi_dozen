//#include "methods.h"
//#include "menu/classic_menu.h"
#include "stdio.h"
#ifdef _WIN32
    #include "windows.h"
    #define select_settings() SetConsoleOutputCP(CP_UTF8)
#else
    #define select_settings()
#endif
#include "file_worker/manager.h"
//#include "table/table.h"

void print_table(const char *input, Table *table) {
    FILE *file = fopen(input, "rb");
    printf("\033[0;33m.\033[0m\n");
    KeySpace current;
    int status = read_keyspace(file, table->key_offset, &current);
    for (; !status; status = read_keyspace(file, current.link_offset, &current)) {
        if (current.link_offset != -1) printf("├"); else printf("└");
        printf("── \033[0;33m%llu\033[0m\n", current.key);
        Node node;
        int status_node = read_node(file, current.first_offset, &node);
        for (; !status_node; status_node = read_node(file, node.next_offset, &node)) {
            if (current.link_offset != -1) printf("│"); else printf(" ");
            printf("   ");
            if (node.next_offset != -1) printf("├"); else printf("└");
            printf("── \033[1;90m%llu:\033[0m%llu\n", node.release, node.info);
        }
    }
}

int main(void) {
//    printf("%llu\n", sizeof(NodePointer));
//    printf("%llu", sizeof(ull) + sizeof(ull) + sizeof(long) + sizeof(long));
    select_settings();
//    Table *table = create_table();
//    KeySpace *key1 = create_keyspace(1);
//    KeySpace *key2 = create_keyspace(2);
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

    FILE *file = fopen("keyspaces", "wb+");
    Table table = {-1};
    KeySpace key = {123, -1, -1, -1};
    printf("%llu\n", sizeof(ull) * 2 + sizeof(long) * 2);
    write_keyspace(file, &table, &key);
    for (int i = 1; i < 5; i++) {
        key.key = i;
        write_keyspace(file, &table, &key);
    }
    read_keyspace(file, 0, &key);
    Node node = {123, 0, -1};
    write_node(file, &key, &node);
    for (int i = 1; i < 5; i++) {
        node.info = i;
        write_node(file, &key, &node);
    }
    update_keyspace(file, 0, &key);
    fclose(file);


    print_table("keyspaces", &table);
    scanf("\n");
//    KeySpace key_test;
//    Node node_test;

//    file = fopen("keyspaces", "rb");
//    read_keyspace(file, 0, &key_test);
//    fclose(file);
//
//    find_node_keyspace("keyspaces", &key_test, &node_test, 2);
//    file = fopen("keyspaces", "r");
//    read_table(file, table);
//    print_table(table);
//    scanf("\n");
//    menu(table);
}