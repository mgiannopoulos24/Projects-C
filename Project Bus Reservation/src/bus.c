#include <stdio.h>
#include "bus.h"

static Bus buses[MAX_BUSES];
static int num_buses = 0;

void init_buses() {
    // Initialize buses with dummy data or read from file
    // Example:
    buses[0].bus_id = 1;
    buses[0].num_seats = 20;
    for (int i = 0; i < buses[0].num_seats; ++i) {
        buses[0].seats_available[i] = 1; // Available
    }
    num_buses = 1;
}

void display_available_buses() {
    printf("Available Buses:\n");
    for (int i = 0; i < num_buses; ++i) {
        printf("Bus ID: %d, Seats available: %d\n", buses[i].bus_id, get_available_seat(buses[i].bus_id));
    }
}

int reserve_seat(int bus_id, int seat_number) {
    for (int i = 0; i < num_buses; ++i) {
        if (buses[i].bus_id == bus_id) {
            if (seat_number >= 0 && seat_number < buses[i].num_seats && buses[i].seats_available[seat_number]) {
                buses[i].seats_available[seat_number] = 0; // Reserve the seat
                return 1; // Successful reservation
            } else {
                return 0; // Seat not available or invalid seat number
            }
        }
    }
    return -1; // Bus ID not found
}

int get_available_seat(int bus_id) {
    for (int i = 0; i < num_buses; ++i) {
        if (buses[i].bus_id == bus_id) {
            int count = 0;
            for (int j = 0; j < buses[i].num_seats; ++j) {
                if (buses[i].seats_available[j]) {
                    count++;
                }
            }
            return count;
        }
    }
    return -1; // Bus ID not found
}
