#include "shared_memory.h"
#include "semaphores.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>

// Function to update a specific record in the binary file
void update_record(FILE *file, int recid, int value) {
    Record record;
    fseek(file, (recid - 1) * sizeof(Record), SEEK_SET);  // Move to the correct record
    if (fread(&record, sizeof(Record), 1, file)) {
        printf("Updating record %d\n", recid);
        printf("Original Balance: %d\n", record.balance);

        // Modify the balance
        record.balance += value;
        
        // Move back to the record position to update it
        fseek(file, (recid - 1) * sizeof(Record), SEEK_SET);
        fwrite(&record, sizeof(Record), 1, file);

        printf("Updated Balance: %d\n", record.balance);
        printf("----------------------\n");
    } else {
        printf("Error reading record ID %d\n", recid);
    }
}

int main(int argc, char *argv[]) {
    int opt;
    char *filename = NULL;
    int recid = -1;
    int value = 0;
    int duration = -1;
    int shmid = -1; // Shared memory ID for synchronization

    // Parse command-line options using getopt
    while ((opt = getopt(argc, argv, "f:l:v:d:s:")) != -1) {
        switch (opt) {
            case 'f':
                filename = optarg;  // Get the filename
                break;
            case 'l':
                recid = atoi(optarg);  // Get the record ID
                break;
            case 'v':
                value = atoi(optarg);  // Get the value to modify the balance
                break;
            case 'd':
                duration = atoi(optarg);  // Get the sleep duration
                break;
            case 's':
                shmid = atoi(optarg);  // Get the shared memory ID (for synchronization)
                break;
            default:
                fprintf(stderr, "Usage: %s -f filename -l recid -v value -d time -s shmid\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // Ensure all required arguments are provided
    if (filename == NULL || recid == -1 || duration == -1 || shmid == -1) {
        fprintf(stderr, "Usage: %s -f filename -l recid -v value -d time -s shmid\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open the binary file
    FILE *file = fopen(filename, "r+b");  // Open for both reading and writing
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Access shared memory (for synchronization purposes)
    int shm_id = create_shared_memory(shmid, sizeof(SharedMemory));
    SharedMemory *shm_ptr = (SharedMemory *)attach_shared_memory(shm_id);

    // Semaphore for synchronization of the specific record
    int sem_id = create_semaphore(shmid + recid, 1); // One semaphore per record

    // Enter critical section (start writing)
    semaphore_wait(sem_id);
    shm_ptr->writers_count[recid]++;
    
    printf("Writing to record %d\n", recid);
    update_record(file, recid, value);  // Update the record in the file

    sleep(duration);  // Simulate processing time

    // Leave critical section
    shm_ptr->writers_count[recid]--;
    semaphore_signal(sem_id);

    printf("Finished writing to record %d\n", recid);

    // Cleanup
    detach_shared_memory(shm_ptr);
    destroy_semaphore(sem_id);
    fclose(file);  // Close the file

    return 0;
}
