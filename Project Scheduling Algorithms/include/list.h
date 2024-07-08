#ifndef LIST_H
#define LIST_H

// Δομή Task για την αποθήκευση των πληροφοριών της διεργασίας
typedef struct Task {
    char name[50];
    int arrival_time;
    int priority;
    int burst_time;
    int deadline;         
    struct Task *next;
} Task;

// Συνάρτηση για τη δημιουργία ενός νέου Task
Task* createTask(char* name, int arrival_time, int priority, int burst_time, int period);

// Συνάρτηση για την προσθήκη ενός Task στη λίστα
void insertTask(Task** head, Task* newTask);

// Συνάρτηση για την αφαίρεση ενός Task από τη λίστα
void deleteTask(Task** head, char* name);

// Συνάρτηση για την εκτύπωση της λίστας των Task (για debugging)
void printTaskList(Task* head);

#endif // LIST_H
