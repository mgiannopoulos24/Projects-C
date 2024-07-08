#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#define MAX_NAME_LENGTH 50
#define MAX_EMPLOYEES 100

struct Employee {
    int empId;
    char name[MAX_NAME_LENGTH];
    float salary;
};

extern struct Employee employees[MAX_EMPLOYEES];
extern int numEmployees;

void initializeEmployees();
void addEmployee();
void deleteEmployee(int empId);
void updateEmployee(int empId);
void listEmployees();
void searchEmployee(int empId);

#endif
