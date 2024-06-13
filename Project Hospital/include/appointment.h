#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#define MAX_APPOINTMENTS 100

#define MAX_NAME_LENGTH 50
#define MAX_ID_LENGTH 10

#include "patient.h"
#include "doctor.h"

typedef struct {
    char id[MAX_ID_LENGTH];
    char patient_id[MAX_ID_LENGTH];
    char doctor_id[MAX_ID_LENGTH];
    char date[20];
    char time[10];
} Appointment;

void schedule_appointment(Appointment appointments[], int *appointment_count,
                          Patient patients[], int patient_count,
                          Doctor doctors[], int doctor_count);
void display_appointments(Appointment appointments[], int appointment_count,
                          Patient patients[], int patient_count,
                          Doctor doctors[], int doctor_count);

#endif
