#ifndef SEM1_LAB4_SEARCH_H
#define SEM1_LAB4_SEARCH_H
#include "../graph/graph.h"

int * dfs(Graph *graph, ull starter, ull port);
ull *bellman_ford(Graph *graph, ull starter, ull port, Vertex **parent);
Graph *create_core_tree(Graph *graph, ull selected_port);

#endif //SEM1_LAB4_SEARCH_H
