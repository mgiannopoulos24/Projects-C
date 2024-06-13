# Bus Reservation System

The Bus Reservation System is a command-line application implemented in C that allows users to manage bus routes, buses, passengers, and reservations. It provides basic functionalities such as displaying available buses and routes, making reservations, and viewing all reservations made.

## Features

- Display available buses with their seating capacities.
- Display available routes between cities.
- Allow passengers to make reservations for a specific route and seat number.
- Display all reservations made by passengers.

## Usage
1. Compilation: To compile the program use `make` or `make all` and to remove it use `make clean`.
2. Execution: `./bus_reservation_system`

Upon running the program, you will see a menu with options to interact with the system:

```bash
======= BUS RESERVATION SYSTEM =======
1. Display available buses
2. Display available routes
3. Make a reservation
4. Display all reservations
5. Exit
======================================
Enter your choice:
```

- Option 1: Displays a list of available buses with their seating capacities.
- Option 2: Displays a list of available routes between cities.
- Option 3: Allows you to make a reservation by entering the passenger name, route ID, and seat number.
- Option 4: Displays all reservations made by passengers.
- Option 5: Exits the program.


## Example

```bash
======= BUS RESERVATION SYSTEM =======
1. Display available buses
2. Display available routes
3. Make a reservation
4. Display all reservations
5. Exit
======================================
Enter your choice: 1
Available Buses:
Bus ID: 1, Seats available: 20

======= BUS RESERVATION SYSTEM =======
1. Display available buses
2. Display available routes
3. Make a reservation
4. Display all reservations
5. Exit
======================================
Enter your choice: 2
Available Routes:
Route ID: 1, Source: City A, Destination: City B
Route ID: 2, Source: City B, Destination: City C

======= BUS RESERVATION SYSTEM =======
1. Display available buses
2. Display available routes
3. Make a reservation
4. Display all reservations
5. Exit
======================================
Enter your choice: 3
Enter passenger name: John Doe
Enter route ID: 1
Enter seat number: 5
Reservation successful!

======= BUS RESERVATION SYSTEM =======
1. Display available buses
2. Display available routes
3. Make a reservation
4. Display all reservations
5. Exit
======================================
Enter your choice: 4
Passengers:
Passenger ID: 1, Name: John, Route ID: 1, Seat Number: 5

======= BUS RESERVATION SYSTEM =======
1. Display available buses
2. Display available routes
3. Make a reservation
4. Display all reservations
5. Exit
======================================
Enter your choice: 5
Exiting program.
```