#ifndef PATIENT_H
#define PATIENT_H

#define MAX_NAME_LENGTH 50
#define MAX_ID_LENGTH 10
#define MAX_PATIENTS 100   

typedef struct {
    char id[MAX_ID_LENGTH];
    char name[MAX_NAME_LENGTH];
    int age;
    char gender;
    char phone[MAX_ID_LENGTH];
} Patient;

void add_patient(Patient patients[], int *patient_count);
void display_patients(Patient patients[], int patient_count);

#endif
