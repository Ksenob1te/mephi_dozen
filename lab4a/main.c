#include "menu/classic_menu.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"


#define BLOCK_SIZE 1000
#define LIMIT 100000000
#define RAND() (rand() & 0x7fff)
typedef ull u64;

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

void counter(Tree *tree) {
    Node *node;
    clock_t start, end, current = 0;
    FILE *file = fopen("file2.txt", "w");
    srand(time(NULL));
    int counter = BLOCK_SIZE + 1;
    ull *list = malloc((LIMIT + 1) * sizeof(ull));
    ull list_size = 0;
    for (long i = 0; i < LIMIT; i++) {
        ull tag = ((u64) RAND() << 48) ^ ((u64) RAND() << 35) ^ ((u64) RAND() << 22) ^
                  ((u64) RAND() << 9) ^ ((u64) RAND() >> 4);
        node = create_node(tag, create_text("sample"));
        add_node(tree, node);
        list[list_size] = tag;
        list_size++;

        if ((i % (BLOCK_SIZE * 100) == 0 && i != 0) || counter <= BLOCK_SIZE) {
            if (i % (BLOCK_SIZE * 100) == 0) {printf("%ld/%d\n", i / (BLOCK_SIZE * 100), (LIMIT / (BLOCK_SIZE * 100))); counter = 0; current = 0;}
            ull r;
            do {
                tag = ((u64) RAND() << 48) ^ ((u64) RAND() << 35) ^ ((u64) RAND() << 22) ^
                      ((u64) RAND() << 9) ^ ((u64) RAND() >> 4);
                r = list[tag % list_size];
            } while (r == 0);
            node = search_node(tree, r);
            start = clock();
            remove_node(tree, node);
            end = clock();
            list[tag % list_size] = 0;
            current += end - start;
            if (counter == BLOCK_SIZE)
                fprintf(file, "%ld\n", current);
            counter++;
        }

    }
    fclose(file);
}

int main(void) {
    select_settings();
    Tree *tree = create_tree();

//    counter(tree);

    Node *node1 = create_node(11, create_text("123"));
    add_node(tree, node1);
    Node *node = create_node(1, create_text("432"));
    add_node(tree, node);
    node = create_node(0, create_text("123"));
    add_node(tree, node);
    node = create_node(7, create_text("123"));
    add_node(tree, node);
    node = create_node(5, create_text("123"));
    add_node(tree, node);
    node = create_node(3, create_text("123"));
    add_node(tree, node);
    node = create_node(4, create_text("123"));
    add_node(tree, node);
    node = create_node(8, create_text("123"));
    add_node(tree, node);
    node = create_node(9, create_text("123"));
    add_node(tree, node);
    node = create_node(14, create_text("123"));
    add_node(tree, node);
    node = create_node(13, create_text("123"));
    add_node(tree, node);
    node = create_node(12, create_text("123"));
    add_node(tree, node);
    node = create_node(16, create_text("123"));
    add_node(tree, node);
    node = create_node(15, create_text("123"));
    add_node(tree, node);
    node = create_node(19, create_text("123"));
    add_node(tree, node);
    node = create_node(17, create_text("123"));
    add_node(tree, node);
//
//    char x[1000] = "";
//    print_root(x, tree->root, 1);
//    node = search_node(tree, 1);
//    remove_node(tree, node);
//    char x1[1000] = "";
//    print_root(x1, tree->root, 1);
//    scanf("\n");
    menu(tree);

    return 0;
}
