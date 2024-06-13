#include "passenger.h"
#include <stdio.h>
#include <string.h>

static Passenger passengers[MAX_PASSENGERS];
static int num_passengers = 0;

void add_passenger(char *name, int route_id, int seat_number) {
    if (num_passengers < MAX_PASSENGERS) {
        passengers[num_passengers].passenger_id = num_passengers + 1; // Assuming passenger_id starts from 1
        strcpy(passengers[num_passengers].name, name);
        passengers[num_passengers].route_id = route_id;
        passengers[num_passengers].seat_number = seat_number;
        num_passengers++;
    } else {
        printf("Cannot add more passengers. Limit exceeded.\n");
    }
}

void display_passengers() {
    printf("Passengers:\n");
    for (int i = 0; i < num_passengers; ++i) {
        printf("Passenger ID: %d, Name: %s, Route ID: %d, Seat Number: %d\n",
               passengers[i].passenger_id, passengers[i].name, passengers[i].route_id, passengers[i].seat_number);
    }
}

Passenger* find_passenger(int passenger_id) {
    for (int i = 0; i < num_passengers; ++i) {
        if (passengers[i].passenger_id == passenger_id) {
            return &passengers[i];
        }
    }
    return NULL; // Passenger ID not found
}
