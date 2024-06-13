#include <stdio.h>
#include <string.h>
#include "doctor.h"

void add_doctor(Doctor doctors[], int *doctor_count) {
    if (*doctor_count >= MAX_DOCTORS) {
        printf("Doctor database full. Cannot add more doctors.\n");
        return;
    }

    printf("Enter doctor ID: ");
    scanf("%s", doctors[*doctor_count].id);

    printf("Enter doctor name: ");
    getchar(); // Consume newline character left by previous scanf or other input
    fgets(doctors[*doctor_count].name, MAX_NAME_LENGTH, stdin);
    doctors[*doctor_count].name[strcspn(doctors[*doctor_count].name, "\n")] = '\0'; // Remove newline if present

    printf("Enter doctor department: ");
    fgets(doctors[*doctor_count].department, MAX_NAME_LENGTH, stdin);
    doctors[*doctor_count].department[strcspn(doctors[*doctor_count].department, "\n")] = '\0'; // Remove newline if present

    (*doctor_count)++;
}

void display_doctors(Doctor doctors[], int doctor_count) {
    printf("\n--- List of Doctors ---\n");
    for (int i = 0; i < doctor_count; i++) {
        printf("ID: %s, Name: %s, Department: %s\n",
               doctors[i].id, doctors[i].name, doctors[i].department);
    }
}
