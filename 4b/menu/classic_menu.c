#include "stdio.h"
#include "../methods.h"
#include "stdlib.h"

void send_command_menu() {
    printf("\033[0;33m____________________________________\n");
    printf("__________Here's your menu__________\n");
    printf("____Select one option from below____\n");
    printf("[1] Add\n");
    printf("[2a] Delete\n");
    printf("[3] Tree traversal\n");
    printf("[4] Search\n");
    printf("[5] Special search\n");
    printf("[0] Exit\n");
    printf("____________________________________\033[0m\n");
}

void menu(Node *nul, Tree *tree) {
    void (*func[5])(Node *, Tree *) = {add_node_tree, remove_node_tree, traversal_limit_tree, search_node_tree, sp_search_node_tree};
    printf("\033[H\033[J");
    send_command_menu();

//    const char *file_name = "keyspaces";
//    FILE *file = fopen(file_name, "wb");
//    fclose(file);

    print_tree(nul, tree);
    while (1) {
        printf("\033[1;90mType command (number [0-5]):\033[0;0m\n");
        int command = 0;
        int x = scanf("%d", &command);
        if (x == EOF) {
            scanf("%*[^\n]*c");
            print_tree(nul, tree);
            clear_tree(nul, tree->root);
            free(tree);
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
                print_tree(nul, tree);
                (*func[command - 1])(nul, tree);
                scanf("%*c%*[^\n]");
                printf("\033[H\033[J");
                send_command_menu();
                print_tree(nul, tree);
                break;
            case 3 ... 5:
                (*func[command - 1])(nul, tree);
                break;
            case 0:
                clear_tree(nul, tree->root);
                free(tree);
                return;
            default:
                break;
        }
    }
}