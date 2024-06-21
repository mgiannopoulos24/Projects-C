#include <stdio.h>
#include <stdbool.h>
#include "dijkstra.h"

void dijkstra(Graph *graph, int start_vertex, int *distances) {
    bool visited[MAX_VERTICES] = { false };

    // Initialize distances
    for (int i = 1; i <= graph->num_vertices; ++i) {
        distances[i] = MAX_DISTANCE;
    }
    distances[start_vertex] = 0;

    // Dijkstra's algorithm
    for (int count = 1; count <= graph->num_vertices; ++count) {
        int min_distance = MAX_DISTANCE;
        int current_vertex = -1;

        // Find the vertex with the minimum distance
        for (int i = 1; i <= graph->num_vertices; ++i) {
            if (!visited[i] && distances[i] < min_distance) {
                min_distance = distances[i];
                current_vertex = i;
            }
        }

        if (current_vertex == -1) {
            break; // No more vertices to process
        }

        visited[current_vertex] = true;

        // Update distances of adjacent vertices
        for (int i = 1; i <= graph->num_vertices; ++i) {
            int weight = get_weight(graph, current_vertex, i);
            if (weight > 0 && distances[current_vertex] + weight < distances[i]) {
                distances[i] = distances[current_vertex] + weight;
            }
        }
    }
}

int main() {
    // Example graph initialization
    Graph graph;
    init_graph(&graph);
    
    // Add edges to the graph (example)
    add_edge(&graph, 1, 2, 4);
    add_edge(&graph, 1, 3, 2);
    add_edge(&graph, 2, 3, 5);
    add_edge(&graph, 2, 4, 10);
    add_edge(&graph, 3, 4, 3);
    add_edge(&graph, 4, 5, 7);

    int start_vertex = 1;
    int distances[MAX_VERTICES];

    // Print the graph
    printf("Graph:\n");
    print_graph(&graph);

    // Compute shortest distances using Dijkstra's algorithm
    dijkstra(&graph, start_vertex, distances);

    // Print shortest distances from the start_vertex
    printf("Shortest distances from vertex %d:\n", start_vertex);
    for (int i = 1; i <= graph.num_vertices; ++i) {
        printf("Vertex %d: %d\n", i, distances[i]);
    }

    return 0;
}
