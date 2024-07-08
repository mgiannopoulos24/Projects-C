#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "schedule_srtf.h"
#include "CPU.h"

// Συνάρτηση για την προσθήκη μιας διεργασίας στη λίστα χρονοπρογραμματισμού SRTF
void addTaskSRTF(Task** schedule_list, Task* newTask) {
    if (*schedule_list == NULL || (*schedule_list)->burst_time > newTask->burst_time) {
        newTask->next = *schedule_list;
        *schedule_list = newTask;
    } else {
        Task* current = *schedule_list;
        while (current->next != NULL && current->next->burst_time <= newTask->burst_time) {
            current = current->next;
        }
        newTask->next = current->next;
        current->next = newTask;
    }
}

// Συνάρτηση για τον χρονοπρογραμματισμό των διεργασιών με βάση τον αλγόριθμο SRTF
void scheduleSRTF(Task** schedule_list) {
    printf("Scheduling tasks using SRTF...\n");
    while (*schedule_list != NULL) {
        Task* shortest = *schedule_list;
        *schedule_list = (*schedule_list)->next;
        run(shortest, shortest->burst_time);
        free(shortest);
    }
}

// Συνάρτηση για το διάβασμα των διεργασιών από ένα αρχείο
void readTasksFromFile(char* filename, Task** schedule_list) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    char name[20];
    int arrival_time, priority, burst_time, deadline;
    while (fscanf(file, "%s %d %d %d %d", name, &arrival_time, &priority, &burst_time, &deadline) == 5) {
        Task* newTask = (Task*)malloc(sizeof(Task));
        if (newTask == NULL) {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }
        strcpy(newTask->name, name);
        newTask->arrival_time = arrival_time;
        newTask->priority = priority;
        newTask->burst_time = burst_time;
        newTask->deadline = deadline;
        newTask->next = NULL;
        addTaskSRTF(schedule_list, newTask);
        printf("read [%s] [%d] [%d] [%d] [%d]\n", name, arrival_time, priority, burst_time, deadline);
    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <schedule_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    Task *schedule_list = NULL;
    readTasksFromFile(argv[1], &schedule_list);
    scheduleSRTF(&schedule_list);

    return EXIT_SUCCESS;
}
