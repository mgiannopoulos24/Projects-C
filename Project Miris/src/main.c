// main.c
#include "graph.h"
#include <stdbool.h>

void display_help() {
    printf("Unrecognized command\n");
}

void process_commands(Graph* graph) {
    char command[256];
    char node1[100], node2[100], date[11], date1[11];
    int sum, sum1, k, m;
    bool running = true;

    while (running) {
        printf("miris> ");
        fgets(command, sizeof(command), stdin);

        if (strncmp(command, "i ", 2) == 0) {
            char* token = strtok(command + 2, " \n");
            while (token != NULL) {
                insert_node(graph, token);
                token = strtok(NULL, " \n");
            }

        } else if (sscanf(command, "n %s %s %d %s", node1, node2, &sum, date) == 4) {
            insert_edge(graph, node1, node2, sum, date);

        } else if (strncmp(command, "d ", 2) == 0) {
            char* token = strtok(command + 2, " \n");
            while (token != NULL) {
                delete_node(graph, token);
                token = strtok(NULL, " \n");
            }

        } else if (sscanf(command, "l %s %s", node1, node2) == 2) {
            delete_edge(graph, node1, node2);

        } else if (sscanf(command, "m %s %s %d %d %s %s", node1, node2, &sum, &sum1, date, date1) == 6) {
            modify_edge(graph, node1, node2, sum, sum1, date, date1);

        } else if (sscanf(command, "f %s", node1) == 1) {
            find_outgoing_transactions(graph, node1);

        } else if (sscanf(command, "r %s", node1) == 1) {
            find_incoming_transactions(graph, node1);

        } else if (sscanf(command, "c %s", node1) == 1) {
            detect_cycle(graph, node1);

        } else if (sscanf(command, "f %s %d", node1, &k) == 2) {
            detect_cycles_with_min_sum(graph, node1, k);

        } else if (sscanf(command, "t %s %d", node1, &m) == 2) {
            trace_flow(graph, node1, m);

        } else if (sscanf(command, "o %s %s", node1, node2) == 2) {
            is_connected(graph, node1, node2);

        } else if (strncmp(command, "e", 1) == 0) {
            size_t bytes_released = sizeof(Graph) + graph->size * sizeof(Node*) + (graph->size * sizeof(Node)) + (graph->size * sizeof(Edge));
            printf("%zu Bytes released\n", bytes_released);
            running = false;

        } else {
            display_help();
        }
    }
}

// Function to write the graph to an output file
void write_graph_to_file(Graph* graph, const char* output_file) {
    FILE* file = fopen(output_file, "w");
    if (file == NULL) {
        perror("Failed to open output file");
        return;
    }

    // Iterate over all nodes and write them to the file
    for (int i = 0; i < graph->size; i++) {
        Node* node = graph->nodes[i];
        while (node != NULL) {
            if (node->edges == NULL) {
                fprintf(file, "Node %s: (no edges)\n", node->id);
            } else {
                fprintf(file, "Node %s:", node->id);
            }
            Edge* edge = node->edges;
            while (edge != NULL) {
                fprintf(file, "  -> %s [%d units on %s]\n", edge->target->id, edge->amount, edge->date);
                edge = edge->next;
            }
            node = node->next;
        }
    }

    fclose(file);
}

int main(int argc, char** argv) {
    if (argc < 5) {
        printf("Format error: %s -i inputfile -o outfile\n", argv[0]);
        return 1;
    }

    const char* input_file = NULL;
    const char* output_dot_file = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            input_file = argv[++i];
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            output_dot_file = argv[++i];
        }
    }

    if (input_file == NULL || output_dot_file == NULL) {
        printf("Invalid input or output file\n");
        return 1;
    }

    Graph* graph = create_graph(100);

    FILE* file = fopen(input_file, "r");
    if (file == NULL) {
        perror("Failed to open input file");
        return 1;
    }

    char from[100], to[100], date[11];
    int amount;
    while (fscanf(file, "%s %s %d %s", from, to, &amount, date) != EOF) {
        insert_edge(graph, from, to, amount, date);
    }
    fclose(file);

    process_commands(graph);
    
    // Write the final state of the graph to the output file
    write_graph_to_file(graph, output_dot_file);

    free_graph(graph);

    return 0;
}