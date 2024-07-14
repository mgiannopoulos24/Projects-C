#include <stdio.h>
#include "file_handling.h"

// Function to save students to file
void saveStudentsToFile(struct Student students[], int count) {
    FILE *fp;
    fp = fopen("students.txt", "w");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d %s %s %s %d\n", students[i].rollNumber, students[i].firstName, students[i].lastName, students[i].course, students[i].age);
    }

    fclose(fp);
    printf("Student data saved to file.\n");
}

// Function to load students from file
int loadStudentsFromFile(struct Student students[]) {
    FILE *fp;
    fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("Error opening file for reading.\n");
        return 0;
    }

    int count = 0;
    while (fscanf(fp, "%d %s %s %s %d\n", &students[count].rollNumber, students[count].firstName, students[count].lastName, students[count].course, &students[count].age) != EOF) {
        count++;
    }

    fclose(fp);
    printf("Student data loaded from file.\n");
    return count;
}
