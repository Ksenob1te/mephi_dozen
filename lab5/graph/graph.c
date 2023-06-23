#include "graph.h"
#include "stdlib.h"
#include "string.h"


// -------------------------------------------------
// EDGE SECTION
// -------------------------------------------------
Edge *create_edge(ull delay) {
    Edge *edge = malloc(sizeof(Edge));
    edge->ports = malloc(sizeof(ull) * BLOCK_SIZE);
    edge->first = NULL;
    edge->second = NULL;
    edge->current_size = 0;
    edge->ports_size = 4;
    edge->delay = delay;
    return edge;
}

void add_port(Edge * edge, ull port) {
    if (!edge) return;
    if (edge->current_size == edge->ports_size) {
        edge->ports = realloc(edge->ports, edge->current_size + BLOCK_SIZE);
        edge->ports_size += BLOCK_SIZE;
    }

    for (ull i = 0; i < edge->current_size; i++) if ((edge->ports)[i] == port) return;
    (edge->ports)[(edge->current_size)++] = port;
}

void remove_port(Edge *edge, ull port) {
    if (!edge || edge->current_size == 0) return;

    ull index = 0;
    for (; (edge->ports)[index] != port && index < edge->current_size; index++);
    if (index == edge->current_size) return;

    (edge->ports)[index] = (edge->ports)[--(edge->current_size)];
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
// VERTEX SECTION
// -------------------------------------------------
Vertex * create_vertex(char *name, ull port) {
    Vertex *vertex = malloc(sizeof(Vertex));
    vertex->current_id = 0;
    vertex->port = port;
    vertex->name = name;
    vertex->edges = create_list();
    return vertex;
}

Vertex * find_vertex(char *name, Graph *graph) {
    for (int i = 0; i < graph->current_size; i++) {
        if (strcmp(name, (graph->vertexes)[i]->name) == 0)
            return (graph->vertexes)[i];
    }
    return NULL;
}

void add_edge(Vertex *conn_1, Vertex *conn_2, Edge *edge) {
    edge->first = conn_1;
    edge->second = conn_2;

    Node *first_node = create_node(edge);
    Node *second_node = create_node(edge);
    add_node(conn_1->edges, first_node);
    add_node(conn_2->edges, second_node);
}


void remove_edge(Edge *edge) {
    Vertex *first = edge->first;
    Node *first_node = find_node(first->edges, edge);
    remove_node(first->edges, first_node);
    free(first_node);

    Vertex *second = edge->second;
    Node *second_node = find_node(second->edges, edge);
    remove_node(second->edges, second_node);
    free(second_node);
    free(edge->ports);
    free(edge);
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

void clear_graph(Graph *graph) {
    for (int i = 0; i < graph->current_size; i++) {
        Vertex *vertex = (graph->vertexes)[i];
        Node *tmp1;
        for (Node *tmp = (vertex->edges)->head; tmp; tmp = tmp1) {
            tmp1 = tmp->next;
            remove_edge(tmp->data);
        }
        free(vertex->name);
        free(vertex->edges);
        free(vertex);
    }
    free(graph->vertexes);
}

int add_vertex(Graph *graph, Vertex *vertex) {
    if (!graph || !vertex) return 1;
    if (graph->current_size == graph->vertex_size) {
        graph->vertexes = realloc(graph->vertexes, graph->vertex_size + BLOCK_SIZE);
        graph->vertex_size += BLOCK_SIZE;
    }
    ull index = 0;
    for (; index < graph->current_size && strcmp((graph->vertexes)[index]->name, vertex->name) != 0; index++);
    if (index != graph->current_size) return 1;
    vertex->current_id = graph->current_size;
    (graph->vertexes)[graph->current_size] = vertex;
    (graph->current_size)++;
    return 0;
}

Vertex * remove_vertex(Graph *graph, char* name) {
    if (!graph) return NULL;

    ull index = 0;
    for (; index < graph->current_size && strcmp((graph->vertexes)[index]->name, name) != 0; index++);
    if (index == graph->current_size) return NULL;


    Vertex *result = (graph->vertexes)[index];
    Node *tmp;
    for (Node *i = result->edges->head; i; i = tmp) {
        tmp = i->next;
        remove_edge(i->data);
    }
    (graph->vertexes)[index] = (graph->vertexes)[--(graph->current_size)];
    (graph->vertexes)[index]->current_id = index;
    return result;
}
// -------------------------------------------------


void file_input(Graph *graph, FILE *file) {
    while (1) {
        char *name = malloc(256 * sizeof(char));
        ull port = -1, port2 = -1;
        ull delay = 0;
        int checker = fscanf(file, "%s", name);
        if (checker == EOF) {free(name); return;}
        fscanf(file, "%llu", &port);
        Vertex *vertex1 = create_vertex(name, port);
        int status = add_vertex(graph, vertex1);
        if (status) {
            free(vertex1->edges);
            free(vertex1);
            vertex1 = find_vertex(name, graph);
            free(name);
        }
        char *name2 = malloc(256 * sizeof(char));
        fscanf(file, "%s", name2);
        fscanf(file, "%llu", &port2);
        Vertex *vertex2 = create_vertex(name2, port2);
        status = add_vertex(graph, vertex2);
        if (status) {
            free(vertex2->edges);
            free(vertex2);
            vertex2 = find_vertex(name2, graph);
            free(name2);
        }
        fscanf(file, "%llu", &delay);

        Edge *edge = create_edge(delay);
        add_edge(vertex1, vertex2, edge);
        status = 1;
        while (status >= 1) {
            status = fscanf(file, "%llu", &port);
            add_port(edge, port);
        }
        fscanf(file, "*[^\n]");
        fscanf(file, "*\n");
    }

}
