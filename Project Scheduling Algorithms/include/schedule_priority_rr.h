#ifndef SCHEDULE_PRIORITY_RR_H
#define SCHEDULE_PRIORITY_RR_H

#include "list.h"

// Συνάρτηση για την προσθήκη μιας διεργασίας στη λίστα χρονοπρογραμματισμού Priority RR
void addTaskPriorityRR(Task** schedule_list, Task* newTask);

// Συνάρτηση για τον χρονοπρογραμματισμό των διεργασιών με βάση τον αλγόριθμο Priority RR
void schedulePriorityRR(Task** schedule_list);

#endif // SCHEDULE_PRIORITY_RR_H
