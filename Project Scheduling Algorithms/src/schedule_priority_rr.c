#include <stdio.h>
#include <stdlib.h>
#include "schedule_priority_rr.h"
#include "CPU.h"
#include "list.h"

#define TIME_QUANTUM 4  // Ορισμός του χρόνου εκ περιτροπής

void readTasksFromFile(char* filename, Task** schedule_list) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    char name[20];
    int arrival_time, priority, burst_time;
    while (fscanf(file, "%s %d %d %d", name, &arrival_time, &priority, &burst_time) == 4) {
        Task* newTask = createTask(name, arrival_time, priority, burst_time, 0);
        insertTask(schedule_list, newTask);
        printf("read [%s] [%d] [%d] [%d]\n", name, arrival_time, priority, burst_time);
    }
    fclose(file);
}

void schedulePriorityRR(Task** schedule_list) {
    printf("Scheduling tasks using Priority RR...\n");
    while (*schedule_list != NULL) {
        Task* current = *schedule_list;
        Task* prev = NULL;
        while (current != NULL) {
            int runtime = (current->burst_time < TIME_QUANTUM) ? current->burst_time : TIME_QUANTUM;
            run(current, runtime);
            current->burst_time -= runtime;
            if (current->burst_time <= 0) {
                if (prev == NULL) {
                    *schedule_list = current->next;
                } else {
                    prev->next = current->next;
                }
                Task* temp = current;
                current = current->next;
                free(temp);
            } else {
                prev = current;
                current = current->next;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <schedule_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    Task* schedule_list = NULL;

    // Διάβασμα των διεργασιών από το αρχείο schedule.txt
    readTasksFromFile(argv[1], &schedule_list);

    // Χρονοπρογραμματισμός των διεργασιών με βάση τον αλγόριθμο Priority RR
    schedulePriorityRR(&schedule_list);

    return EXIT_SUCCESS;
}
