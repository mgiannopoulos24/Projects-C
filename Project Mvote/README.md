# Mvote: Voting Management System

## Project Overview
Mvote is a command-line application written in C designed to manage a voting process. It allows a pollster to track the voting status of voters, add new voters, mark voters as having voted, and generate various statistics related to the voting process. The project utilizes linear hashing for efficient data access and an inverted list to track voters by postal code.

## Directory Structure
```bash
project/
|-- src/
|   |-- main.c
|   |-- hash_table.c
|   |-- inverted_list.c
|   |-- commands.c
|-- include/
|   |-- hash_table.h
|   |-- inverted_list.h
|   |-- voter.h
|   |-- commands.h
|-- tests/
|   |-- voters50.csv
|   |-- voters500.csv
|   |-- voters5000.csv
|   |-- voters50000.csv
|   |-- voters100000.csv
|-- obj/
|-- build/
|-- Makefile
|-- README.md
```

## Features
- **Voter Management:** Add new voters, search for voters by PIN, and mark voters as having voted.
- **Batch Updates:** Mark multiple voters as having voted using a batch file.
- **Statistics:** Display the number of voters who have voted, the percentage of voters who have voted, and list voters by postal code.
- **Postal Code Analysis:** Display all postal codes with the number of voters who have voted, sorted in descending order.

## Dependencies
- A C compiler (e.g., gcc)
- GNU Make

## Compilation
To compile the project, navigate to the project directory and run:
```console
make
```

This will compile the source files and generate the executable `mvote` in the `build` directory.

## Usage
### Running the Program

```console
./build/mvote -f tests/voters50.csv -b 10
```

*For convenience I chose the `voters50.csv` file but you can use any of the others.

### Commands
Once the program is running, you can use the following commands:

- **Look up a voter by PIN**
```console
l <pin>
```

Example:
```console
mvote> l 100093
100093 WIGGINS DEAN 4010 N
```

- **Insert a new voter**

```console
i <pin> <lname> <fname> <zip>
```

Example:

```console
mvote> i 100200 SMITH JOHN 4020
Voter 100200 SMITH JOHN added.
```

*This will create the `registeredvoters.csv` file in the project directory and it will have all the users of the selected `voters*.csv` file you chose before and add the new record first.*

- **Mark a voter as voted**

```console
m <pin>
```

Example:
```console
mvote> m 100093
Voter 100093 marked as voted.
```

*If you haven't used the previous option, this command will also create the `registeredvoters.csv` file in the project directory and it will have all the users of the selected `voters*.csv` file you chose before but the person you chose will have `Y` status on the last column meaning he voted.*

- **Batch vote status update**

```console
bv <fileofkeys>
```

Example:

```console
mvote> bv registeredvoters.csv
Processing PIN: 100200
Processing PIN: 100070
Processing PIN: 100040
Processing PIN: 100060
(more PINs ...)
(more PINs ...)
Processing PIN: 100009
Processing PIN: 100109
Processing PIN: 100139
Processing PIN: 100059
```

*For this command to work I would recommend having used `i` or `m` options first.*

- **Count voters who have voted**
```console
v
```

Example:

```console
mvote> v
Voted: 51
```

- **Show the percentage of voters who have voted**

```console
perc
```

Example:

```console
mvote> perc
Percentage: 100.00%
```

- **List voters by postal code**

```console
z <zipcode>
```

Example: 

```console
mvote> z 4006
100070 ROGERS TOM 4006 Y
100005 VELAZQUEZ BLAKE 4006 Y
100028 SWEENEY PERCY 4006 Y
100134 DONALDSON MARCOS 4006 Y
```

- **Display all postal codes with voter counts**

```console
o
```

Example:

```console
mvote> o
4010 4
4006 4
4009 4
3990 3
(more votes ...)
(more votes ...)
4014 1
3999 1
```

*Here we can confirm that 4 people with zipcode 4006 voted from the previous step.*

- **Exit the program**

```console
exit
```

Example:

```console
mvote> exit
```

- **List all voters**

```console
list
```

Example:

```console
mvote> list
100070 ROGERS TOM 4006 N
100040 VALENCIA JIM 4004 N
100060 BARRERA BENNETT 3999 N
100130 BAKER STANTON 4019 N
100050 LARSON HOMER 4007 N
(more voters ...)
(more voters ...)
(more voters ...)
100109 SHORT SAL 3990 N
100139 CHAVEZ ROSARIO 4005 N
100059 SNYDER BYRON 3996 N
```

*This last command wasn't a part of the assignment but I added it for convenience.*

## Error Handling
- The program will print error messages if a command fails, such as when trying to insert a voter with a duplicate PIN or when a specified file cannot be found.
- It also ensures that all dynamic memory allocations are properly managed to prevent memory leaks.

## Cleaning Up
To clean up the project directory and remove all compiled files, run:
```console
make clean
```

**Note:** This project is the 1st assignment of Operating Systems 2023-24 (K22) course of DIT NKUA.