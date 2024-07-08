#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "CPU.h"
#include "schedule_fcfs.h"

// Συνάρτηση για το διάβασμα του αρχείου εισόδου και τη δημιουργία της λίστας των Task
void readInputFile(char* filename, Task** head) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Could not open input file");
        return;
    }

    char name[50];
    int arrival_time, priority, burst_time, period;
    while (fscanf(file, "%s %d %d %d %d", name, &arrival_time, &priority, &burst_time, &period) == 5) {
        Task* newTask = createTask(name, arrival_time, priority, burst_time, period);
        addTaskFCFS(head, newTask);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    char* input_file = argv[1];
    Task* task_list = NULL;

    // Διάβασμα του αρχείου εισόδου και δημιουργία της λίστας των Task
    readInputFile(input_file, &task_list);

    // Κλήση της συνάρτησης scheduleFCFS για τον χρονοπρογραμματισμό των Task
    scheduleFCFS(task_list);

    // Καθαρισμός της λίστας των Task
    Task* temp;
    while (task_list != NULL) {
        temp = task_list;
        task_list = task_list->next;
        free(temp);
    }

    return 0;
}
