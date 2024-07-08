#include <stdio.h>
#include "CPU.h"

// Συνάρτηση για την εκτέλεση ενός Task στη CPU
void run(Task* task, int time) {
    if (task != NULL) {
        printf("Running task %s for %d time units.\n", task->name, time);
    } else {
        printf("No task to run.\n");
    }
}
