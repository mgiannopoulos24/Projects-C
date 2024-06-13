#ifndef BUS_H
#define BUS_H

#define MAX_BUSES 50
#define MAX_SEATS 50

typedef struct {
    int bus_id;
    int num_seats;
    int seats_available[MAX_SEATS];
} Bus;

void init_buses();
void display_available_buses();
int reserve_seat(int bus_id, int seat_number);
int get_available_seat(int bus_id);

#endif
