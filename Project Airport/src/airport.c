#include <stdio.h>
#include "flight.h"
#include "passenger.h"
#include "staff.h"
#include "airport.h"

// Remove definitions of manageFlights, managePassengers, and manageStaff from this file
// Only call the respective functions from their files

void manageAirport() {
    int choice;

    while (1) {
        printf("Airport Management System\n");
        printf("1. Manage Flights\n");
        printf("2. Manage Passengers\n");
        printf("3. Manage Staff\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                manageFlights();
                break;
            case 2:
                managePassengers();
                break;
            case 3:
                manageStaff();
                break;
            case 4:
                printf("Exiting...\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
