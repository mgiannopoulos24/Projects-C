#include <stdio.h>
#include <stdbool.h>
#include "prim.h"

void prim(Graph *graph, int start_vertex, int *parent) {
    int num_vertices = graph->num_vertices;
    bool visited[MAX_VERTICES] = { false };
    int min_cost[MAX_VERTICES];
    
    // Initialize min_cost array
    for (int i = 1; i <= num_vertices; ++i) {
        min_cost[i] = MAX_DISTANCE;
    }

    min_cost[start_vertex] = 0;
    parent[start_vertex] = -1;  // Start vertex has no parent

    for (int count = 1; count <= num_vertices; ++count) {
        int min_vertex = -1;
        int min_cost_value = MAX_DISTANCE;

        // Find the vertex with the minimum cost
        for (int v = 1; v <= num_vertices; ++v) {
            if (!visited[v] && min_cost[v] < min_cost_value) {
                min_cost_value = min_cost[v];
                min_vertex = v;
            }
        }

        if (min_vertex == -1) {
            break;  // No more vertices to process
        }

        visited[min_vertex] = true;

        // Update the cost of adjacent vertices
        for (int v = 1; v <= num_vertices; ++v) {
            int weight = get_weight(graph, min_vertex, v);
            if (!visited[v] && weight > 0 && weight < min_cost[v]) {
                parent[v] = min_vertex;
                min_cost[v] = weight;
            }
        }
    }
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

    // Starting vertex for Prim's algorithm
    int start_vertex = 1;

   
    // Print the graph
    printf("Graph:\n");
    print_graph(&graph);
    
    // Apply Prim's algorithm
    prim(&graph, start_vertex, parent);

    // Print the Minimum Spanning Tree (MST)
    printf("Minimum Spanning Tree (MST) from vertex %d:\n", start_vertex);
    for (int i = 2; i <= graph.num_vertices; ++i) {
        printf("Edge %d - %d: %d\n", parent[i], i, get_weight(&graph, i, parent[i]));
    }

    return 0;
}
