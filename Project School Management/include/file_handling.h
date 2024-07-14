#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include "student.h"

void saveStudentsToFile(struct Student students[], int count);
int loadStudentsFromFile(struct Student students[]);

#endif // FILE_HANDLING_H
