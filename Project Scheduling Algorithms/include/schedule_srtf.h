#ifndef SCHEDULE_SRTF_H
#define SCHEDULE_SRTF_H

#include "list.h"

// Συνάρτηση για την προσθήκη μιας διεργασίας στη λίστα χρονοπρογραμματισμού SRTF
void addTaskSRTF(Task** schedule_list, Task* newTask);

// Συνάρτηση για τον χρονοπρογραμματισμό των διεργασιών με βάση τον αλγόριθμο SRTF
void scheduleSRTF(Task** schedule_list);

#endif // SCHEDULE_SRTF_H
