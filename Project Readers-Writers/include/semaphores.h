#ifndef SEMAPHORES_H
#define SEMAPHORES_H

#include <sys/sem.h>

// Function prototypes
int create_semaphore(key_t key, int init_val);
void semaphore_wait(int sem_id);
void semaphore_signal(int sem_id);
void destroy_semaphore(int sem_id);

#endif // SEMAPHORES_H
