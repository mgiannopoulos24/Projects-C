#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "todo_list.h"

#define INITIAL_CAPACITY 10

static Task *tasks = NULL;
static int num_tasks = 0;
static int capacity = 0;

void add_task(const char *description) {
    if (num_tasks >= capacity) {
        if (capacity == 0) {
            capacity = INITIAL_CAPACITY;
            tasks = malloc(capacity * sizeof(Task));
        } else {
            capacity *= 2;
            tasks = realloc(tasks, capacity * sizeof(Task));
        }
        if (tasks == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(1);
        }
    }
    strcpy(tasks[num_tasks].description, description);
    num_tasks++;
    printf("Task added successfully.\n");
}

void view_tasks() {
    if (num_tasks == 0) {
        printf("No tasks added yet.\n");
    } else {
        printf("===== Tasks =====\n");
        for (int i = 0; i < num_tasks; ++i) {
            printf("%d. %s\n", i + 1, tasks[i].description);
        }
    }
}

void remove_task(int index) {
    if (index < 1 || index > num_tasks) {
        printf("Invalid index.\n");
    } else {
        for (int i = index - 1; i < num_tasks - 1; ++i) {
            strcpy(tasks[i].description, tasks[i + 1].description);
        }
        num_tasks--;
        printf("Task removed successfully.\n");
    }
}

void cleanup() {
    free(tasks);
    tasks = NULL;
    num_tasks = 0;
    capacity = 0;
}

void load_tasks_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[MAX_TASK_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // Remove newline character
        add_task(line);
    }

    fclose(file);
}

void save_tasks_to_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < num_tasks; ++i) {
        fprintf(file, "%s\n", tasks[i].description);
    }

    fclose(file);
}
