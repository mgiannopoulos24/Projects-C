#include <stdio.h>
#include "graph.h"

void init_graph(Graph *graph) {
    graph->num_vertices = 0;
}

void add_edge(Graph *graph, int start, int end, int weight) {
    graph->edges[start][end].weight = weight;
    graph->edges[start][end].end_vertex = end;
    // Assuming undirected graph for simplicity
    graph->edges[end][start].weight = weight;
    graph->edges[end][start].end_vertex = start;

    if (start > graph->num_vertices) {
        graph->num_vertices = start;
    }
    if (end > graph->num_vertices) {
        graph->num_vertices = end;
    }
}

int get_weight(Graph *graph, int start, int end) {
    return graph->edges[start][end].weight;
}

void print_graph(Graph *graph) {
    printf("Graph with %d vertices:\n", graph->num_vertices);
    for (int i = 1; i <= graph->num_vertices; ++i) {
        printf("Vertex %d -> ", i);
        for (int j = 1; j <= graph->num_vertices; ++j) {
            if (graph->edges[i][j].weight > 0) {
                printf("(%d, %d) ", j, graph->edges[i][j].weight);
            }
        }
        printf("\n");
    }
}
