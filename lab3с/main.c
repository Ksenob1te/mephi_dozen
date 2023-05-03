#include "stdio.h"
#ifdef _WIN32
#include "windows.h"
#define select_settings() SetConsoleOutputCP(CP_UTF8)
#else
#define select_settings()
#endif

#include "table/table.h"
#include "menu/classic_menu.h"
#define TABLE_SIZE 10

int main(void) {
    select_settings();
    Table *table = create_table(TABLE_SIZE);
    menu(table);
//    insert_element(table, "hello", 100);
//    insert_element(table, "f", 101);
//    KeySpace *key = find_element(table, "f");
//    key->info = 0;
//    remove_element(table, "f");
//
//    printf("%llu\n", str_linear_hash("f", TABLE_SIZE));
//    print_table(table);
    return 0;
}