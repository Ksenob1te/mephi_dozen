#include "stdio.h"
#include "../methods.h"
#include "stdlib.h"

void send_command_menu() {
    printf("\033[0;33m____________________________________\n");
    printf("__________Here's your menu__________\n");
    printf("____Select one option from below____\n");
    printf("[1] Add new key\n");
    printf("[2] Delete key\n");
    printf("[3] Search by key\n");
    printf("[0] Exit\n");
    printf("____________________________________\033[0m\n");
}

void menu(Table *mainTable) {
    void (*func[3])(Table *) = {add_key, delete_key, search_key};
    printf("\033[H\033[J");
    send_command_menu();

//    const char *file_name = "keyspaces";
//    FILE *file = fopen(file_name, "wb");
//    fclose(file);

    print_table(mainTable);
    while (1) {
        printf("\033[1;90mType command (number [0-3]):\033[0;0m\n");
        int command = 0;
        int x = scanf("%d", &command);
        if (x == EOF) {
            scanf("%*[^\n]*c");
//            clear_table(mainTable);
            return;
        }
        if (x == 0) {
            printf("Incorrect input, try again\n");
            scanf("%*[^\n]*c");
            continue;
        }
        switch (command) {
            case 1 ... 2:
                printf("\033[H\033[J");
                print_table(mainTable);
                (*func[command - 1])(mainTable);
                scanf("%*c%*[^\n]");
                printf("\033[H\033[J");
                send_command_menu();
                print_table(mainTable);
                break;
            case 3:
                (*func[command - 1])(mainTable);
                break;
            case 0:
//                clear_table(mainTable);
                return;
            default:
                break;
        }
    }
}