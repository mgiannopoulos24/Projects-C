#include "mysort.h"

void parse_args(int argc, char *argv[], char **input_file, int *k, char **sort_exec1, char **sort_exec2) {
    if (argc < 9) {
        fprintf(stderr, "Usage: %s -i input_file -k num_children -e1 sort_exec1 -e2 sort_exec2\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            if (i + 1 < argc) {
                *input_file = argv[++i];
            } else {
                fprintf(stderr, "Error: Missing argument for -i\n");
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(argv[i], "-k") == 0) {
            if (i + 1 < argc) {
                *k = atoi(argv[++i]);
            } else {
                fprintf(stderr, "Error: Missing argument for -k\n");
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(argv[i], "-e1") == 0) {
            if (i + 1 < argc) {
                *sort_exec1 = argv[++i];
            } else {
                fprintf(stderr, "Error: Missing argument for -e1\n");
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(argv[i], "-e2") == 0) {
            if (i + 1 < argc) {
                *sort_exec2 = argv[++i];
            } else {
                fprintf(stderr, "Error: Missing argument for -e2\n");
                exit(EXIT_FAILURE);
            }
        } else {
            fprintf(stderr, "Unknown argument: %s\n", argv[i]);
            fprintf(stderr, "Usage: %s -i input_file -k num_children -e1 sort_exec1 -e2 sort_exec2\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if (*input_file == NULL || *k <= 0 || *sort_exec1 == NULL || *sort_exec2 == NULL) {
        fprintf(stderr, "Invalid arguments\n");
        exit(EXIT_FAILURE);
    }
}


void create_hierarchy(const char *input_file, int k, const char *sort_exec1, const char *sort_exec2) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Call splitter_merger with the input_file
        for (int i = 0; i < k; i++) {
            splitter_merger(input_file, k - i, (i % 2 == 0) ? sort_exec1 : sort_exec2);
        }
        exit(EXIT_SUCCESS);
    } else {
        wait(NULL);
    }
}

int main(int argc, char *argv[]) {
    char *input_file = NULL;
    int k = 0;
    char *sort_exec1 = NULL;
    char *sort_exec2 = NULL;

    parse_args(argc, argv, &input_file, &k, &sort_exec1, &sort_exec2);
    create_hierarchy(input_file, k, sort_exec1, sort_exec2);

    return 0;
}
