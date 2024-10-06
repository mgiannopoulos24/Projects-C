#include "shared_memory.h"
#include "semaphores.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>

// Function to split record IDs (e.g., "1,2,3") into an array
int parse_record_ids(char *arg, int *records) {
    int count = 0;
    char *token = strtok(arg, ",");
    while (token != NULL && count < 100) {
        records[count++] = atoi(token);
        token = strtok(NULL, ",");
    }
    return count;
}

// Function to read and display a specific record from the binary file
void read_record(FILE *file, int recid) {
    Record record;
    fseek(file, (recid - 1) * sizeof(Record), SEEK_SET); // Move file pointer to the specific record
    if (fread(&record, sizeof(Record), 1, file)) {
        printf("----------------------\n");
        printf("ID: %d\n", record.id);
        printf("Last Name: %s\n", record.last_name);
        printf("First Name: %s\n", record.first_name);
        printf("Balance: %d\n", record.balance);
        printf("----------------------\n");
    } else {
        printf("Error reading record ID %d\n", recid);
    }
}

int main(int argc, char *argv[]) {
    int opt;
    char *filename = NULL;
    char *recid_str = NULL;
    int duration = -1;
    int shmid = -1; // Shared memory ID for synchronization
    int records[100];  // Array to hold record IDs
    int num_records = 0;

    // Parse command-line options using getopt
    while ((opt = getopt(argc, argv, "f:l:d:s:")) != -1) {
        switch (opt) {
            case 'f':
                filename = optarg;  // Get the filename
                break;
            case 'l':
                recid_str = optarg;  // Get the record IDs (comma-separated)
                break;
            case 'd':
                duration = atoi(optarg);  // Get the sleep duration
                break;
            case 's':
                shmid = atoi(optarg);  // Get the shared memory ID (for synchronization)
                break;
            default:
                fprintf(stderr, "Usage: %s -f filename -l recid[,recid] -d time -s shmid\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // Ensure all required arguments are provided
    if (filename == NULL || recid_str == NULL || duration == -1 || shmid == -1) {
        fprintf(stderr, "Usage: %s -f filename -l recid[,recid] -d time -s shmid\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Parse record IDs
    num_records = parse_record_ids(recid_str, records);
    if (num_records == 0) {
        fprintf(stderr, "Error: Invalid record IDs\n");
        exit(EXIT_FAILURE);
    }

    // Open the binary file
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Access shared memory (for synchronization purposes)
    int shm_id = create_shared_memory(shmid, sizeof(SharedMemory));
    SharedMemory *shm_ptr = (SharedMemory *)attach_shared_memory(shm_id);

    // Loop through each record and read it from the binary file
    for (int i = 0; i < num_records; i++) {
        int recid = records[i];

        // Semaphore for synchronization of the specific record
        int sem_id = create_semaphore(shmid + recid, 1); // One semaphore per record

        // Enter critical section (start reading)
        semaphore_wait(sem_id);
        shm_ptr->readers_count[recid]++;
        
        printf("Reading record %d\n", recid);
        read_record(file, recid);  // Read and print the specific record

        sleep(duration);  // Simulate processing time

        // Leave critical section
        shm_ptr->readers_count[recid]--;
        semaphore_signal(sem_id);

        printf("Finished reading record %d\n", recid);

        // Cleanup semaphore for the current record
        destroy_semaphore(sem_id);
    }

    // Cleanup shared memory
    detach_shared_memory(shm_ptr);

    fclose(file);  // Close the file
    return 0;
}
