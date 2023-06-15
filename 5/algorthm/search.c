#include "search.h"
#include "stdlib.h"

void dfs_step(Graph *graph, ull current, ull port, int *colors) {
    colors[current] = 1;
    Vertex *vertex = (graph->vertexes)[current];
    for (Node *node = vertex->edges->head; node; node = node->next) {
        Edge *edge = node->data;
        Vertex *tmp;
        if (edge->first == vertex) tmp = edge->second;
        else tmp = edge->first;
        int checker = 0;
        for (int i = 0; i < edge->current_size; i++)
            if ((edge->ports)[i] == port) checker = 1;
        if (colors[tmp->current_id] == 0 && checker)
            dfs_step(graph, tmp->current_id, port, colors);
    }
}

int *dfs(Graph *graph, ull starter, ull port) {
    int *colors = calloc(sizeof(int), graph->current_size);
    dfs_step(graph, starter, port, colors);
    return colors;
}


ull * bellman_ford(Graph *graph, ull starter, ull port, Vertex **parent) {
    ull *dist = malloc(sizeof(ull) * graph->current_size);
    for (ull i = 0; i < graph->current_size; i++) {
        dist[i] = LLONG_MAX;
        parent[i] = NULL;
    }
    dist[starter] = 0;

    for (ull i = 0; i < graph->current_size - 1; i++) {
        for (ull k = 0; k < graph->current_size; k++) {
            Vertex *vertex = (graph->vertexes)[k];
            for (Node *node = vertex->edges->head; node; node = node->next) {
                Edge *edge = node->data;
                Vertex *tmp;
                int port_checker = 0;
                for (int m = 0; m < edge->current_size;  m++)
                    if ((edge->ports)[m] == port) port_checker = 1;
                if (edge->first == vertex) tmp = edge->second; else tmp = edge->first;
                if (dist[vertex->current_id] != LLONG_MAX &&
                    dist[vertex->current_id] + edge->delay < dist[tmp->current_id] &&
                    port_checker) {
                    dist[tmp->current_id] = dist[vertex->current_id] + edge->delay;
                    parent[tmp->current_id] = vertex;
                }
            }
        }
    }
    return dist;
}

int comparator(const void *p, const void *q) {
    ull l = (*((Edge **) p))->delay;
    ull r = (*((Edge **) q))->delay;
    if (l > r) return 1;
    else if (l < r) return -1;
    else return 0;
}

Graph *create_core_tree(Graph *graph, ull selected_port) {
    Graph *new_graph = create_graph();

    Edge **all_edges = malloc(graph->current_size * (graph->current_size - 1) * sizeof(Edge *));
    ull edges_size = 0;
    for (int i = 0; i < graph->current_size; i++) {
        Vertex *current = (graph->vertexes)[i];
        for (Node *node = current->edges->head; node; node = node->next) {
            Edge *tmp = node->data;
            int checker = 0;
            for (int k = 0; k < edges_size; k++)
                if (all_edges[k] == tmp) checker = 1;
            int port_checker = 0;
            for (int k = 0; k < tmp->current_size; k++)
                if ((tmp->ports)[k] == selected_port) port_checker = 1;
            if (!checker && port_checker) all_edges[edges_size++] = tmp;
        }
    }

    qsort(all_edges, edges_size, sizeof(Edge *), comparator);
    int added[graph->current_size];
    for (int i = 0; i < graph->current_size; i++) added[i] = 0;
    ull k = 0;
    int current_color = 1;
    for (int i = 0; i < graph->current_size && k < edges_size; i++) {
        Vertex *first_old = all_edges[k]->first, *second_old = all_edges[k]->second;
        if (!added[first_old->current_id] || !added[second_old->current_id] ||
                added[first_old->current_id] != added[second_old->current_id]) {
            Vertex *first = NULL, *second = NULL;
            if (!added[first_old->current_id] && !added[second_old->current_id])
                current_color++;
            if (added[first_old->current_id] != added[second_old->current_id] &&
                    added[first_old->current_id] && added[second_old->current_id]) {
                current_color++;
                int c1 = added[first_old->current_id], c2 = added[second_old->current_id];
                for (int m = 0; m < graph->current_size; m++) {
                    if (added[m] == c1 || added[m] == c2)
                        added[m] = current_color;
                }
            }
            if (!added[first_old->current_id]) {
                first = create_vertex(first_old->name, first_old->port);
                add_vertex(new_graph, first);
                if (added[second_old->current_id])
                    added[first_old->current_id] = added[second_old->current_id];
                else
                    added[first_old->current_id] = current_color;
            }
            if (!added[second_old->current_id]) {
                second = create_vertex(second_old->name, second_old->port);
                add_vertex(new_graph, second);
                if (added[first_old->current_id])
                    added[second_old->current_id] = added[first_old->current_id];
                else
                    added[second_old->current_id] = current_color;
            }

            for (int m = 0; m < new_graph->current_size; m++) {
                if (second_old->name == (new_graph->vertexes)[m]->name)
                    second = (new_graph->vertexes)[m];
                if (first_old->name == (new_graph->vertexes)[m]->name)
                    first = (new_graph->vertexes)[m];
            }

            Edge *edge = create_edge(all_edges[k]->delay);
            edge->ports = all_edges[k]->ports;
            edge->ports_size = all_edges[k]->ports_size;
            edge->current_size = all_edges[k]->current_size;
            add_edge(first, second, edge);
        } else {
            i--;
        }
        k++;
    }
        return new_graph;
}
