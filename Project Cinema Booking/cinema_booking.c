#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "constants.h"
#include <semaphore.h>

// Define a structure to represent a zone in the theater
typedef struct {
    int start_row;
    int end_row;
    int cost;
} Zone;

// Define a structure to represent the theater
typedef struct {
    int rows;
    int seats_per_row;
    int **seats;
} Theater;

// Global variables
int M; // Number of cashiers
int N; // Number of customers
Zone zoneA;
Zone zoneB;
Theater theater;
pthread_mutex_t theater_lock;   // Mutex for theater seating plan
pthread_mutex_t stats_lock;     // Mutex for statistics
sem_t cashiers;                 // Semaphore to limit number of concurrent cashiers  

int total_revenue = 0;
int successful_transactions = 0;
double total_service_time = 0;
double total_waiting_time = 0;

// Function to serve a customer
void* serve_customer(void* arg) {
    int customer_id = *((int *)arg); // Get customer ID
    free(arg); // Free the allocated memory for customer ID
    struct timespec start, end, waiting_start, waiting_end;

    // Record the waiting start time
    clock_gettime(CLOCK_REALTIME, &waiting_start);

    // Wait for an available cashier
    sem_wait(&cashiers);

    // Record the waiting end time
    clock_gettime(CLOCK_REALTIME, &waiting_end);
    double waiting_time = (waiting_end.tv_sec - waiting_start.tv_sec) + 
                          (waiting_end.tv_nsec - waiting_start.tv_nsec) / 1e9;

    // Record the service start time
    clock_gettime(CLOCK_REALTIME, &start);

    // Select a zone based on probability P_a
    Zone selected_zone;
    if (rand() % 100 < P_a) {
        selected_zone = zoneA;
    } else {
        selected_zone = zoneB;
    }

    // Select a random number of tickets between N_low and N_high
    int tickets = (rand() % (N_high - N_low + 1)) + N_low;
    // Select a random serve time between t_low and t_high seconds
    int serve_time = (rand() % (t_high - t_low + 1)) + t_low;

    // Simulate processing time
    sleep(serve_time);  

    // Lock the theater seating plan
    pthread_mutex_lock(&theater_lock);

    int found = 0;
    int row = -1;
    int start_seat = -1;

    // Search for consecutive available seats in the selected zone
    for (int i = selected_zone.start_row; i <= selected_zone.end_row; i++) {
        for (int j = 0; j <= theater.seats_per_row - tickets; j++) {
            int available = 1;
            for (int k = 0; k < tickets; k++) {
                if (theater.seats[i][j + k] != 0) {
                    available = 0;
                    break;
                }
            }
            if (available) {
                found = 1;
                row = i;
                start_seat = j;
                for (int k = 0; k < tickets; k++) {
                    theater.seats[i][j + k] = customer_id;
                }
                break;
            }
        }
        if (found) break;
    }

    // Unlock the theater seating plan
    pthread_mutex_unlock(&theater_lock);
    
    // Record the service end time
    clock_gettime(CLOCK_REALTIME, &end);
    double service_time = (end.tv_sec - start.tv_sec) + 
                          (end.tv_nsec - start.tv_nsec) / 1e9;

    // Lock the statistics mutex
    pthread_mutex_lock(&stats_lock);
    total_waiting_time += waiting_time;
    total_service_time += service_time;

    if (found) {
        // Calculate the cost of the tickets
        int cost = tickets * selected_zone.cost;
        total_revenue += cost;
        successful_transactions++;
        // Unlock the statistics mutex
        pthread_mutex_unlock(&stats_lock);

        // Print the success message
        printf("Booking completed successfully. Your seats are in zone %s, row %d, from seat %d to %d and the transaction cost is %d euros.\n",
               (selected_zone.start_row == zoneA.start_row) ? "A" : "B", row + 1, start_seat + 1, start_seat + tickets, cost);
    } else {
        // Unlock the statistics mutex
        pthread_mutex_unlock(&stats_lock);
        // Print the failure message
        printf("Booking failed because there are no suitable seats available.\n");
    }

    // Release the cashier
    sem_post(&cashiers);

    pthread_exit(NULL);
}

// Function to print the seat plan
void print_seat_plan() {
    printf("\nSeat Plan:\n");
    for (int i = 0; i < theater.rows; i++) {
        for (int j = 0; j < theater.seats_per_row; j++) {
            if (theater.seats[i][j] != 0) {
                printf("Zone %s / Row %d / Seat %d / Customer %d\n", 
                       (i < zoneB.start_row) ? "A" : "B", i + 1, j + 1, theater.seats[i][j]);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    // Check for correct number of arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number_of_cashiers> <number_of_customers>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    M = atoi(argv[1]); // Number of cashiers
    N = atoi(argv[2]); // Number of customers

    srand(time(NULL)); // Seed the random number generator

    // Initialize zones
    zoneA.start_row = 0;
    zoneA.end_row = N_zoneA - 1;
    zoneA.cost = C_zoneA;

    zoneB.start_row = N_zoneA;
    zoneB.end_row = N_zoneA + N_zoneB - 1;
    zoneB.cost = C_zoneB;

    // Initialize theater
    theater.rows = N_zoneA + N_zoneB;
    theater.seats_per_row = N_seat;
    theater.seats = malloc(theater.rows * sizeof(int *));
    for (int i = 0; i < theater.rows; i++) {
        theater.seats[i] = calloc(theater.seats_per_row, sizeof(int));
    }

    // Initialize mutexes and semaphore
    pthread_mutex_init(&theater_lock, NULL);
    pthread_mutex_init(&stats_lock, NULL);
    sem_init(&cashiers, 0, M);

    pthread_t customers[N]; // Array of customer threads
    for (int i = 0; i < N; i++) {
        int *customer_id = malloc(sizeof(int));
        *customer_id = i + 1;
        usleep((rand() % 5 + 1) * 1000); // Random delay between customers
        pthread_create(&customers[i], NULL, serve_customer, customer_id);
    }

    // Wait for all customer threads to complete
    for (int i = 0; i < N; i++) {
        pthread_join(customers[i], NULL);
    }

    // Print the final seat plan
    print_seat_plan();

    // Print the final statistics
    printf("Total revenue: %d euros\n", total_revenue);
    printf("Percentage of successful transactions: %.2f%%\n", (successful_transactions / (double)N) * 100);
    printf("Average service time: %.2f seconds\n", total_service_time / N);
    printf("Average waiting time: %.2f seconds\n", total_waiting_time / N);

    // Clean up
    for (int i = 0; i < theater.rows; i++) {
        free(theater.seats[i]);
    }
    free(theater.seats);

    pthread_mutex_destroy(&theater_lock);
    pthread_mutex_destroy(&stats_lock);
    sem_destroy(&cashiers);

    return 0;
}
