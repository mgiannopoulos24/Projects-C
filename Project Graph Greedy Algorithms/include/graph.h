#ifndef GRAPH_H
#define GRAPH_H

#define MAX_VERTICES 100

typedef struct {
    int start_vertex;
    int end_vertex;
    int weight;
} Edge;

typedef struct {
    Edge edges[MAX_VERTICES][MAX_VERTICES];
    int num_vertices;
} Graph;

void init_graph(Graph *graph);
void add_edge(Graph *graph, int start, int end, int weight);
int get_weight(Graph *graph, int start, int end);
void print_graph(Graph *graph);

#endif