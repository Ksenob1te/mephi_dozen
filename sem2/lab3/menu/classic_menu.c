#include "stdio.h"
#include "../methods.h"
#include "stdlib.h"

void send_command_menu() {
    printf("\033[0;33m____________________________________\n");
    printf("__________Here's your menu__________\n");
    printf("____Select one option from below____\n");
    printf("[1] Add new key\n");
    printf("[2] Add element by key\n");
    printf("[3] Delete key\n");
    printf("[4] Delete element\n");
    printf("[5] Search by key interval\n");
    printf("[6] Search by key\n");
    printf("[7] Search by version\n");
    printf("[0] Exit\n");
    printf("____________________________________\033[0m\n");
}

void menu(Table *mainTable) {
    void (*func[8])(const char *, Table *) = {add_key, add_element_key, delete_key, delete_element_version, search_interval,
                                search_key, search_element_version};
    printf("\033[H\033[J");
    send_command_menu();

    const char *file_name = "keyspaces";
//    FILE *file = fopen(file_name, "wb");
//    fclose(file);

    print_table(file_name, mainTable);
    while (1) {
        printf("\033[1;90mType command (number [0-8]):\033[0;0m\n");
        int command = 0;
        int x = scanf("%d", &command);
        if (x == EOF) {
            scanf("%*[^\n]*c");
            mainTable->remove(file_name, mainTable);
            return;
        }
        if (x == 0) {
            printf("Incorrect input, try again\n");
            scanf("%*[^\n]*c");
            continue;
        }
        switch (command) {
            case 1 ... 4:
                printf("\033[H\033[J");
                print_table(file_name, mainTable);
                (*func[command - 1])(file_name, mainTable);
                scanf("%*c%*[^\n]");
                printf("\033[H\033[J");
                send_command_menu();
                print_table(file_name, mainTable);
                break;
            case 5 ... 7:
                (*func[command - 1])(file_name, mainTable);
                break;
            case 0:
                free(mainTable);
                return;
            default:
                break;
        }
    }
}