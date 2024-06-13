#include <stdio.h>
#include <string.h>
#include "patient.h"

void add_patient(Patient patients[], int *patient_count) {
    if (*patient_count >= MAX_PATIENTS) {
        printf("Patient database full. Cannot add more patients.\n");
        return;
    }

    printf("Enter patient ID: ");
    scanf("%s", patients[*patient_count].id);

    printf("Enter patient name: ");
    getchar(); // Consume newline character left by previous scanf or other input
    fgets(patients[*patient_count].name, MAX_NAME_LENGTH, stdin);
    patients[*patient_count].name[strcspn(patients[*patient_count].name, "\n")] = '\0'; // Remove newline if present

    printf("Enter patient age: ");
    scanf("%d", &patients[*patient_count].age);

    printf("Enter patient gender (M/F): ");
    scanf(" %c", &patients[*patient_count].gender);

    printf("Enter patient phone number: ");
    scanf("%s", patients[*patient_count].phone);

    (*patient_count)++;
}

void display_patients(Patient patients[], int patient_count) {
    printf("\n--- List of Patients ---\n");
    for (int i = 0; i < patient_count; i++) {
        printf("ID: %s, Name: %s, Age: %d, Gender: %c, Phone: %s\n",
               patients[i].id, patients[i].name, patients[i].age,
               patients[i].gender, patients[i].phone);
    }
}
