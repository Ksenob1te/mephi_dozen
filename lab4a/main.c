#include "menu/classic_menu.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"


#define BLOCK_SIZE 100000
#ifdef _WIN32
#include "windows.h"
#define select_settings() SetConsoleOutputCP(CP_UTF8)
#else
#define select_settings()
#endif


char *create_text(char *text) {
    char *result = calloc((strlen(text) + 1), sizeof(char));
    strcat(result, text);
    result[strlen(text)] = '\0';
    return result;
}
int main(void) {
    select_settings();
    Tree *tree = create_tree();


    Node *node;
    clock_t start = clock(), end;
    srand(time(NULL));
    int counter = 0;
    for (int i = 0; i < 1000000000; i++) {
        if (i % 100000 == 0) {
            start = clock();
            counter = 0;
        }
        counter++;
        node = create_node(rand() % 100000000, create_text("sample"));
        add_node(tree, node);
        if (counter == BLOCK_SIZE) {
            end = clock();
            printf("%d: %lf\n", i, ((double)(end - start)) / CLOCKS_PER_SEC / BLOCK_SIZE);
        }
    }
//    char x[10000] = "";
//    print_root(x, tree->root, 1);
    scanf("\n");
//    Node *node1 = create_node(30, create_text("123"));
//    add_node(tree, node1);
//    Node *node = create_node(27, create_text("432"));
//    add_node(tree, node);
//    node = create_node(13, create_text("123"));
//    add_node(tree, node);
//    node = create_node(8, create_text("123"));
//    add_node(tree, node);
//    node = create_node(3, create_text("123"));
//    add_node(tree, node);
//    node = create_node(18, create_text("123"));
//    add_node(tree, node);
//    node = create_node(13, create_text("123"));
//    add_node(tree, node);

//    remove_node(tree, node1);
//    node = search_node(tree, 15);
//    tree_traversal(tree, 8);
//    char x[1000] = "";
//    print_root(x, tree->root, 1);
//    menu(tree);


    return 0;
}
