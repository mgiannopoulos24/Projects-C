#include <stdio.h>
#include <string.h>
#include "flight.h"

#define MAX_FLIGHTS 100

typedef struct {
    int flightNumber;
    char origin[30];
    char destination[30];
    char departureTime[10];
    char arrivalTime[10];
} Flight;

Flight flights[MAX_FLIGHTS];
int flightCount = 0;

void manageFlights() {
    int choice;

    while (1) {
        printf("\nFlight Management\n");
        printf("1. Add Flight\n");
        printf("2. Remove Flight\n");
        printf("3. List Flights\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addFlight();
                break;
            case 2:
                removeFlight();
                break;
            case 3:
                listFlights();
                break;
            case 4:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void addFlight() {
    if (flightCount >= MAX_FLIGHTS) {
        printf("Cannot add more flights. Maximum limit reached.\n");
        return;
    }

    Flight newFlight;
    printf("Enter flight number: ");
    scanf("%d", &newFlight.flightNumber);
    printf("Enter origin: ");
    scanf("%s", newFlight.origin);
    printf("Enter destination: ");
    scanf("%s", newFlight.destination);
    printf("Enter departure time: ");
    scanf("%s", newFlight.departureTime);
    printf("Enter arrival time: ");
    scanf("%s", newFlight.arrivalTime);

    flights[flightCount++] = newFlight;
    printf("Flight added successfully.\n");
}

void removeFlight() {
    int flightNumber;
    printf("Enter flight number to remove: ");
    scanf("%d", &flightNumber);

    int found = 0;
    for (int i = 0; i < flightCount; i++) {
        if (flights[i].flightNumber == flightNumber) {
            for (int j = i; j < flightCount - 1; j++) {
                flights[j] = flights[j + 1];
            }
            flightCount--;
            found = 1;
            printf("Flight removed successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Flight not found.\n");
    }
}

void listFlights() {
    if (flightCount == 0) {
        printf("No flights available.\n");
        return;
    }

    printf("\nList of Flights:\n");
    for (int i = 0; i < flightCount; i++) {
        printf("Flight Number: %d\n", flights[i].flightNumber);
        printf("Origin: %s\n", flights[i].origin);
        printf("Destination: %s\n", flights[i].destination);
        printf("Departure Time: %s\n", flights[i].departureTime);
        printf("Arrival Time: %s\n", flights[i].arrivalTime);
        printf("\n");
    }
}
