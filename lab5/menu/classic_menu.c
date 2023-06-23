#include "stdio.h"
#include "../methods.h"
#include "stdlib.h"

void send_command_menu() {
    printf("\033[0;33m____________________________________\n");
    printf("__________Here's your menu__________\n");
    printf("____Select one option from below____\n");
    printf("[1] Add Vertex\n");
    printf("[2] Delete Vertex\n");
    printf("[3] Add Edge\n");
    printf("[4] Delete Edge\n");
    printf("[5] Change Vertex\n");
    printf("[6] Change Edge\n");
    printf("[7] DFS\n");
    printf("[8] Bellman Ford\n");
    printf("[9] Tree Core\n");
    printf("[10] Draw Graph\n");
    printf("[0] Exit\n");
    printf("____________________________________\033[0m\n");
}

void menu(Graph *graph) {
    void (*func[10])(Graph *) = {methods_add_vertex, methods_remove_vertex, methods_add_edge, methods_remove_edge,
                                print_graph, methods_add_port, search_dfs, search_bellman, methods_create_core, draw_graph};
    printf("\033[H\033[J");
    send_command_menu();

//    const char *file_name = "keyspaces";
//    FILE *file = fopen(file_name, "wb");
//    fclose(file);

//    print_graph(graph);
    while (1) {
        printf("\033[1;90mType command (number [0-5]):\033[0;0m\n");
        int command = 0;
        int x = scanf("%d", &command);
        if (x == EOF) {
            scanf("%*[^\n]*c");
//            print_graph(graph);
            clear_graph(graph);
            free(graph);
            return;
        }
        if (x == 0) {
            printf("Incorrect input, try again\n");
            scanf("%*[^\n]*c");
            continue;
        }
        switch (command) {
            case 1 ... 10:
                printf("\033[H\033[J");
//                print_graph(graph);
                (*func[command - 1])(graph);
                scanf("%*c%*[^\n]");
                printf("\033[H\033[J");
                send_command_menu();
//                print_graph(graph);
                break;
//            case 3 ... 5:
//                (*func[command - 1])(graph);
//                break;
            case 0:
                clear_graph(graph);
                free(graph);
                return;
            default:
                break;
        }
    }
}