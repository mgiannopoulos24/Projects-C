#include "shared_memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>

int create_shared_memory(key_t key, size_t size) {
    int shm_id = shmget(key, size, IPC_CREAT | 0666);
    if (shm_id < 0) {
        perror("shmget");
        exit(1);
    }
    return shm_id;
}

void *attach_shared_memory(int shm_id) {
    void *shm_addr = shmat(shm_id, NULL, 0);
    if (shm_addr == (void *) -1) {
        perror("shmat");
        exit(1);
    }
    return shm_addr;
}

void detach_shared_memory(void *shm_addr) {
    if (shmdt(shm_addr) == -1) {
        perror("shmdt");
        exit(1);
    }
}

void destroy_shared_memory(int shm_id) {
    if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }
}
