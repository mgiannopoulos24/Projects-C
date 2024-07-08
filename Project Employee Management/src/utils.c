#include <stdio.h>
#include "employee.h"
#include "utils.h"

int validateId(int empId) {
    for (int i = 0; i < numEmployees; ++i) {
        if (employees[i].empId == empId) {
            return 1; // ID found
        }
    }
    return 0; // ID not found
}

void saveData() {
    FILE *fp = fopen("data.txt", "w");
    if (fp == NULL) {
        perror("Error opening file.");
        return;
    }
    
    for (int i = 0; i < numEmployees; ++i) {
        fprintf(fp, "%d,%s,%.2f\n", employees[i].empId, employees[i].name, employees[i].salary);
    }
    
    fclose(fp);
}

void loadData() {
    FILE *fp = fopen("data.txt", "r");
    if (fp == NULL) {
        perror("Error opening file.");
        return;
    }
    
    while (fscanf(fp, "%d,%[^,],%f\n", &employees[numEmployees].empId, employees[numEmployees].name, &employees[numEmployees].salary) == 3) {
        numEmployees++;
    }
    
    fclose(fp);
}
