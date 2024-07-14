#ifndef STUDENT_H
#define STUDENT_H

#define MAX_STUDENTS 100

// Define a structure for student details
struct Student {
    int rollNumber;
    char firstName[50];
    char lastName[50];
    char course[100];
    int age;
};


// Function prototypes for student operations
void addStudent(struct Student students[], int *count);
void findStudentByRollNumber(struct Student students[], int count, int rollNumber);
void findStudentByFirstName(struct Student students[], int count, const char *firstName);
void findStudentsByCourse(struct Student students[], int count, const char *course);
void displayStudentCount(int count);
void deleteStudent(struct Student students[], int *count, int rollNumber);
void updateStudent(struct Student students[], int count, int rollNumber);


#endif // STUDENT_H