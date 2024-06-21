#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include "boruvka.h"
#include "union_find.h"
#include "graph.h" // Make sure to include graph.h or define Edge struct

void boruvka(Graph *graph, int *parent) {
    int num_vertices = graph->num_vertices;

    UnionFind uf;
    uf_init(&uf, num_vertices);

    int num_components = num_vertices;

    while (num_components > 1) {
        // Initialize cheapest array for each component
        Edge cheapest[MAX_VERTICES];
        for (int i = 1; i <= num_vertices; ++i) {
            cheapest[i].weight = INT_MAX;
        }

        // Find cheapest edge for each component
        for (int v = 1; v <= num_vertices; ++v) {
            int root = uf_find(&uf, v);
            for (int u = 1; u <= num_vertices; ++u) {
                if (root != uf_find(&uf, u)) {
                    int weight = get_weight(graph, u, v);
                    if (weight > 0 && weight < cheapest[root].weight) {
                        cheapest[root].start_vertex = u;
                        cheapest[root].end_vertex = v;
                        cheapest[root].weight = weight;
                    }
                }
            }
        }

        // Add cheapest edges to MST
        for (int v = 1; v <= num_vertices; ++v) {
            int root = uf_find(&uf, v);
            if (cheapest[root].weight != INT_MAX) {
                int start = cheapest[root].start_vertex;
                int end = cheapest[root].end_vertex;
                if (uf_find(&uf, start) != uf_find(&uf, end)) {
                    parent[end] = start; // Update parent for tracking MST
                    uf_union(&uf, uf_find(&uf, start), uf_find(&uf, end));
                    num_components--;
                }
            }
        }
    }

    uf_destroy(&uf);
}


int main() {
    Graph graph;
    init_graph(&graph);

    // Example graph initialization
    add_edge(&graph, 1, 2, 1);
    add_edge(&graph, 1, 3, 4);
    add_edge(&graph, 2, 3, 2);
    add_edge(&graph, 2, 4, 5);
    add_edge(&graph, 3, 4, 1);
    add_edge(&graph, 3, 5, 3);
    add_edge(&graph, 4, 5, 7);

    // Print the graph
    printf("Graph:\n");
    print_graph(&graph);
    int parent[MAX_VERTICES] = { 0 };
    boruvka(&graph, parent);

    printf("Minimum Spanning Tree (MST):\n");
    for (int v = 2; v <= graph.num_vertices; ++v) {
        printf("Edge %d - %d: %d\n", parent[v], v, get_weight(&graph, v, parent[v]));
    }

    return 0;
}
