#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "CPU.h"
#include "schedule_fcfs.h"

// Συνάρτηση για την προσθήκη μιας διεργασίας στη λίστα χρονοπρογραμματισμού FCFS
void addTaskFCFS(Task** schedule_list, Task* newTask) {
    if (*schedule_list == NULL) {
        *schedule_list = newTask;
    } else {
        Task* current = *schedule_list;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newTask;
    }
}

// Συνάρτηση για τον χρονοπρογραμματισμό των διεργασιών με βάση τον αλγόριθμο FCFS
void scheduleFCFS(Task** schedule_list) {
    printf("Scheduling tasks using FCFS...\n");
    while (*schedule_list != NULL) {
        run(*schedule_list, (*schedule_list)->burst_time);
        Task* temp = *schedule_list;
        *schedule_list = (*schedule_list)->next;
        free(temp);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Διαβάζουμε τις διεργασίες από το αρχείο
    Task* tasks = NULL;
    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    char name[20];
    int arrival_time, priority, burst_time, period;
    while (fscanf(file, "%s %d %d %d %d", name, &arrival_time, &priority, &burst_time, &period) == 5) {
        Task* newTask = createTask(name, arrival_time, priority, burst_time, period);
        addTaskFCFS(&tasks, newTask);
        printf("read [%s] [%d] [%d] [%d] [%d]\n", name, arrival_time, priority, burst_time, period);
    }
    fclose(file);

    // Εκτέλεση των διεργασιών με τον αλγόριθμο FCFS
    scheduleFCFS(&tasks);

    return 0;
}
