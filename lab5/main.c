#include "methods.h"
#include "graph/graph.h"
#include "stdlib.h"
#include "algorthm/search.h"
#include "methods.h"
#include "menu/classic_menu.h"

#ifdef _WIN32
#include "windows.h"
#define select_settings() SetConsoleOutputCP(CP_UTF8)
#else
#define select_settings()
#endif

#define PRESET 1
#if PRESET == -1
#define preset(graph) FILE *file = fopen("try.txt", "r"); file_input(graph, file); fclose(file);
#elif PRESET == 1
#define preset(graph) fill(graph);
#else
#define preset(graph)
#endif


void fill(Graph *graph) {
    char *x = malloc(2);
    x[0] = 'A';
    x[1] = '\0';
    Vertex *vertex_1 = create_vertex(x, 10);

    x = malloc(2);
    x[0] = 'B';
    x[1] = '\0';
    Vertex *vertex_2 = create_vertex(x, 10);

    x = malloc(2);
    x[0] = 'C';
    x[1] = '\0';
    Vertex *vertex_3 = create_vertex(x, 10);

    x = malloc(2);
    x[0] = 'D';
    x[1] = '\0';
    Vertex *vertex_4 = create_vertex(x, 10);

    x = malloc(2);
    x[0] = 'E';
    x[1] = '\0';
    Vertex *vertex_5 = create_vertex(x, 10);
    x = malloc(2);
    x[0] = 'F';
    x[1] = '\0';
    Vertex *vertex_6 = create_vertex(x, 10);
    x = malloc(2);
    x[0] = 'G';
    x[1] = '\0';
    Vertex *vertex_7 = create_vertex(x, 10);

    add_vertex(graph, vertex_1);
    add_vertex(graph, vertex_1);
    add_vertex(graph, vertex_2);
    add_vertex(graph, vertex_3);
    add_vertex(graph, vertex_4);
    add_vertex(graph, vertex_5);
    add_vertex(graph, vertex_6);
    add_vertex(graph, vertex_7);

    Edge *edge = create_edge(7);
    add_port(edge, 10);
    add_edge(vertex_1, vertex_2, edge);

    edge = create_edge(8);
    add_port(edge, 10);
    add_edge(vertex_2, vertex_3, edge);

    edge = create_edge(5);
    add_port(edge, 2);
    add_edge(vertex_1, vertex_4, edge);

    edge = create_edge(9);
    add_port(edge, 10);
    add_edge(vertex_4, vertex_2, edge);

    edge = create_edge(7);
    add_port(edge, 10);
    add_edge(vertex_2, vertex_5, edge);

    edge = create_edge(5);
    add_port(edge, 2);
    add_edge(vertex_3, vertex_5, edge);

    edge = create_edge(15);
    add_port(edge, 2);
    add_edge(vertex_4, vertex_5, edge);

    edge = create_edge(6);
    add_port(edge, 2);
    add_edge(vertex_4, vertex_6, edge);

    edge = create_edge(8);
    add_port(edge, 2);
    add_edge(vertex_5, vertex_6, edge);

    edge = create_edge(11);
    add_port(edge, 2);
    add_edge(vertex_6, vertex_7, edge);

    edge = create_edge(9);
    add_port(edge, 2);
    add_edge(vertex_5, vertex_7, edge);
}


int main(void) {
    select_settings();

    Graph *graph = create_graph();

    preset(graph)



//    methods_create_core(graph);
//    int *colors = dfs(graph, 0, 10);
//    for (int i = 0; i < graph->current_size; i++)
//        printf("%d: %s %d\n", i + 1, (graph->vertexes)[i]->name, colors[i]);
//    free(colors);
//    Graph *new_graph = create_core_tree(graph, 2);
    menu(graph, PRESET);

//    write_edges(graph);
//    system("main.exe");
//
//    print_graph(graph);
    return 1;
}