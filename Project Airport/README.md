# Airport Management System
The Airport Management System is a command-line application designed to manage flights, passengers, and staff within an airport setting. This project demonstrates basic functionalities for managing flights, passengers, and staff members, providing a simple interface for adding, removing, and listing these entities.

## Features
1. Flight Management:
- Add new flights with details such as flight number, origin, destination, departure time, and arrival time.
- Remove existing flights by specifying the flight number.
- List all flights currently managed by the system.
2. Passenger Management:
- Add new passengers with details including passenger ID, name, passport number, nationality, and associated flight number.
- Remove existing passengers by specifying the passenger ID.
- List all passengers currently registered in the system.
3. Staff Management:
- Add new staff members with details such as staff ID, name, position, and department.
- Remove existing staff members by specifying the staff ID.
- List all staff members currently employed at the airport.
4. Main Menu:
- Provides a user-friendly interface to navigate between flight management, passenger management, staff management, and exit options.

## Compilation 

To compile the program use `make` or `make all` and to remove it use `make clean`.

## Example execution

Once you run the program, you will see the main menu:
```bash
Airport Management System
1. Manage Flights
2. Manage Passengers
3. Manage Staff
4. Exit
Enter your choice:
```

## Operations
1. Manage Flights:
- Add a Flight:
```bash
Enter your choice: 1

Flight Management
1. Add Flight
2. Remove Flight
3. List Flights
4. Back to Main Menu
Enter your choice: 1

Enter flight number: 123
Enter origin: JFK
Enter destination: LAX
Enter departure time: 09:00
Enter arrival time: 12:00
Flight added successfully.
```
- List Flights:
```bash
Flight Management
1. Add Flight
2. Remove Flight
3. List Flights
4. Back to Main Menu
Enter your choice: 3

List of Flights:
Flight Number: 123
Origin: JFK
Destination: LAX
Departure Time: 09:00
Arrival Time: 12:00
```
- Remove a Flight:
```bash
Flight Management
1. Add Flight
2. Remove Flight
3. List Flights
4. Back to Main Menu
Enter your choice: 2

Enter flight number to remove: 123
Flight removed successfully.
```
2. Manage Passengers:
- Add a Passenger:
```bash
Enter your choice: 2

Passenger Management
1. Add Passenger
2. Remove Passenger
3. List Passengers
4. Back to Main Menu
Enter your choice: 1

Enter passenger ID: 1
Enter name: JohnDoe
Enter passport number: A1234567
Enter nationality: USA
Enter flight number: 123
Passenger added successfully.
```
- List Passengers:
```bash
Passenger Management
1. Add Passenger
2. Remove Passenger
3. List Passengers
4. Back to Main Menu
Enter your choice: 3

List of Passengers:
Passenger ID: 1
Name: JohnDoe
Passport Number: A1234567
Nationality: USA
Flight Number: 123
```
- Remove a Passenger:
```bash
Passenger Management
1. Add Passenger
2. Remove Passenger
3. List Passengers
4. Back to Main Menu
Enter your choice: 2

Enter passenger ID to remove: 1
Passenger removed successfully.
```
3. Manage Staff
- Add a Staff Member:
```bash
Enter your choice: 3

Staff Management
1. Add Staff
2. Remove Staff
3. List Staff
4. Back to Main Menu
Enter your choice: 1

Enter staff ID: 101
Enter name: JaneDoe
Enter position: Pilot
Enter department: Operations
Staff member added successfully.
```
- List Staff:
```bash
Staff Management
1. Add Staff
2. Remove Staff
3. List Staff
4. Back to Main Menu
Enter your choice: 3

List of Staff Members:
Staff ID: 101
Name: JaneDoe
Position: Pilot
Department: Operations
```
- Remove a Staff Member:
```bash
Staff Management
1. Add Staff
2. Remove Staff
3. List Staff
4. Back to Main Menu
Enter your choice: 2

Enter staff ID to remove: 101
Staff member removed successfully.
```
4. Exit
```bash
Enter your choice: 4
Exiting...
```