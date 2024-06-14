#include <stdio.h>
#include <string.h>
#include "staff.h"

#define MAX_STAFF 100

typedef struct {
    int staffID;
    char name[50];
    char position[50];
    char department[50];
} Staff;

Staff staffList[MAX_STAFF];
int staffCount = 0;

void manageStaff() {
    int choice;

    while (1) {
        printf("\nStaff Management\n");
        printf("1. Add Staff\n");
        printf("2. Remove Staff\n");
        printf("3. List Staff\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStaff();
                break;
            case 2:
                removeStaff();
                break;
            case 3:
                listStaff();
                break;
            case 4:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void addStaff() {
    if (staffCount >= MAX_STAFF) {
        printf("Cannot add more staff. Maximum limit reached.\n");
        return;
    }

    Staff newStaff;
    printf("Enter staff ID: ");
    scanf("%d", &newStaff.staffID);
    printf("Enter name: ");
    scanf("%s", newStaff.name);
    printf("Enter position: ");
    scanf("%s", newStaff.position);
    printf("Enter department: ");
    scanf("%s", newStaff.department);

    staffList[staffCount++] = newStaff;
    printf("Staff member added successfully.\n");
}

void removeStaff() {
    int staffID;
    printf("Enter staff ID to remove: ");
    scanf("%d", &staffID);

    int found = 0;
    for (int i = 0; i < staffCount; i++) {
        if (staffList[i].staffID == staffID) {
            for (int j = i; j < staffCount - 1; j++) {
                staffList[j] = staffList[j + 1];
            }
            staffCount--;
            found = 1;
            printf("Staff member removed successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Staff member not found.\n");
    }
}

void listStaff() {
    if (staffCount == 0) {
        printf("No staff members available.\n");
        return;
    }

    printf("\nList of Staff Members:\n");
    for (int i = 0; i < staffCount; i++) {
        printf("Staff ID: %d\n", staffList[i].staffID);
        printf("Name: %s\n", staffList[i].name);
        printf("Position: %s\n", staffList[i].position);
        printf("Department: %s\n", staffList[i].department);
        printf("\n");
    }
}
