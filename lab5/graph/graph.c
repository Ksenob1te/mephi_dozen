#include "graph.h"
#include "stdlib.h"
#include "string.h"


// -------------------------------------------------
// EDGE SECTION
// -------------------------------------------------
Edge *create_edge(ull delay) {
    Edge *edge = malloc(sizeof(Edge));
    edge->ports = malloc(sizeof(ull) * BLOCK_SIZE);
    edge->current_size = 0;
    edge->ports_size = 4;
    edge->delay = delay;
    return edge;
}

void add_port(Graph *graph, Edge * edge, ull port) {
    if (!edge) return;
    if (edge->current_size == edge->ports_size) {
        edge->ports = realloc(edge->ports, edge->current_size + BLOCK_SIZE);
        edge->ports_size += BLOCK_SIZE;
    }

    for (ull i = 0; i < edge->current_size; i++) if ((edge->ports)[i] == port) return;
    (edge->ports)[(edge->current_size)++] = port;

    if (graph->current_size == 0) return;
    for (ull i = 0; i < graph->current_size; i++) {
        Vertex *vertex = (graph->vertexes)[i];
        if (vertex->port == port) {
            Node *temp = create_node(edge);
            add_node(vertex->edges, temp);
        }
    }
}

void remove_port(Graph *graph, Edge *edge, ull port) {
    if (!edge || edge->current_size == 0) return;

    ull index = 0;
    for (; (edge->ports)[index] != port && index < edge->current_size; index++);
    if (index == edge->current_size) return;

    (edge->ports)[index] = (edge->ports)[--(edge->current_size)];

    if (graph->current_size == 0) return;
    for (ull i = 0; i < graph->current_size; i++) {
        Vertex *vertex = (graph->vertexes)[i];
        if (vertex->port == port) {
            Node *temp = find_node(vertex->edges, edge);
            remove_node(vertex->edges, temp);
            // clear temp here
        }
    }
}
// -------------------------------------------------



// -------------------------------------------------
// LIST SECTION
// -------------------------------------------------
List * create_list() {
    List *list = malloc(sizeof (List));
    list->head = NULL;
    return list;
}

Node * create_node(Edge *data) {
    Node *node = malloc(sizeof (Node));
    node->next = NULL;
    node->data = data;
    return node;
}

void add_node(List *list, Node *node) {
    if (!node || !list) return;
    node->next = list->head;
    list->head = node;
}

Node *find_node(List *list, Edge *edge) {
    Node *current = list->head;
    for (; current && current->data != edge; current = current->next);
    return current;
}

void remove_node(List *list, Node *node) {
    if (!node || !list) return;
    if (node == list->head) {
        list->head = node->next;
        return;
    }
    Node *prev = list->head;
    for (; prev->next && prev->next != node; prev = prev->next);
    if (prev->next == node)
        prev->next = node->next;
}
// -------------------------------------------------



// -------------------------------------------------
// GRAPH SECTION
// -------------------------------------------------
Graph * create_graph() {
    Graph *graph = malloc(sizeof(Graph));
    graph->vertexes = malloc(sizeof(Vertex *) * BLOCK_SIZE);
    graph->current_size = 0;
    graph->vertex_size = BLOCK_SIZE;
    return graph;
}

Vertex * create_vertex(char *name, ull port) {
    Vertex *vertex = malloc(sizeof(Vertex));
    vertex->port = port;
    vertex->name = name;
    vertex->edges = create_list();
    return vertex;
}

static int check_edge(Edge *edge, ull port) {
    ull index = 0;
    for (; (edge->ports)[index] != port && index < edge->current_size; index++);
    if (index == edge->current_size) return 0;
    return 1;
}

void add_vertex(Graph *graph, Vertex *vertex) {
    if (!graph || !vertex) return;
    if (graph->current_size == graph->vertex_size) {
        graph->vertexes = realloc(graph->vertexes, graph->vertex_size + BLOCK_SIZE);
        graph->vertex_size += BLOCK_SIZE;
    }

    // ТУТ ПЕРЕДЕЛАТЬ
    for (ull i = 0; i < graph->current_size; i++) {
        Vertex *tmp = (graph->vertexes)[i];
        for (Node *node = tmp->edges->head; node; node = node->next)
            if (check_edge(node->data, vertex->port))
                add_node(vertex->edges, create_node(node->data));
    }

    (graph->vertexes)[(graph->current_size)++] = vertex;

}

Vertex * remove_vertex(Graph *graph, char* name) {
    if (!graph) return NULL;

    ull index = 0;
    for (; strcmp((graph->vertexes)[index]->name, name) != 0 && index < graph->current_size; index++);
    if (index == graph->current_size) return NULL;

    Vertex *result = (graph->vertexes)[index];
    (graph->vertexes)[index] = (graph->vertexes)[--(graph->current_size)];
    return result;
}
// -------------------------------------------------
