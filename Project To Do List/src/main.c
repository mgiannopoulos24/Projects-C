#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "todo_list.h"

int main() {
    int choice;
    char task[MAX_TASK_LENGTH];

    // Load tasks from file at startup
    load_tasks_from_file("tasks.txt");

    while (1) {
        printf("\n===== To-Do List Menu =====\n");
        printf("1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Remove Task\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character left in buffer

        switch (choice) {
            case 1:
                printf("Enter task to add: ");
                fgets(task, sizeof(task), stdin);
                task[strcspn(task, "\n")] = '\0'; // Remove newline character from fgets
                add_task(task);
                break;
            case 2:
                view_tasks();
                break;
            case 3:
                printf("Enter index of task to remove: ");
                scanf("%d", &choice);
                getchar(); // Consume newline character left in buffer
                remove_task(choice);
                break;
            case 4:
                printf("Saving tasks and exiting program.\n");
                save_tasks_to_file("tasks.txt");
                cleanup();
                exit(0);
            default:
                printf("Invalid choice. Please enter a number from 1 to 4.\n");
        }
    }

    return 0;
}
