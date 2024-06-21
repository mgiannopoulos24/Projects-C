#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include "dial.h"
#include "graph.h" // Make sure to include graph.h or define Edge struct

#define MAX_WEIGHT 1000 // Maximum weight in the graph for bucket array size

typedef struct {
    int *vertices[MAX_WEIGHT + 1]; // Bucket array
    int num_vertices;
} Bucket;

void initialize_buckets(Bucket *buckets, int num_vertices) {
    buckets->num_vertices = num_vertices;
    for (int i = 0; i <= MAX_WEIGHT; ++i) {
        buckets->vertices[i] = NULL;
    }
}

void add_to_bucket(Bucket *buckets, int vertex, int distance) {
    if (distance > MAX_WEIGHT) {
        distance = MAX_WEIGHT;
    }
    if (buckets->vertices[distance] == NULL) {
        buckets->vertices[distance] = (int *)malloc(buckets->num_vertices * sizeof(int));
        for (int i = 0; i < buckets->num_vertices; ++i) {
            buckets->vertices[distance][i] = -1;
        }
    }
    int index = 0;
    while (buckets->vertices[distance][index] != -1) {
        index++;
    }
    buckets->vertices[distance][index] = vertex;
}

void remove_from_bucket(Bucket *buckets, int vertex, int distance) {
    for (int i = 0; i < buckets->num_vertices; ++i) {
        if (buckets->vertices[distance][i] == vertex) {
            buckets->vertices[distance][i] = -1;
            return;
        }
    }
}

int get_next_vertex(Bucket *buckets) {
    for (int i = 0; i <= MAX_WEIGHT; ++i) {
        if (buckets->vertices[i] != NULL) {
            for (int j = 0; j < buckets->num_vertices; ++j) {
                if (buckets->vertices[i][j] != -1) {
                    int vertex = buckets->vertices[i][j];
                    buckets->vertices[i][j] = -1;
                    return vertex;
                }
            }
        }
    }
    return -1; // No more vertices to process
}

void dial(Graph *graph, int *distances, int start_vertex) {
    int num_vertices = graph->num_vertices;
    Bucket buckets;
    initialize_buckets(&buckets, num_vertices);

    // Initialize distances
    for (int i = 1; i <= num_vertices; ++i) {
        distances[i] = INT_MAX;
    }
    distances[start_vertex] = 0;

    // Add start vertex to bucket with distance 0
    add_to_bucket(&buckets, start_vertex, 0);

    // Process vertices until all are processed
    while (true) {
        int u = get_next_vertex(&buckets);
        if (u == -1) {
            break; // No more vertices to process
        }

        // Relax edges
        for (int v = 1; v <= num_vertices; ++v) {
            if (graph->edges[u][v].weight > 0) {
                int weight = graph->edges[u][v].weight;
                if (distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                    int old_distance = distances[v] - weight;
                    if (old_distance <= MAX_WEIGHT) {
                        remove_from_bucket(&buckets, v, old_distance);
                    }
                    add_to_bucket(&buckets, v, distances[v]);
                }
            }
        }
    }

    // Clean up allocated memory for buckets
    for (int i = 0; i <= MAX_WEIGHT; ++i) {
        if (buckets.vertices[i] != NULL) {
            free(buckets.vertices[i]);
        }
    }
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
    
    int start_vertex = 1;
    int distances[MAX_VERTICES];
    dial(&graph, distances, start_vertex);

    printf("Shortest distances from vertex %d:\n", start_vertex);
    for (int i = 1; i <= graph.num_vertices; ++i) {
        printf("Vertex %d: %d\n", i, distances[i]);
    }

    return 0;
}
