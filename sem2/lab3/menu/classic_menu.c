#include "stdio.h"
#include "../table/table.h"

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

void menu() {
    Table *mainTable = create_table();
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
            case 1:
                mainList.fill(&mainList);
                break;
            case 2:
                printf("Type index and then number:\n");
                int index = 0;
                char* number = malloc(35 * sizeof(char));
                x = scanf("%d%34s", &index, number);
                if (x == EOF) {
                    scanf("%*[^\n]*c");
                    break;
                }
                if (x <= 1) {
                    printf("Incorrect input, try again\n");
                    printf("Or [-1] for command menu\n");
                    scanf("%*[^\n]*c");
                    break;
                }
                mainList.add_index(&mainList, index, number);
                break;
            case 3:
                printf("Type index:\n");
                index = 0;
                x = scanf("%d", &index);
                if (x == EOF) {
                    scanf("%*[^\n]*c");
                    break;
                }
                if (x <= 0) {
                    printf("Incorrect input, try again\n");
                    printf("Or [-1] for command menu\n");
                    scanf("%*[^\n]*c");
                    break;
                }
                mainList.remove_index(&mainList, index);
                break;
            case 4:
                ansList.free_array(&ansList);
                ansList = mainList.process(&mainList);
                printf("Result array: ");
                ansList.print(&ansList);
                break;
            case 5:
                printf("Your main array is: ");
                mainList.print(&mainList);
                break;
            case 6:
                printf("Your result array is: ");
                ansList.print(&ansList);
                break;
            case 0:
                mainList.free_array(&mainList);
                ansList.free_array(&ansList);
                return;
            case -1:
                send_command_menu();
                break;
            default:
                break;
        }
    }
}