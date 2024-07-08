#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

// Συνάρτηση για τη δημιουργία ενός νέου Task
Task* createTask(char* name, int arrival_time, int priority, int burst_time, int deadline) {
    Task* newTask = (Task*) malloc(sizeof(Task));
    if (newTask == NULL) {
        perror("Failed to allocate memory for new task");
        exit(1);
    }
    strcpy(newTask->name, name);
    newTask->arrival_time = arrival_time;
    newTask->priority = priority;
    newTask->burst_time = burst_time;
    newTask->deadline = deadline;
    newTask->next = NULL;
    return newTask;
}

// Συνάρτηση για την προσθήκη ενός Task στη λίστα
void insertTask(Task** head, Task* newTask) {
    if (*head == NULL) {
        *head = newTask;
    } else {
        Task* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newTask;
    }
}

// Συνάρτηση για την αφαίρεση ενός Task από τη λίστα
void deleteTask(Task** head, char* name) {
    Task* temp = *head;
    Task* prev = NULL;

    // Αν η κεφαλή της λίστας είναι το Task που θέλουμε να αφαιρέσουμε
    if (temp != NULL && strcmp(temp->name, name) == 0) {
        *head = temp->next; // Αλλάζουμε την κεφαλή
        free(temp);         // Απελευθερώνουμε τη μνήμη
        return;
    }

    // Ψάχνουμε το Task που θέλουμε να αφαιρέσουμε, διατηρώντας τον προηγούμενο κόμβο
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }

    // Αν δεν βρήκαμε το Task με το δοσμένο όνομα
    if (temp == NULL) return;

    // Αφαιρούμε το Task από τη λίστα
    prev->next = temp->next;

    free(temp); // Απελευθερώνουμε τη μνήμη
}

// Συνάρτηση για την εκτύπωση της λίστας των Task (για debugging)
void printTaskList(Task* head) {
    Task* temp = head;
    while (temp != NULL) {
        printf("Task: %s, Arrival Time: %d, Priority: %d, Burst Time: %d, Period: %d\n",
               temp->name, temp->arrival_time, temp->priority, temp->burst_time, temp->deadline);
        temp = temp->next;
    }
}
