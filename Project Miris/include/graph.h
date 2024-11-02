#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct Edge {
    struct Node* target;
    int amount;
    char date[11]; // "YYYY-MM-DD"
    struct Edge* next;
} Edge;

typedef struct Node {
    char* id;
    Edge* edges;
    struct Node* next;
} Node;

typedef struct Graph {
    Node** nodes;
    int size;
} Graph;

// Graph function prototypes
Graph* create_graph(int size);
Node* create_node(const char* id);
Edge* create_edge(Node* target, int amount, const char* date);
void insert_node(Graph* graph, const char* id);
void insert_edge(Graph* graph, const char* from_id, const char* to_id, int amount, const char* date);
void delete_node(Graph* graph, const char* id);
void delete_edge(Graph* graph, const char* from_id, const char* to_id);
Node* find_node(Graph* graph, const char* id);
void display_graph(Graph* graph);
void free_graph(Graph* graph);

// Command-related prototypes
void modify_edge(Graph* graph, const char* from_id, const char* to_id, int old_sum, int new_sum, const char* old_date, const char* new_date);
void find_outgoing_transactions(Graph* graph, const char* id);
void find_incoming_transactions(Graph* graph, const char* id);
bool detect_cycle(Graph* graph, const char* id);
bool detect_cycles_with_min_sum(Graph* graph, const char* id, int k);
bool trace_flow(Graph* graph, const char* id, int m);
bool is_connected(Graph* graph, const char* from_id, const char* to_id);

// Helper function prototypes
bool dfs_cycle(Graph* graph, Node* node, bool* visited, bool* rec_stack);
bool dfs_cycle_min_sum(Graph* graph, Node* node, bool* visited, bool* rec_stack, int min_sum);
void dfs_trace_flow(Graph* graph, Node* node, int depth, int max_depth);
bool dfs_is_connected(Graph* graph, Node* node, const char* target_id, bool* visited);

// Graph visualization and DOT file generation
void write_dot_file(Graph* graph, const char* output_dot_file);

#endif
