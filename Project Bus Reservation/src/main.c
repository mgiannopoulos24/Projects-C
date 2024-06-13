#include <stdio.h>
#include "bus.h"
#include "route.h"
#include "passenger.h"
#include "reservation.h"
#include "utils.h"

void display_menu() {
    printf("\n======= BUS RESERVATION SYSTEM =======\n");
    printf("1. Display available buses\n");
    printf("2. Display available routes\n");
    printf("3. Make a reservation\n");
    printf("4. Display all reservations\n");
    printf("5. Exit\n");
    printf("======================================\n");
    printf("Enter your choice: ");
}

int main() {
    init_buses(); // Initialize buses with dummy data

    // Dummy routes
    routes[num_routes++] = (Route){1, "City A", "City B", 1};
    routes[num_routes++] = (Route){2, "City B", "City C", 1};

    int choice;
    do {
        display_menu();
        choice = get_int_input();

        switch (choice) {
            case 1:
                display_available_buses();
                break;
            case 2:
                display_routes();
                break;
            case 3: {
                printf("Enter passenger name: ");
                char name[50];
                scanf("%s", name);
                clear_input_buffer();

                printf("Enter route ID: ");
                int route_id = get_int_input();

                printf("Enter seat number: ");
                int seat_number = get_int_input();

                make_reservation(name, route_id, seat_number);
                break;
            }
            case 4:
                display_reservations();
                break;
            case 5:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
                break;
        }
    } while (choice != 5);

    return 0;
}
