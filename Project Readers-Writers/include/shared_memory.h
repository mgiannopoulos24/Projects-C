#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define RECORDS_COUNT 10
#define MAX_NAME_LEN 20

typedef struct {
    int id;
    char last_name[MAX_NAME_LEN];
    char first_name[MAX_NAME_LEN];
    int balance;
} Record;

typedef struct {
    Record records[RECORDS_COUNT];
    int readers_count[RECORDS_COUNT];
    int writers_count[RECORDS_COUNT];
} SharedMemory;

// Function prototypes
int create_shared_memory(key_t key, size_t size);
void *attach_shared_memory(int shm_id);
void detach_shared_memory(void *shm_addr);
void destroy_shared_memory(int shm_id);

#endif // SHARED_MEMORY_H
