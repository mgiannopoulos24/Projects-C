#include <stdio.h>
#include <string.h>
#include "student.h"

// Function to add a new student
void addStudent(struct Student students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Cannot add more students. Maximum limit reached.\n");
        return;
    }

    struct Student newStudent;

    // Input new student details
    printf("Enter roll number: ");
    scanf("%d", &newStudent.rollNumber);

    // Check if roll number already exists
    for (int i = 0; i < *count; i++) {
        if (students[i].rollNumber == newStudent.rollNumber) {
            printf("Error: Student with roll number %d already exists.\n", newStudent.rollNumber);
            return; // Exit function without adding duplicate student
        }
    }

    // Clear input buffer
    while (getchar() != '\n');

    printf("Enter first name: ");
    scanf("%s", newStudent.firstName);

    printf("Enter last name: ");
    scanf("%s", newStudent.lastName);

    printf("Enter course: ");
    scanf(" %[^\n]s", newStudent.course); // Read entire line including spaces

    printf("Enter age: ");
    scanf("%d", &newStudent.age);

    // Add new student to the array
    students[*count] = newStudent;
    (*count)++;

    // Save student to file
    FILE *fp = fopen("students.txt", "a"); // Open file in append mode
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(fp, "%d %s %s %s %d\n", newStudent.rollNumber, newStudent.firstName, newStudent.lastName, newStudent.course, newStudent.age);

    fclose(fp); // Close file

    printf("Student added successfully.\n");
}

// Function to find a student by roll number
void findStudentByRollNumber(struct Student students[], int count, int rollNumber) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (students[i].rollNumber == rollNumber) {
            printf("Student found:\n");
            printf("Roll Number: %d\n", students[i].rollNumber);
            printf("Name: %s %s\n", students[i].firstName, students[i].lastName);
            printf("Course: %s\n", students[i].course);
            printf("Age: %d\n", students[i].age);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Student with roll number %d not found.\n", rollNumber);
    }
}

// Function to find students by first name
void findStudentByFirstName(struct Student students[], int count, const char *firstName) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].firstName, firstName) == 0) {
            printf("Student found:\n");
            printf("Roll Number: %d\n", students[i].rollNumber);
            printf("Name: %s %s\n", students[i].firstName, students[i].lastName);
            printf("Course: %s\n", students[i].course);
            printf("Age: %d\n", students[i].age);
            found = 1;
        }
    }
    if (!found) {
        printf("No student found with first name '%s'.\n", firstName);
    }
}

// Function to find students by course
void findStudentsByCourse(struct Student students[], int count, const char *course) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].course, course) == 0) {
            printf("Student found:\n");
            printf("Roll Number: %d\n", students[i].rollNumber);
            printf("Name: %s %s\n", students[i].firstName, students[i].lastName);
            printf("Course: %s\n", students[i].course);
            printf("Age: %d\n", students[i].age);
            found = 1;
        }
    }
    if (!found) {
        printf("No students registered in course '%s'.\n", course);
    }
}

// Function to display count of students
void displayStudentCount(int count) {
    printf("Total number of students: %d\n", count);
}

// Function to delete a student by roll number
void deleteStudent(struct Student students[], int *count, int rollNumber) {
    int found = 0;
    for (int i = 0; i < *count; i++) {
        if (students[i].rollNumber == rollNumber) {
            // Shift all elements after the deleted element one position back
            for (int j = i; j < *count - 1; j++) {
                students[j] = students[j + 1];
            }
            (*count)--;
            found = 1;
            printf("Student with roll number %d deleted successfully.\n", rollNumber);
            break;
        }
    }
    if (!found) {
        printf("Student with roll number %d not found.\n", rollNumber);
    }
}

// Function to update student details
void updateStudent(struct Student students[], int count, int rollNumber) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (students[i].rollNumber == rollNumber) {
            printf("Enter new first name: ");
            scanf("%s", students[i].firstName);
            printf("Enter new last name: ");
            scanf("%s", students[i].lastName);
            printf("Enter new course: ");
            scanf("%s", students[i].course);
            printf("Enter new age: ");
            scanf("%d", &students[i].age);
            found = 1;
            printf("Student details updated successfully.\n");
            break;
        }
    }
    if (!found) {
        printf("Student with roll number %d not found.\n", rollNumber);
    }
}
