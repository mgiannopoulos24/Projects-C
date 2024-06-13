#ifndef PASSENGER_H
#define PASSENGER_H

#define MAX_PASSENGERS 100

typedef struct {
    int passenger_id;
    char name[50];
    int route_id;
    int seat_number;
    // Add more fields as needed
} Passenger;

void add_passenger(char *name, int route_id, int seat_number);
void display_passengers();
Passenger* find_passenger(int passenger_id);

#endif
