#include "stdio.h"
#include "../table/table.h"
#include "../methods.h"

void send_command_menu() {
    printf("\033[0;33____________________________________\n");
    printf("__________Here's your menu__________\n");
    printf("____Select one option from below____\n");
    printf("[1] Print table\n");
    printf("[2] Add new key\n");
    printf("[3] Add element by key\n");
    printf("[4] Search by key interval\n");
    printf("[5] Search by key\n");
    printf("[6] Search by version\n");
    printf("[7] Delete key\n");
    printf("[8] Delete element\n");
    printf("[0] Exit\n");
    printf("____________________________________\033[0m\n");
}

void menu(Table *mainTable) {
    void (*func[8])(Table *) = {print_table, add_key, add_element_key, search_interval,
                                search_key, search_element_version, delete_key, delete_element_version};
//    memory_worker(&mainList, 10);
    send_command_menu();
    while (1) {
        printf("Type command (number [0-8]) or [-1] for command menu:\n");
        int command = 0;
        int x = scanf("%d", &command);
        if (x == EOF) {
            scanf("%*[^\n]*c");
            mainTable->remove(mainTable);
            return;
        }
        if (x == 0) {
            printf("Incorrect input, try again\n");
            printf("Or [-1] for command menu\n");
            scanf("%*[^\n]*c");
            continue;
        }
        switch (command) {
            case 1 ... 8:
                (*func[command - 1])(mainTable);
                break;
            case 0:
                mainTable->remove(mainTable);
                return;
            case -1:
                send_command_menu();
                break;
            default:
                break;
        }
    }
}