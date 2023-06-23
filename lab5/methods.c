#include "methods.h"
#include "algorthm/search.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "graph/graph.h"
#include "limits.h"

static void print_vertex(Vertex *vertex) {
    printf("%s(%llu) -> ", vertex->name, vertex->port);
    for (Node *node = vertex->edges->head; node; node = node->next) {
        Edge *edge = node->data;
        printf("[(%llums: ", edge->delay);
        for (ull i = 0; i < edge->current_size; i++)
            printf((i + 1) == edge->current_size ? "%llu" : "%llu ", (edge->ports)[i]);
        printf(") -> ");
        if (edge->first == vertex) printf("%s(%llu)]", edge->second->name, edge->second->port);
        else printf("%s(%llu)]", edge->first->name, edge->first->port);
        printf(node->next ? ", " : "");
    }
    printf("\n");
}

void print_graph(Graph *graph) {
    for (ull i = 0; i < graph->current_size; i++) {
        print_vertex((graph->vertexes)[i]);
    }
}

void write_edges(Graph *graph) {
    FILE *file = fopen("file.txt", "w");
    for (int i = 0; i < graph->current_size; i++) {
        Vertex *vertex = (graph->vertexes)[i];
        for (Node *j = vertex->edges->head; j; j = j->next) {
            fprintf(file, "%s %llu %s %llu ", j->data->first->name, j->data->first->port,
                    j->data->second->name, j->data->second->port);
            fprintf(file, "%llu ", j->data->delay);
            for (ull k = 0; k < j->data->current_size; k++)
                fprintf(file, ((k + 1) == j->data->current_size) ? "%llu":"%llu, ", (j->data->ports)[k]);
            fprintf(file, "\n");
        }
    }
    fclose(file);
}

static ull input_ull() {
    ull key;
    int status;
    input:
    status = scanf("%llu", &key);
    if (status == EOF || status < 0) return -1;
    if (status == 0) {
        fprintf(stderr, "\033[0;31mError in input, try again\033[0m\n");
        scanf("%*[^\n]");
        goto input;
    }
    return key;
}

static char *readline() {
    char *ptr = (char *) malloc(sizeof(char));
    char buf[81];
    int n, len = 0, bufLen;
    *ptr = '\0';
    do {
        n = scanf("%80[^\n]%n", buf, &bufLen);
        if (n < 0) {
            free(ptr);
            ptr = NULL;
            continue;
        }
        if (n == 0)
            scanf("%*c");
        else {
            len += bufLen;
            ptr = (char *) realloc(ptr, len + 1);
            strcat(ptr, buf);
        }
    } while (n > 0);
    return ptr;
}

void search_dfs(Graph *graph) {
    printf("Type in name of the starter PC(str): ");
    scanf("\n");
    char *name = readline();
    Vertex *vertex = find_vertex(name, graph);
    if (!vertex) {
        free(name);
        fprintf(stderr, "\033[0;31mNo PC has been found\033[0m\n");
        return;
    }
    printf("Type in port u wanna use (int): ");
    ull port = input_ull();
    int *colors = dfs(graph, vertex->current_id, port);
    printf("From PC \"%s\" you can get to:\n", name);
    for (int i = 0; i < graph->current_size; i++) {
        if (colors[i] && (graph->vertexes)[i]->port == port) print_vertex((graph->vertexes)[i]);
    }
    free(name);
    free(colors);
    printf("Done!");
}

void search_bellman(Graph *graph) {
    printf("Type in name of the starter PC(str): ");
    scanf("\n");
    char *name1 = readline();
    printf("Type in name of the end PC(str): ");
    scanf("\n");
    char *name2 = readline();
    printf("Type in port u wanna use (int): ");
    ull port = input_ull();
    Vertex *vertex1 = find_vertex(name1, graph);
    if (!vertex1) {
        free(name1);
        free(name2);
        fprintf(stderr, "\033[0;31mNo PC has been found\033[0m\n");
        return;
    }
    Vertex *vertex2 = find_vertex(name2, graph);
    if (!vertex2) {
        free(name1);
        free(name2);
        fprintf(stderr, "\033[0;31mNo PC has been found\033[0m\n");
        return;
    }
    free(name1);
    free(name2);
    Vertex **parent = malloc(sizeof(Vertex *) * graph->current_size);
    ull *dist = bellman_ford(graph, vertex1->current_id, port, parent);
    if (dist[vertex2->current_id] == LLONG_MAX) printf("No path has been found\n");
    else {
        printf("Length of the path: %llu\n", dist[vertex2->current_id]);
        print_vertex(vertex2);
        for (Vertex *tmp = parent[vertex2->current_id]; tmp; tmp = parent[tmp->current_id])
            print_vertex(tmp);
    }
    free(parent);
    free(dist);
    printf("Done!");
}

void methods_create_core(Graph *graph) {
    printf("Type in port u wanna use (int): ");
    ull port = input_ull();
    Graph *core = create_core_tree(graph, port);
    write_edges(core);
    system("main.exe");
    clear_graph(core);
    free(core);
    printf("Done!");
}

void methods_add_vertex(Graph *graph) {
    printf("Type in name of the PC(str): ");
    scanf("\n");
    char *name = readline();
    printf("Type in port (int): ");
    ull port = input_ull();
    Vertex *vertex = create_vertex(name, port);
    int status = add_vertex(graph, vertex);
    if (status) {
        fprintf(stderr, "\033[0;31mThis vertex already exists\033[0m\n");
        free(name);
        free(vertex);
    }
    printf("Done!");
}

void methods_add_edge(Graph *graph) {
    printf("Type in name of the starting PC(str): ");
    scanf("\n");
    char *name1 = readline();
    printf("Type in name of the end PC(str): ");
    scanf("\n");
    char *name2 = readline();
    printf("Type in delay for the edge (int): ");
    ull delay = input_ull();

    Vertex *vertex1 = find_vertex(name1, graph);
    Vertex *vertex2 = find_vertex(name2, graph);

    if (!vertex1 || !vertex2) {
        fprintf(stderr, "\033[0;31mNo vertex has been found\033[0m\n");
        return;
    }
    Edge *edge = create_edge(delay);
    add_edge(vertex1, vertex2, edge);
    printf("Done!");
}

void methods_remove_vertex(Graph *graph) {
    printf("Type in name of the PC(str): ");
    scanf("\n");
    char *name = readline();
    Vertex *vertex = remove_vertex(graph, name);
    if (!vertex) {
        fprintf(stderr, "\033[0;31mNo vertex has been found\033[0m\n");
        return;
    } else {
        free(vertex);
    }
    printf("Done!");
}

void methods_remove_edge(Graph *graph) {
    printf("Type in name of the starting PC(str): ");
    scanf("\n");
    char *name1 = readline();
    printf("Type in name of the end PC(str): ");
    scanf("\n");
    char *name2 = readline();

    Vertex *vertex1 = find_vertex(name1, graph);
    Vertex *vertex2 = find_vertex(name2, graph);

    if (!vertex1 || !vertex2) {
        fprintf(stderr, "\033[0;31mNo vertex has been found\033[0m\n");
        return;
    }

    Edge *edge = NULL;
    for (Node *i = vertex1->edges->head; i; i = i->next) {
        if (i->data->first == vertex2 || i->data->second == vertex2)
            edge = i->data;
    }
    if (!edge) {
        fprintf(stderr, "\033[0;31mNo edge has been found\033[0m\n");
        return;
    }
    remove_edge(edge);
    printf("Done!");
}

void methods_add_port(Graph *graph) {
    printf("Type in name of the starting PC(str): ");
    scanf("\n");
    char *name1 = readline();
    printf("Type in name of the end PC(str): ");
    scanf("\n");
    char *name2 = readline();

    Vertex *vertex1 = find_vertex(name1, graph);
    Vertex *vertex2 = find_vertex(name2, graph);

    if (!vertex1 || !vertex2) {
        fprintf(stderr, "\033[0;31mNo vertex has been found\033[0m\n");
        return;
    }

    Edge *edge = NULL;
    for (Node *i = vertex1->edges->head; i; i = i->next) {
        if (i->data->first == vertex2 || i->data->second == vertex2)
            edge = i->data;
    }
    if (!edge) {
        fprintf(stderr, "\033[0;31mNo edge has been found\033[0m\n");
        return;
    }
    printf("Type in port (int): ");
    ull port = input_ull();
    add_port(edge, port);
    printf("Done!");
}

void draw_graph(Graph *graph) {
    write_edges(graph);
    system("main.exe");
}
