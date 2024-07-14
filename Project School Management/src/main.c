#include <stdio.h>
#include "student.h"

int main() {
    struct Student students[MAX_STUDENTS];
    int studentCount = 0;
    int choice;
    int rollNumber;
    char firstName[50];
    char course[100];

    do {
        printf("\n\nSchool Management System\n");
        printf("1. Add Student\n");
        printf("2. Find Student by Roll Number\n");
        printf("3. Find Student by First Name\n");
        printf("4. Find Students by Course\n");
        printf("5. Display Student Count\n");
        printf("6. Delete Student\n");
        printf("7. Update Student\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(students, &studentCount);
                break;
            case 2:
                printf("Enter roll number: ");
                scanf("%d", &rollNumber);
                findStudentByRollNumber(students, studentCount, rollNumber);
                break;
            case 3:
                printf("Enter first name: ");
                scanf("%s", firstName);
                findStudentByFirstName(students, studentCount, firstName);
                break;
            case 4:
                printf("Enter course: ");
                scanf("%s", course);
                findStudentsByCourse(students, studentCount, course);
                break;
            case 5:
                displayStudentCount(studentCount);
                break;
            case 6:
                printf("Enter roll number to delete: ");
                scanf("%d", &rollNumber);
                deleteStudent(students, &studentCount, rollNumber);
                break;
            case 7:
                printf("Enter roll number to update: ");
                scanf("%d", &rollNumber);
                updateStudent(students, studentCount, rollNumber);
                break;
            case 8:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 8.\n");
        }
    } while (choice != 8);

    return 0;
}
