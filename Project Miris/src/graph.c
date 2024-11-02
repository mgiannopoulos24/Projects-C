#include "graph.h"
#include <stdbool.h>

// Hash function for node IDs
int hash_function(const char* id, int size) {
    int hash = 0;
    for (int i = 0; id[i] != '\0'; i++) {
        hash = (hash + id[i]) % size;
    }
    return hash;
}

Graph* create_graph(int size) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->size = size;
    graph->nodes = (Node**)calloc(size, sizeof(Node*));
    return graph;
}

Node* create_node(const char* id) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->id = strdup(id);
    node->edges = NULL;
    node->next = NULL;
    return node;
}

Edge* create_edge(Node* target, int amount, const char* date) {
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->target = target;
    edge->amount = amount;
    strcpy(edge->date, date);
    edge->next = NULL;
    return edge;
}

void insert_node(Graph* graph, const char* id) {
    if (find_node(graph, id) != NULL) {
        printf("IssueWith: %s\n", id);
        return;
    }

    int hash = hash_function(id, graph->size);
    Node* node = create_node(id);
    node->next = graph->nodes[hash];
    graph->nodes[hash] = node;
    printf("Succ: %s\n", id);
}

void insert_edge(Graph* graph, const char* from_id, const char* to_id, int amount, const char* date) {
    Node* from_node = find_node(graph, from_id);
    Node* to_node = find_node(graph, to_id);

    if (from_node == NULL) {
        insert_node(graph, from_id);
        from_node = find_node(graph, from_id);
    }

    if (to_node == NULL) {
        insert_node(graph, to_id);
        to_node = find_node(graph, to_id);
    }

    Edge* edge = create_edge(to_node, amount, date);
    edge->next = from_node->edges;
    from_node->edges = edge;
}

void delete_node(Graph* graph, const char* id) {
    int hash = hash_function(id, graph->size);
    Node* current = graph->nodes[hash];
    Node* prev = NULL;

    // Traverse the bucket to find the node
    while (current != NULL && strcmp(current->id, id) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Non-existing node(s): %s\n", id);
        return;
    }

    // Delete all incoming edges pointing to this node
    for (int i = 0; i < graph->size; i++) {
        Node* node = graph->nodes[i];
        while (node != NULL) {
            Edge* prev_edge = NULL;
            Edge* edge = node->edges;

            while (edge != NULL) {
                if (strcmp(edge->target->id, id) == 0) {
                    // Remove the edge pointing to the node being deleted
                    if (prev_edge == NULL) {
                        node->edges = edge->next;
                    } else {
                        prev_edge->next = edge->next;
                    }
                    Edge* temp_edge = edge;
                    edge = edge->next;
                    free(temp_edge);  // Free the edge structure
                } else {
                    prev_edge = edge;
                    edge = edge->next;
                }
            }
            node = node->next;
        }
    }

    // Delete all outgoing edges from the node itself
    Edge* edge = current->edges;
    while (edge != NULL) {
        Edge* temp = edge;
        edge = edge->next;
        free(temp);  // Free each outgoing edge
    }

    // Remove the node itself from the hash table and free it
    if (prev == NULL) {
        graph->nodes[hash] = current->next;
    } else {
        prev->next = current->next;
    }

    free(current->id);
    free(current);
    printf("Node %s deleted.\n", id);
}

void delete_edge(Graph* graph, const char* from_id, const char* to_id) {
    Node* from_node = find_node(graph, from_id);
    if (from_node == NULL) {
        printf("Non-existing node(s): %s\n", from_id);
        return;
    }

    Edge* current = from_node->edges;
    Edge* prev = NULL;

    while (current != NULL && strcmp(current->target->id, to_id) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Edge from %s to %s not found.\n", from_id, to_id);
        return;
    }

    if (prev == NULL) {
        from_node->edges = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    printf("Edge from %s to %s deleted.\n", from_id, to_id);
}

Node* find_node(Graph* graph, const char* id) {
    int hash = hash_function(id, graph->size);
    Node* current = graph->nodes[hash];
    while (current != NULL && strcmp(current->id, id) != 0) {
        current = current->next;
    }
    return current;
}

void display_graph(Graph* graph) {
    for (int i = 0; i < graph->size; i++) {
        Node* node = graph->nodes[i];
        while (node != NULL) {
            printf("Node %s:\n", node->id);
            Edge* edge = node->edges;
            while (edge != NULL) {
                printf("  -> %s [%d units on %s]\n", edge->target->id, edge->amount, edge->date);
                edge = edge->next;
            }
            node = node->next;
        }
    }
}

void free_graph(Graph* graph) {
    // Iterate over all nodes in the graph
    for (int i = 0; i < graph->size; i++) {
        Node* node = graph->nodes[i];
        while (node != NULL) {
            Node* temp_node = node;
            Edge* edge = node->edges;

            // Free all edges associated with the current node
            while (edge != NULL) {
                Edge* temp_edge = edge;
                edge = edge->next;
                free(temp_edge);  // Free each edge structure
            }

            node = node->next;
            free(temp_node->id);  // Free the node's ID (string)
            free(temp_node);      // Free the node itself
        }
    }

    // Free the array of node pointers (hash table)
    free(graph->nodes);

    // Finally, free the graph structure itself
    free(graph);
}

// Modify an edge between two nodes
void modify_edge(Graph* graph, const char* from_id, const char* to_id, int old_sum, int new_sum, const char* old_date, const char* new_date) {
    Node* from_node = find_node(graph, from_id);
    if (from_node == NULL) {
        printf("Node %s not found.\n", from_id);
        return;
    }

    Edge* edge = from_node->edges;
    while (edge != NULL) {
        // Check if the edge matches both the target node and the old sum and date
        if (strcmp(edge->target->id, to_id) == 0 && edge->amount == old_sum && strcmp(edge->date, old_date) == 0) {
            // Modify the edge properties
            edge->amount = new_sum;
            strcpy(edge->date, new_date);
            printf("Edge from %s to %s updated: new amount = %d, new date = %s.\n", from_id, to_id, new_sum, new_date);
            return;
        }
        edge = edge->next;
    }

    printf("Edge from %s to %s with amount %d and date %s not found.\n", from_id, to_id, old_sum, old_date);
}

// Find outgoing transactions
void find_outgoing_transactions(Graph* graph, const char* id) {
    Node* node = find_node(graph, id);
    if (node == NULL) {
        printf("Node %s not found.\n", id);
        return;
    }

    Edge* edge = node->edges;
    printf("Outgoing transactions from %s:\n", id);
    while (edge != NULL) {
        printf("  -> %s [%d units on %s]\n", edge->target->id, edge->amount, edge->date);
        edge = edge->next;
    }
}

// Find incoming transactions
void find_incoming_transactions(Graph* graph, const char* id) {
    printf("Incoming transactions to %s:\n", id);
    for (int i = 0; i < graph->size; i++) {
        Node* node = graph->nodes[i];
        while (node != NULL) {
            Edge* edge = node->edges;
            while (edge != NULL) {
                if (strcmp(edge->target->id, id) == 0) {
                    printf("  <- %s [%d units on %s]\n", node->id, edge->amount, edge->date);
                }
                edge = edge->next;
            }
            node = node->next;
        }
    }
}

// Detect simple cycles using DFS
bool dfs_cycle(Graph* graph, Node* node, bool* visited, bool* rec_stack) {
    int hash = hash_function(node->id, graph->size);
    if (!visited[hash]) {
        visited[hash] = true;
        rec_stack[hash] = true;

        Edge* edge = node->edges;
        while (edge != NULL) {
            int target_hash = hash_function(edge->target->id, graph->size);
            if (!visited[target_hash] && dfs_cycle(graph, edge->target, visited, rec_stack)) {
                return true;
            } else if (rec_stack[target_hash]) {
                return true;
            }
            edge = edge->next;
        }
    }
    rec_stack[hash] = false;
    return false;
}

bool detect_cycle(Graph* graph, const char* id) {
    Node* start_node = find_node(graph, id);
    if (start_node == NULL) {
        printf("Node %s not found.\n", id);
        return false;
    }

    bool* visited = (bool*)calloc(graph->size, sizeof(bool));
    bool* rec_stack = (bool*)calloc(graph->size, sizeof(bool));

    if (dfs_cycle(graph, start_node, visited, rec_stack)) {
        printf("Cycle detected involving node %s.\n", id);
        free(visited);
        free(rec_stack);
        return true;
    } else {
        printf("No cycles involving node %s.\n", id);
        free(visited);
        free(rec_stack);
        return false;
    }
}

// Detect cycles with a minimum sum using DFS
bool dfs_cycle_min_sum(Graph* graph, Node* node, bool* visited, bool* rec_stack, int min_sum) {
    int hash = hash_function(node->id, graph->size);
    if (!visited[hash]) {
        visited[hash] = true;
        rec_stack[hash] = true;

        Edge* edge = node->edges;
        while (edge != NULL) {
            if (edge->amount >= min_sum) {
                int target_hash = hash_function(edge->target->id, graph->size);
                if (!visited[target_hash] && dfs_cycle_min_sum(graph, edge->target, visited, rec_stack, min_sum)) {
                    return true;
                } else if (rec_stack[target_hash]) {
                    return true;
                }
            }
            edge = edge->next;
        }
    }
    rec_stack[hash] = false;
    return false;
}

bool detect_cycles_with_min_sum(Graph* graph, const char* id, int k) {
    Node* start_node = find_node(graph, id);
    if (start_node == NULL) {
        printf("Node %s not found.\n", id);
        return false;
    }

    bool* visited = (bool*)calloc(graph->size, sizeof(bool));
    bool* rec_stack = (bool*)calloc(graph->size, sizeof(bool));

    if (dfs_cycle_min_sum(graph, start_node, visited, rec_stack, k)) {
        printf("Cycle detected involving node %s with minimum sum of %d.\n", id, k);
        free(visited);
        free(rec_stack);
        return true;
    } else {
        printf("No cycles involving node %s with minimum sum of %d.\n", id, k);
        free(visited);
        free(rec_stack);
        return false;
    }
}

// Trace flow from a node with a maximum depth of m
void dfs_trace_flow(Graph* graph, Node* node, int depth, int max_depth) {
    if (depth > max_depth) {
        return;
    }

    Edge* edge = node->edges;
    while (edge != NULL) {
        printf("  -> %s [%d units on %s]\n", edge->target->id, edge->amount, edge->date);
        dfs_trace_flow(graph, edge->target, depth + 1, max_depth);
        edge = edge->next;
    }
}

bool trace_flow(Graph* graph, const char* id, int m) {
    Node* start_node = find_node(graph, id);
    if (start_node == NULL) {
        printf("Node %s not found.\n", id);
        return false;
    }

    printf("Tracing flow from %s with max depth of %d:\n", id, m);
    dfs_trace_flow(graph, start_node, 0, m);
    return true;
}

// Check if two nodes are connected using DFS
bool dfs_is_connected(Graph* graph, Node* node, const char* target_id, bool* visited) {
    if (strcmp(node->id, target_id) == 0) {
        return true;
    }

    int hash = hash_function(node->id, graph->size);
    visited[hash] = true;

    Edge* edge = node->edges;
    while (edge != NULL) {
        int target_hash = hash_function(edge->target->id, graph->size);
        if (!visited[target_hash] && dfs_is_connected(graph, edge->target, target_id, visited)) {
            return true;
        }
        edge = edge->next;
    }
    return false;
}

bool is_connected(Graph* graph, const char* from_id, const char* to_id) {
    Node* from_node = find_node(graph, from_id);
    if (from_node == NULL) {
        printf("Node %s not found.\n", from_id);
        return false;
    }

    Node* to_node = find_node(graph, to_id);
    if (to_node == NULL) {
        printf("Node %s not found.\n", to_id);
        return false;
    }

    bool* visited = (bool*)calloc(graph->size, sizeof(bool));
    bool connected = dfs_is_connected(graph, from_node, to_id, visited);
    free(visited);

    if (connected) {
        printf("%s is connected to %s.\n", from_id, to_id);
    } else {
        printf("%s is not connected to %s.\n", from_id, to_id);
    }

    return connected;
}
