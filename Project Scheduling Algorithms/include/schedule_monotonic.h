#ifndef SCHEDULE_MONOTONIC_H
#define SCHEDULE_MONOTONIC_H

#include "list.h"

// Συνάρτηση για την προσθήκη μιας διεργασίας στη λίστα χρονοπρογραμματισμού Rate Monotonic
void addTaskMonotonic(Task** schedule_list, Task* newTask);

// Συνάρτηση για τον χρονοπρογραμματισμό των διεργασιών με βάση τον αλγόριθμο Rate Monotonic
void scheduleMonotonic(Task** schedule_list);

#endif // SCHEDULE_MONOTONIC_H
