#include "semaphores.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>

int create_semaphore(key_t key, int init_val) {
    int sem_id = semget(key, 1, IPC_CREAT | 0666);
    if (sem_id < 0) {
        perror("semget");
        exit(1);
    }
    if (semctl(sem_id, 0, SETVAL, init_val) == -1) {
        perror("semctl");
        exit(1);
    }
    return sem_id;
}

void semaphore_wait(int sem_id) {
    struct sembuf operation = {0, -1, 0};
    if (semop(sem_id, &operation, 1) == -1) {
        perror("semop wait");
        exit(1);
    }
}

void semaphore_signal(int sem_id) {
    struct sembuf operation = {0, 1, 0};
    if (semop(sem_id, &operation, 1) == -1) {
        perror("semop signal");
        exit(1);
    }
}

void destroy_semaphore(int sem_id) {
    if (semctl(sem_id, 0, IPC_RMID) == -1) {
        perror("semctl destroy");
        exit(1);
    }
}
