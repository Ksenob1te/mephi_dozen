#ifndef SEM1_LAB4_METHODS_H
#define SEM1_LAB4_METHODS_H

#include "stdio.h"
#include "graph/graph.h"

void print_graph(Graph *graph);
void search_dfs(Graph *graph);
void search_bellman(Graph *graph);
void write_edges(Graph *graph);
void methods_create_core(Graph *graph);

#endif //SEM1_LAB4_METHODS_H
