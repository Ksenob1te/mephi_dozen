#include "methods.h"

static void print_vertex(Vertex *vertex) {
    printf("%s: %llu -> ", vertex->name, vertex->port);
    for (Node *node = vertex->edges->head; node; node = node->next) {
        Edge *edge = node->data;
        printf("(%llums: ", edge->delay);
        for (ull i = 0; i < edge->current_size; i++)
            printf("%llu ", (edge->ports)[i]);
        printf(") ");
    }
    printf("\n");
}

void print_graph(Graph *graph) {
    for (ull i = 0; i < graph->current_size; i++) {
        print_vertex((graph->vertexes)[i]);
    }
}
