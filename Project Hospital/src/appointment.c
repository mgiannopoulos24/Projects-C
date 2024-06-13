#include <stdio.h>
#include "appointment.h"
#include "patient.h"
#include "doctor.h"

void schedule_appointment(Appointment appointments[], int *appointment_count,
                          Patient patients[], int patient_count,
                          Doctor doctors[], int doctor_count) {
    if (*appointment_count >= MAX_APPOINTMENTS) {
        printf("Appointment schedule full. Cannot schedule more appointments.\n");
        return;
    }

    printf("Enter appointment ID: ");
    scanf("%s", appointments[*appointment_count].id);

    printf("Enter patient ID: ");
    scanf("%s", appointments[*appointment_count].patient_id);

    printf("Enter doctor ID: ");
    scanf("%s", appointments[*appointment_count].doctor_id);

    printf("Enter date (DD/MM/YYYY): ");
    scanf("%s", appointments[*appointment_count].date);

    printf("Enter time (HH:MM): ");
    scanf("%s", appointments[*appointment_count].time);

    (*appointment_count)++;
}

void display_appointments(Appointment appointments[], int appointment_count,
                          Patient patients[], int patient_count,
                          Doctor doctors[], int doctor_count) {
    printf("\n--- List of Appointments ---\n");
    for (int i = 0; i < appointment_count; i++) {
        printf("ID: %s, Patient: %s (%s), Doctor: %s (%s), Date: %s, Time: %s\n",
               appointments[i].id,
               patients[i].name, appointments[i].patient_id,
               doctors[i].name, appointments[i].doctor_id,
               appointments[i].date, appointments[i].time);
    }
}
