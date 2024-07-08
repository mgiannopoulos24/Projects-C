# Cinema Booking System

This program simulates a cinema booking system using C language. It utilizes threads to represent customers and cashiers, mutexes and semaphores for synchronization, and randomization for selecting zones and processing delays.

## Features
- The cinema has a seating plan divided into two zones:
    - Zone A (front rows) costs 30 euros per seat.
    - Zone B (back rows) costs 20 euros per seat.
- Multiple cashiers can serve customers concurrently, with a limit of M cashiers.
- Customers arrive with a random delay between 1 to 5 milliseconds.
- Each customer selects a zone and the number of tickets randomly.
- If consecutive seats are available, the booking is successful, otherwise it fails.
- Total revenue is tracked and displayed at the end.

## Compilation and Execution

1. Compile the program:
```bash
gcc -pthread cinema_booking.c -o cinema_booking
```
2. Run the program:
```bash
./cinema_booking <number_of_cashiers> <number_of_customers>
```

For example:
```bash
./cinema_booking 3 20
```
### Example Output

- With 100% success rate:
```bash
User@Github:~$ ./cinema_booking 3 20
Booking completed successfully. Your seats are in zone B, row 11, from seat 1 to 2 and the transaction cost is 40 euros.
Booking completed successfully. Your seats are in zone B, row 11, from seat 3 to 3 and the transaction cost is 20 euros.
Booking completed successfully. Your seats are in zone B, row 11, from seat 4 to 4 and the transaction cost is 20 euros.
Booking completed successfully. Your seats are in zone B, row 11, from seat 5 to 8 and the transaction cost is 80 euros.
Booking completed successfully. Your seats are in zone A, row 1, from seat 1 to 3 and the transaction cost is 90 euros.
Booking completed successfully. Your seats are in zone B, row 12, from seat 1 to 5 and the transaction cost is 100 euros.
Booking completed successfully. Your seats are in zone B, row 12, from seat 6 to 8 and the transaction cost is 60 euros.
Booking completed successfully. Your seats are in zone B, row 13, from seat 1 to 3 and the transaction cost is 60 euros.
Booking completed successfully. Your seats are in zone B, row 13, from seat 4 to 8 and the transaction cost is 100 euros.
Booking completed successfully. Your seats are in zone A, row 1, from seat 4 to 4 and the transaction cost is 30 euros.
Booking completed successfully. Your seats are in zone A, row 1, from seat 5 to 9 and the transaction cost is 150 euros.
Booking completed successfully. Your seats are in zone B, row 14, from seat 1 to 5 and the transaction cost is 100 euros.
Booking completed successfully. Your seats are in zone B, row 14, from seat 6 to 9 and the transaction cost is 80 euros.
Booking completed successfully. Your seats are in zone B, row 15, from seat 1 to 4 and the transaction cost is 80 euros.
Booking completed successfully. Your seats are in zone B, row 15, from seat 5 to 9 and the transaction cost is 100 euros.
Booking completed successfully. Your seats are in zone A, row 2, from seat 1 to 4 and the transaction cost is 120 euros.
Booking completed successfully. Your seats are in zone B, row 16, from seat 1 to 3 and the transaction cost is 60 euros.
Booking completed successfully. Your seats are in zone A, row 2, from seat 5 to 7 and the transaction cost is 90 euros.
Booking completed successfully. Your seats are in zone B, row 11, from seat 9 to 10 and the transaction cost is 40 euros.
Booking completed successfully. Your seats are in zone B, row 16, from seat 4 to 6 and the transaction cost is 60 euros.

Seat Plan:
Zone A / Row 1 / Seat 1 / Customer 1
Zone A / Row 1 / Seat 2 / Customer 1
Zone A / Row 1 / Seat 3 / Customer 1
Zone A / Row 1 / Seat 4 / Customer 9
Zone A / Row 1 / Seat 5 / Customer 12
Zone A / Row 1 / Seat 6 / Customer 12
Zone A / Row 1 / Seat 7 / Customer 12
Zone A / Row 1 / Seat 8 / Customer 12
Zone A / Row 1 / Seat 9 / Customer 12
Zone A / Row 2 / Seat 1 / Customer 15
Zone A / Row 2 / Seat 2 / Customer 15
Zone A / Row 2 / Seat 3 / Customer 15
Zone A / Row 2 / Seat 4 / Customer 15
Zone A / Row 2 / Seat 5 / Customer 19
Zone A / Row 2 / Seat 6 / Customer 19
Zone A / Row 2 / Seat 7 / Customer 19
Zone B / Row 11 / Seat 1 / Customer 2
Zone B / Row 11 / Seat 2 / Customer 2
Zone B / Row 11 / Seat 3 / Customer 4
Zone B / Row 11 / Seat 4 / Customer 3
Zone B / Row 11 / Seat 5 / Customer 5
Zone B / Row 11 / Seat 6 / Customer 5
Zone B / Row 11 / Seat 7 / Customer 5
Zone B / Row 11 / Seat 8 / Customer 5
Zone B / Row 11 / Seat 9 / Customer 20
Zone B / Row 11 / Seat 10 / Customer 20
Zone B / Row 12 / Seat 1 / Customer 6
Zone B / Row 12 / Seat 2 / Customer 6
Zone B / Row 12 / Seat 3 / Customer 6
Zone B / Row 12 / Seat 4 / Customer 6
Zone B / Row 12 / Seat 5 / Customer 6
Zone B / Row 12 / Seat 6 / Customer 8
Zone B / Row 12 / Seat 7 / Customer 8
Zone B / Row 12 / Seat 8 / Customer 8
Zone B / Row 13 / Seat 1 / Customer 7
Zone B / Row 13 / Seat 2 / Customer 7
Zone B / Row 13 / Seat 3 / Customer 7
Zone B / Row 13 / Seat 4 / Customer 11
Zone B / Row 13 / Seat 5 / Customer 11
Zone B / Row 13 / Seat 6 / Customer 11
Zone B / Row 13 / Seat 7 / Customer 11
Zone B / Row 13 / Seat 8 / Customer 11
Zone B / Row 14 / Seat 1 / Customer 13
Zone B / Row 14 / Seat 2 / Customer 13
Zone B / Row 14 / Seat 3 / Customer 13
Zone B / Row 14 / Seat 4 / Customer 13
Zone B / Row 14 / Seat 5 / Customer 13
Zone B / Row 14 / Seat 6 / Customer 10
Zone B / Row 14 / Seat 7 / Customer 10
Zone B / Row 14 / Seat 8 / Customer 10
Zone B / Row 14 / Seat 9 / Customer 10
Zone B / Row 15 / Seat 1 / Customer 16
Zone B / Row 15 / Seat 2 / Customer 16
Zone B / Row 15 / Seat 3 / Customer 16
Zone B / Row 15 / Seat 4 / Customer 16
Zone B / Row 15 / Seat 5 / Customer 14
Zone B / Row 15 / Seat 6 / Customer 14
Zone B / Row 15 / Seat 7 / Customer 14
Zone B / Row 15 / Seat 8 / Customer 14
Zone B / Row 15 / Seat 9 / Customer 14
Zone B / Row 16 / Seat 1 / Customer 17
Zone B / Row 16 / Seat 2 / Customer 17
Zone B / Row 16 / Seat 3 / Customer 17
Zone B / Row 16 / Seat 4 / Customer 18
Zone B / Row 16 / Seat 5 / Customer 18
Zone B / Row 16 / Seat 6 / Customer 18
Total revenue: 1480 euros
Percentage of successful transactions: 100.00%
Average service time: 2.40 seconds
Average waiting time: 6.62 seconds
```
- With less success rate:

```bash
User@Github:~$ ./cinema_booking 3 20
Booking completed successfully. Your seats are in zone A, row 1, from seat 1 to 2 and the transaction cost is 60 euros.
Booking completed successfully. Your seats are in zone B, row 3, from seat 1 to 1 and the transaction cost is 20 euros.
Booking completed successfully. Your seats are in zone A, row 1, from seat 3 to 3 and the transaction cost is 30 euros.
Booking completed successfully. Your seats are in zone A, row 1, from seat 4 to 4 and the transaction cost is 30 euros.
Booking completed successfully. Your seats are in zone B, row 3, from seat 2 to 4 and the transaction cost is 60 euros.
Booking completed successfully. Your seats are in zone B, row 4, from seat 1 to 2 and the transaction cost is 40 euros.
Booking completed successfully. Your seats are in zone A, row 1, from seat 5 to 5 and the transaction cost is 30 euros.
Booking completed successfully. Your seats are in zone B, row 4, from seat 3 to 4 and the transaction cost is 40 euros.
Booking completed successfully. Your seats are in zone B, row 5, from seat 1 to 3 and the transaction cost is 60 euros.
Booking completed successfully. Your seats are in zone B, row 5, from seat 4 to 5 and the transaction cost is 40 euros.
Booking failed because there are no suitable seats available.
Booking completed successfully. Your seats are in zone A, row 2, from seat 1 to 2 and the transaction cost is 60 euros.
Booking completed successfully. Your seats are in zone B, row 3, from seat 5 to 5 and the transaction cost is 20 euros.
Booking failed because there are no suitable seats available.
Booking failed because there are no suitable seats available.
Booking failed because there are no suitable seats available.
Booking completed successfully. Your seats are in zone B, row 4, from seat 5 to 5 and the transaction cost is 20 euros.
Booking failed because there are no suitable seats available.
Booking failed because there are no suitable seats available.
Booking completed successfully. Your seats are in zone A, row 2, from seat 3 to 5 and the transaction cost is 90 euros.

Seat Plan:
Zone A / Row 1 / Seat 1 / Customer 2
Zone A / Row 1 / Seat 2 / Customer 2
Zone A / Row 1 / Seat 3 / Customer 1
Zone A / Row 1 / Seat 4 / Customer 5
Zone A / Row 1 / Seat 5 / Customer 9
Zone A / Row 2 / Seat 1 / Customer 14
Zone A / Row 2 / Seat 2 / Customer 14
Zone A / Row 2 / Seat 3 / Customer 20
Zone A / Row 2 / Seat 4 / Customer 20
Zone A / Row 2 / Seat 5 / Customer 20
Zone B / Row 3 / Seat 1 / Customer 3
Zone B / Row 3 / Seat 2 / Customer 6
Zone B / Row 3 / Seat 3 / Customer 6
Zone B / Row 3 / Seat 4 / Customer 6
Zone B / Row 3 / Seat 5 / Customer 12
Zone B / Row 4 / Seat 1 / Customer 4
Zone B / Row 4 / Seat 2 / Customer 4
Zone B / Row 4 / Seat 3 / Customer 7
Zone B / Row 4 / Seat 4 / Customer 7
Zone B / Row 4 / Seat 5 / Customer 16
Zone B / Row 5 / Seat 1 / Customer 8
Zone B / Row 5 / Seat 2 / Customer 8
Zone B / Row 5 / Seat 3 / Customer 8
Zone B / Row 5 / Seat 4 / Customer 10
Zone B / Row 5 / Seat 5 / Customer 10
Total revenue: 600 euros
Percentage of successful transactions: 70.00%
Average service time: 2.00 seconds
Average waiting time: 5.02 seconds
```
## Detailed Explanation
- Zones:
    - For low values:
        - Zone A consists of rows 0 to 1 and costs 30 euros per seat.
        - Zone B consists of rows 2 to 4 and costs 20 euros per seat.
    - For high values:
        - Zone A consists of rows 0 to 9 and costs 30 euros per seat.
        - Zone B consists of rows 10 to 29 and costs 20 euros per seat.
- Theater Structure:
    - For low values:
        - The theater is initialized with 5 rows, each having 5 seats.
    - For high values:
        - The theater is initialized with 30 rows, each having 10 seats.
    - Seats are represented by a 2D array where 0 indicates an empty seat.
- Synchronization:
    - `theater_lock` mutex is used to protect access to the theater seating plan.
    - `stats_lock` mutex is used to protect access to the statistics.
    - `cashiers` semaphore limits the number of concurrent customers being served.
- Customer Thread:
    - Each customer selects a zone and the number of tickets randomly.
    - The customer tries to find consecutive available seats in the selected zone.
    - If seats are found, they are booked, and the cost is added to the total revenue.
    - If no suitable seats are found, the booking fails.
    - The program records the service time and waiting time for each customer.

**Note:** This project is an assignment of the 3rd series of exercises of the Algorithms, Programming and Data Structures (104) course of AST NKUA.