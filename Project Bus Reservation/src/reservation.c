#include "reservation.h"
#include "passenger.h"
#include "route.h"
#include "bus.h"
#include <stdio.h>

void make_reservation(char *passenger_name, int route_id, int seat_number) {
    Route *route = find_route(route_id);
    if (route == NULL) {
        printf("Route not found. Reservation failed.\n");
        return;
    }

    int bus_id = route->bus_id;
    int result = reserve_seat(bus_id, seat_number);
    if (result == 1) {
        add_passenger(passenger_name, route_id, seat_number);
        printf("Reservation successful!\n");
    } else if (result == 0) {
        printf("Seat already reserved or invalid seat number. Reservation failed.\n");
    } else {
        printf("Bus not found. Reservation failed.\n");
    }
}

void display_reservations() {
    display_passengers();
}
