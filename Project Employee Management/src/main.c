#include <stdio.h>
#include "employee.h"
#include "utils.h"

int main() {
    int choice;
    int empId;

    // Load existing data from file (if any)
    loadData();

    do {
        printf("\nEmployee Management System\n");
        printf("1. Add Employee\n");
        printf("2. Delete Employee\n");
        printf("3. Update Employee\n");
        printf("4. List Employees\n");
        printf("5. Search Employee\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee();
                saveData();
                break;
            case 2:
                printf("Enter employee ID to delete: ");
                scanf("%d", &empId);
                deleteEmployee(empId);
                saveData();
                break;
            case 3:
                printf("Enter employee ID to update: ");
                scanf("%d", &empId);
                updateEmployee(empId);
                saveData();
                break;
            case 4:
                listEmployees();
                break;
            case 5:
                printf("Enter employee ID to search: ");
                scanf("%d", &empId);
                searchEmployee(empId);
                break;
            case 6:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 6);

    return 0;
}
