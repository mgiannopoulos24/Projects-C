#ifndef TODO_LIST_H
#define TODO_LIST_H

#define MAX_TASK_LENGTH 100

typedef struct {
    char description[MAX_TASK_LENGTH];
} Task;

void add_task(const char *description);
void view_tasks();
void remove_task(int index);
void cleanup();
void load_tasks_from_file(const char *filename);
void save_tasks_to_file(const char *filename);

#endif // TODO_LIST_H
