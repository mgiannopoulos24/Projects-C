#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // for qsort
#include "kruskal.h"
#include "union_find.h"
#include "graph.h" 

// Compare function for qsort
int compare_edges(const void *a, const void *b) {
    Edge *edge1 = (Edge *)a;
    Edge *edge2 = (Edge *)b;
    return edge1->weight - edge2->weight;
}

void kruskal(Graph *graph, int *parent) {
    int num_vertices = graph->num_vertices;
    int num_edges = 0;
    Edge edges[MAX_VERTICES * MAX_VERTICES / 2]; // Maximum possible edges in a complete graph

    // Collect all edges from the graph
    for (int i = 1; i <= num_vertices; ++i) {
        for (int j = i + 1; j <= num_vertices; ++j) {
            if (graph->edges[i][j].weight > 0) {
                edges[num_edges].start_vertex = i;
                edges[num_edges].end_vertex = j;
                edges[num_edges].weight = graph->edges[i][j].weight;
                num_edges++;
            }
        }
    }

    // Sort edges by weight
    qsort(edges, num_edges, sizeof(Edge), compare_edges);

    UnionFind uf;
    uf_init(&uf, num_vertices);

    int edge_count = 0;
    for (int i = 0; i < num_edges && edge_count < num_vertices - 1; ++i) {
        int start = edges[i].start_vertex;
        int end = edges[i].end_vertex;

        int root_start = uf_find(&uf, start);
        int root_end = uf_find(&uf, end);

        if (root_start != root_end) {
            parent[end] = start; // Update parent for tracking MST
            uf_union(&uf, root_start, root_end);
            ++edge_count;
        }
    }

    uf_destroy(&uf);
}

int main() {
    Graph graph;
    int parent[MAX_VERTICES];

    // Initialize the graph (you can use your own initialization method here)
    init_graph(&graph);

    // Example graph initialization
    add_edge(&graph, 1, 2, 4);
    add_edge(&graph, 1, 3, 2);
    add_edge(&graph, 2, 3, 5);
    add_edge(&graph, 2, 4, 10);
    add_edge(&graph, 3, 4, 3);
    add_edge(&graph, 4, 5, 7);


    // Print the graph
    printf("Graph:\n");
    print_graph(&graph);
    
    // Apply Kruskal's algorithm
    kruskal(&graph, parent);

    // Print the Minimum Spanning Tree (MST)
    printf("Minimum Spanning Tree (MST):\n");
    for (int i = 2; i <= graph.num_vertices; ++i) {
        printf("Edge %d - %d: %d\n", parent[i], i, get_weight(&graph, i, parent[i]));
    }

    return 0;
}
