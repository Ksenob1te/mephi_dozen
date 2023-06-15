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


// обычная хеш таблица без перемешивания

int main(void) {
    select_settings();
    printf("File: ");
    char *file_name = readline();
    Table *table = create_table(file_name);
    menu(table);
    return 0;
}