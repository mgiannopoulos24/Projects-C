#include <stdio.h>
#include <string.h>
#include "employee.h"
#include "utils.h"

struct Employee employees[MAX_EMPLOYEES];
int numEmployees = 0;

void initializeEmployees() {
    // Load employees from data.txt or initialize as needed
}

void addEmployee() {
    if (numEmployees >= MAX_EMPLOYEES) {
        printf("Maximum number of employees reached.\n");
        return;
    }
    
    struct Employee newEmployee;
    printf("Enter employee ID: ");
    scanf("%d", &newEmployee.empId);
    printf("Enter employee name: ");
    scanf(" %[^\n]", newEmployee.name);
    printf("Enter employee salary: ");
    scanf("%f", &newEmployee.salary);
    
    employees[numEmployees++] = newEmployee;
    printf("Employee added successfully.\n");
}

void deleteEmployee(int empId) {
    int found = 0;
    for (int i = 0; i < numEmployees; ++i) {
        if (employees[i].empId == empId) {
            found = 1;
            for (int j = i; j < numEmployees - 1; ++j) {
                employees[j] = employees[j + 1];
            }
            numEmployees--;
            printf("Employee deleted successfully.\n");
            break;
        }
    }
    if (!found) {
        printf("Employee not found.\n");
    }
}

void updateEmployee(int empId) {
    int found = 0;
    for (int i = 0; i < numEmployees; ++i) {
        if (employees[i].empId == empId) {
            found = 1;
            printf("Enter new employee name: ");
            scanf(" %[^\n]", employees[i].name);
            printf("Enter new employee salary: ");
            scanf("%f", &employees[i].salary);
            printf("Employee updated successfully.\n");
            break;
        }
    }
    if (!found) {
        printf("Employee not found.\n");
    }
}

void listEmployees() {
    if (numEmployees == 0) {
        printf("No employees to display.\n");
    } else {
        printf("Employee ID\tName\t\t\t\tSalary\n");
        for (int i = 0; i < numEmployees; ++i) {
            printf("%d\t\t%s\t\t\t%.2f\n", employees[i].empId, employees[i].name, employees[i].salary);
        }
    }
}

void searchEmployee(int empId) {
    int found = 0;
    for (int i = 0; i < numEmployees; ++i) {
        if (employees[i].empId == empId) {
            found = 1;
            printf("Employee found:\n");
            printf("Employee ID: %d\n", employees[i].empId);
            printf("Name: %s\n", employees[i].name);
            printf("Salary: %.2f\n", employees[i].salary);
            break;
        }
    }
    if (!found) {
        printf("Employee not found.\n");
    }
}
