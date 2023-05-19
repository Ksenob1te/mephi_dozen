#ifndef SEM1_LAB4_SEARCH_H
#define SEM1_LAB4_SEARCH_H
#include "../graph/graph.h"

void DFS_step(Vertex *v, int id, ull time, ull limit, int *color) {
    color[id] = 1;
    if (time <= limit) {

    }
    color[id] = 2;
}

void DFS(Graph *graph, int *color, ull limit) {
    for (int i = 0; i < graph->current_size; i++)
        color[i] = 0;


}

#endif //SEM1_LAB4_SEARCH_H
