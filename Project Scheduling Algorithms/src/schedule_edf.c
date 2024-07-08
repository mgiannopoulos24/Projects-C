#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "schedule_edf.h"
#include "CPU.h"


void addTaskEDF(Task** schedule_list, Task* newTask) {
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


void scheduleEDF(Task** schedule_list) {
    printf("Scheduling tasks using Earliest Deadline First (EDF)...\n");
    int currentTime = 0;
    while (*schedule_list != NULL) {
        Task* earliestDeadlineTask = *schedule_list;
        Task* current = *schedule_list;
        while (current != NULL) {
            if (current->arrival_time <= currentTime && current->deadline < earliestDeadlineTask->deadline) {
                earliestDeadlineTask = current;
            }
            current = current->next;
        }
        if (earliestDeadlineTask->arrival_time > currentTime) {
            currentTime = earliestDeadlineTask->arrival_time;
        }
        if (earliestDeadlineTask->burst_time > earliestDeadlineTask->deadline - currentTime) {
            printf("Missed deadline for task %s\n", earliestDeadlineTask->name);
            // Δεν ελευθερώνουμε τη μνήμη αν η διεργασία δεν έχει ολοκληρώσει την εκτέλεσή της
            *schedule_list = earliestDeadlineTask->next;
        } else {
            run(earliestDeadlineTask, earliestDeadlineTask->burst_time);
            currentTime += earliestDeadlineTask->burst_time;
            // Ελευθερώνουμε τη μνήμη μόνο αν η διεργασία έχει ολοκληρώσει την εκτέλεσή της
            if (earliestDeadlineTask->deadline <= currentTime) {
                *schedule_list = earliestDeadlineTask->next;
                free(earliestDeadlineTask);
            }
        }
    }
}




// Συνάρτηση για τη διάβαση των διεργασιών από ένα αρχείο
void readTasksFromFile(char* filename, Task** schedule_list) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    char name[20];
    int arrival_time, priority, burst_time, deadline;
    while (fscanf(file, "%s %d %d %d %d", name, &arrival_time, &priority, &burst_time, &deadline) == 5) {
        Task* newTask = createTask(name, arrival_time, priority, burst_time, deadline);
        addTaskEDF(schedule_list, newTask);
        printf("read [%s] [%d] [%d] [%d] [%d]\n", name, arrival_time, priority, burst_time, deadline);
    }
    fclose(file);
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    Task* schedule_list = NULL;  // Αρχικοποίηση της λίστας των διεργασιών

    readTasksFromFile(argv[1], &schedule_list);  // Διάβασμα των διεργασιών από το αρχείο

    scheduleEDF(&schedule_list);  // Χρονοπρογραμματισμός των διεργασιών με EDF

    return 0;
}
