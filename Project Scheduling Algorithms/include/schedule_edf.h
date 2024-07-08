#ifndef SCHEDULE_EDF_H
#define SCHEDULE_EDF_H

#include "list.h"

void scheduleEDF(Task** schedule_list);
void addTaskEDF(Task** schedule_list, Task* newTask);

#endif /* SCHEDULE_EDF_H */
