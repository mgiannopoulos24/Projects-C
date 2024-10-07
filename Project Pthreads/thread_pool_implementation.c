#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREAD_POOL_SIZE 4
#define TASK_QUEUE_SIZE 8

typedef struct {
    void (*function)(void *);
    void *argument;
} Task;

Task task_queue[TASK_QUEUE_SIZE];
int queue_front = 0, queue_rear = 0, task_count = 0;
pthread_mutex_t queue_mutex;
pthread_cond_t task_available, task_taken;

void *thread_worker(void *arg) {
    while (1) {
        pthread_mutex_lock(&queue_mutex);

        while (task_count == 0) {
            pthread_cond_wait(&task_available, &queue_mutex);
        }

        Task task = task_queue[queue_front];
        queue_front = (queue_front + 1) % TASK_QUEUE_SIZE;
        task_count--;

        pthread_cond_signal(&task_taken);
        pthread_mutex_unlock(&queue_mutex);

        task.function(task.argument);
    }
    return NULL;
}

void enqueue_task(void (*function)(void *), void *arg) {
    pthread_mutex_lock(&queue_mutex);

    while (task_count == TASK_QUEUE_SIZE) {
        pthread_cond_wait(&task_taken, &queue_mutex);
    }

    task_queue[queue_rear].function = function;
    task_queue[queue_rear].argument = arg;
    queue_rear = (queue_rear + 1) % TASK_QUEUE_SIZE;
    task_count++;

    pthread_cond_signal(&task_available);
    pthread_mutex_unlock(&queue_mutex);
}

void sample_task(void *arg) {
    int id = *(int *)arg;
    printf("Task %d is being processed by thread.\n", id);
    sleep(1);  // Simulating task work
}

int main() {
    pthread_t thread_pool[THREAD_POOL_SIZE];
    pthread_mutex_init(&queue_mutex, NULL);
    pthread_cond_init(&task_available, NULL);
    pthread_cond_init(&task_taken, NULL);

    for (int i = 0; i < THREAD_POOL_SIZE; i++) {
        pthread_create(&thread_pool[i], NULL, thread_worker, NULL);
    }

    int tasks[TASK_QUEUE_SIZE];
    for (int i = 0; i < TASK_QUEUE_SIZE; i++) {
        tasks[i] = i + 1;
        enqueue_task(sample_task, &tasks[i]);
    }

    for (int i = 0; i < THREAD_POOL_SIZE; i++) {
        pthread_join(thread_pool[i], NULL);
    }

    pthread_mutex_destroy(&queue_mutex);
    pthread_cond_destroy(&task_available);
    pthread_cond_destroy(&task_taken);

    return 0;
}
