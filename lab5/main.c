#include "methods.h"
#include "graph/graph.h"

int main(void) {
    Graph *graph = create_graph();

    Vertex *v = create_vertex("comp1", 1);
    add_vertex(graph, v);
    Edge *edge = create_edge(10);
    add_port(graph, edge, 1);
    add_port(graph, edge, 2);
    v = create_vertex("comp2", 2);
    add_vertex(graph, v);
    print_graph(graph);

    return 1;
}