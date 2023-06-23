#ifndef SEM1_LAB4_GRAPH_H
#define SEM1_LAB4_GRAPH_H

#define ull unsigned long long
#define BLOCK_SIZE 100

typedef struct Edge {
    ull *ports;
    struct Vertex *first;
    struct Vertex *second;
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
    ull current_id;
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
int add_vertex(Graph *graph, Vertex *vertex);
Vertex * remove_vertex(Graph *graph, char* name);
Vertex * find_vertex(char *name, Graph *graph);


Edge * create_edge(ull delay);
void add_edge(Vertex *conn_1, Vertex *conn_2, Edge *edge);
void remove_edge(Edge *edge);

void add_port(Edge *edge, ull port);
void remove_port(Edge *edge, ull port);


List * create_list();

Node * create_node(Edge *data);
void add_node(List *list, Node *node);
Node * find_node(List *list, Edge *edge);
void remove_node(List *list, Node *node);
void clear_graph(Graph *graph);


#endif //SEM1_LAB4_GRAPH_H
