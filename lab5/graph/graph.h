#ifndef SEM1_LAB4_GRAPH_H
#define SEM1_LAB4_GRAPH_H

#define ull unsigned long long
#define BLOCK_SIZE 4

typedef struct Edge {
    ull *ports;
    ull current_size;
    ull ports_size;
    ull delay;
} Edge;

typedef struct Node {
    Edge *data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

typedef struct Vertex {
    char *name;
    ull port;
    List *edges;
} Vertex;

typedef struct Graph {
    Vertex **vertexes;
    ull current_size;
    ull vertex_size;
} Graph;

Graph * create_graph();
Vertex * create_vertex(char *name, ull port);
void add_vertex(Graph *graph, Vertex *vertex);
Vertex * remove_vertex(Graph *graph, char* name);

Edge * create_edge(ull delay);
void add_port(Graph *graph, Edge *edge, ull port);
void remove_port(Graph *graph, Edge *edge, ull port);


List * create_list();

Node * create_node(Edge *data);
void add_node(List *list, Node *node);
Node * find_node(List *list, Edge *edge);
void remove_node(List *list, Node *node);


#endif //SEM1_LAB4_GRAPH_H
