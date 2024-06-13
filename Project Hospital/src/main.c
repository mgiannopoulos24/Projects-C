#include <stdio.h>
#include "patient.h"
#include "doctor.h"
#include "appointment.h"

#define MAX_DOCTORS 50
#define MAX_APPOINTMENTS 100

int main() {
    Patient patients[MAX_PATIENTS];
    Doctor doctors[MAX_DOCTORS];
    Appointment appointments[MAX_APPOINTMENTS];
    int patient_count = 0;
    int doctor_count = 0;
    int appointment_count = 0;
    int choice;

    do {
        printf("\n--- Hospital Management System ---\n");
        printf("1. Add Patient\n");
        printf("2. Display Patients\n");
        printf("3. Add Doctor\n");
        printf("4. Display Doctors\n");
        printf("5. Schedule Appointment\n");
        printf("6. Display Appointments\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_patient(patients, &patient_count);
                break;
            case 2:
                display_patients(patients, patient_count);
                break;
            case 3:
                add_doctor(doctors, &doctor_count);
                break;
            case 4:
                display_doctors(doctors, doctor_count);
                break;
            case 5:
                schedule_appointment(appointments, &appointment_count,
                                    patients, patient_count,
                                    doctors, doctor_count);
                break;
            case 6:
                display_appointments(appointments, appointment_count,
                                    patients, patient_count,
                                    doctors, doctor_count);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}
