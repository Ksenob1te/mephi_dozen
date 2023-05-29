#include "methods.h"
#include "graph/graph.h"
#include "stdlib.h"
#include "algorthm/search.h"
#include "methods.h"



int main(void) {
    Graph *graph = create_graph();

    Vertex *vertex_1 = create_vertex("A", 10);
    Vertex *vertex_2 = create_vertex("B", 10);
    Vertex *vertex_3 = create_vertex("C", 2);
    Vertex *vertex_4 = create_vertex("D", 2);
    Vertex *vertex_5 = create_vertex("E", 2);
    Vertex *vertex_6 = create_vertex("F", 2);
    Vertex *vertex_7 = create_vertex("G", 2);
//    Vertex *vertex_8 = create_vertex("c8", 2);

    add_vertex(graph, vertex_1);
    add_vertex(graph, vertex_1);
    add_vertex(graph, vertex_2);
    add_vertex(graph, vertex_3);
    add_vertex(graph, vertex_4);
    add_vertex(graph, vertex_5);
    add_vertex(graph, vertex_6);
    add_vertex(graph, vertex_7);
//    add_vertex(graph, vertex_8);

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


//    methods_create_core(graph);
//    int *colors = dfs(graph, 0, 10);
//    for (int i = 0; i < graph->current_size; i++)
//        printf("%d: %s %d\n", i + 1, (graph->vertexes)[i]->name, colors[i]);
//    free(colors);
//    Graph *new_graph = create_core_tree(graph, 2);
    write_edges(graph);
    system("main.exe");

    print_graph(graph);
    return 1;
}