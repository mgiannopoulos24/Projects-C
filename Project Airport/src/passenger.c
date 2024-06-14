#include <stdio.h>
#include <string.h>
#include "passenger.h"

#define MAX_PASSENGERS 100

typedef struct {
    int passengerID;
    char name[50];
    char passportNumber[20];
    char nationality[30];
    char flightNumber[10];
} Passenger;

Passenger passengers[MAX_PASSENGERS];
int passengerCount = 0;

void managePassengers() {
    int choice;

    while (1) {
        printf("\nPassenger Management\n");
        printf("1. Add Passenger\n");
        printf("2. Remove Passenger\n");
        printf("3. List Passengers\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addPassenger();
                break;
            case 2:
                removePassenger();
                break;
            case 3:
                listPassengers();
                break;
            case 4:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void addPassenger() {
    if (passengerCount >= MAX_PASSENGERS) {
        printf("Cannot add more passengers. Maximum limit reached.\n");
        return;
    }

    Passenger newPassenger;
    printf("Enter passenger ID: ");
    scanf("%d", &newPassenger.passengerID);
    printf("Enter name: ");
    scanf("%s", newPassenger.name);
    printf("Enter passport number: ");
    scanf("%s", newPassenger.passportNumber);
    printf("Enter nationality: ");
    scanf("%s", newPassenger.nationality);
    printf("Enter flight number: ");
    scanf("%s", newPassenger.flightNumber);

    passengers[passengerCount++] = newPassenger;
    printf("Passenger added successfully.\n");
}

void removePassenger() {
    int passengerID;
    printf("Enter passenger ID to remove: ");
    scanf("%d", &passengerID);

    int found = 0;
    for (int i = 0; i < passengerCount; i++) {
        if (passengers[i].passengerID == passengerID) {
            for (int j = i; j < passengerCount - 1; j++) {
                passengers[j] = passengers[j + 1];
            }
            passengerCount--;
            found = 1;
            printf("Passenger removed successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Passenger not found.\n");
    }
}

void listPassengers() {
    if (passengerCount == 0) {
        printf("No passengers available.\n");
        return;
    }

    printf("\nList of Passengers:\n");
    for (int i = 0; i < passengerCount; i++) {
        printf("Passenger ID: %d\n", passengers[i].passengerID);
        printf("Name: %s\n", passengers[i].name);
        printf("Passport Number: %s\n", passengers[i].passportNumber);
        printf("Nationality: %s\n", passengers[i].nationality);
        printf("Flight Number: %s\n", passengers[i].flightNumber);
        printf("\n");
    }
}
