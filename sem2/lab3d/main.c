#include "stdio.h"
#ifdef _WIN32
#include "windows.h"
#define select_settings() SetConsoleOutputCP(CP_UTF8)
#else
#define select_settings()
#endif

#include "table/table.h"
#include "methods.h"
#include "menu/classic_menu.h"

int main(void) {
    select_settings();
    printf("File: ");
    char *file_name = readline();
    Table *table = create_table(file_name);
//    int status = insert_element(table, "hello", 123);
//    printf("%d\n", status);
//    print_table(table);
//    scanf("\n");
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