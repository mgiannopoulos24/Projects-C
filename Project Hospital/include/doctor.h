#ifndef DOCTOR_H
#define DOCTOR_H

#define MAX_DOCTORS 50

#define MAX_NAME_LENGTH 50
#define MAX_ID_LENGTH 10

typedef struct {
    char id[MAX_ID_LENGTH];
    char name[MAX_NAME_LENGTH];
    char department[MAX_NAME_LENGTH];
} Doctor;

void add_doctor(Doctor doctors[], int *doctor_count);
void display_doctors(Doctor doctors[], int doctor_count);

#endif
