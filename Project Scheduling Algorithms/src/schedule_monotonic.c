#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "schedule_monotonic.h"
#include "CPU.h"

// Διάβασμα των διεργασιών από ένα αρχείο
void readTasksFromFile(char* filename, Task** schedule_list) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    char name[50];
    int arrival_time, priority, burst_time, deadline;
    while (fscanf(file, "%s %d %d %d %d", name, &arrival_time, &priority, &burst_time, &deadline) == 5) {
        Task* newTask = createTask(name, arrival_time, priority, burst_time, deadline);
        insertTask(schedule_list, newTask);
        printf("read [%s] [%d] [%d] [%d] [%d]\n", name, arrival_time, priority, burst_time, deadline);
    }
    fclose(file);
}

// Συνάρτηση για την προσθήκη μιας διεργασίας στη λίστα χρονοπρογραμματισμού Rate Monotonic
void addTaskMonotonic(Task** schedule_list, Task* newTask) {
    if (*schedule_list == NULL || newTask->deadline < (*schedule_list)->deadline) {
        newTask->next = *schedule_list;
        *schedule_list = newTask;
    } else {
        Task* current = *schedule_list;
        while (current->next != NULL && current->next->deadline <= newTask->deadline) {
            current = current->next;
        }
        newTask->next = current->next;
        current->next = newTask;
    }
}

// Συνάρτηση για τον χρονοπρογραμματισμό των διεργασιών με βάση τον αλγόριθμο Rate Monotonic
void scheduleMonotonic(Task** schedule_list) {
    printf("Scheduling tasks using Rate Monotonic...\n");
    int currentTime = 0;
    while (*schedule_list != NULL) {
        Task* current = *schedule_list;
        while (current != NULL) {
            if (currentTime % current->deadline == 0) {
                if (current->burst_time > current->deadline) {
                    printf("Missed deadline for task %s\n", current->name);
                } else {
                    run(current, current->burst_time);
                    // Αφαίρεση της διεργασίας από τη λίστα
                    *schedule_list = current->next;
                    free(current);
                }
            }
            current = current->next;
        }
        currentTime++;
    }
}


// Κύρια συνάρτηση
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <schedule_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    Task* schedule_list = NULL;

    // Διάβασμα των διεργασιών από το αρχείο προγράμματος
    readTasksFromFile(argv[1], &schedule_list);

    // Χρονοπρογραμματισμός των διεργασιών με βάση τον αλγόριθμο Monotonic
    scheduleMonotonic(&schedule_list);

    return EXIT_SUCCESS;
}
