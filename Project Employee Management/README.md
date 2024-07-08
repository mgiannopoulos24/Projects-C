# Employee Management Project
## Description
This project is an Employee Management System implemented in C. It allows users to perform various operations on employee records such as adding, deleting, updating, listing, and searching employees. The program utilizes a text file (data.txt) to persist employee data between program runs.

## Features
- Add a new employee with unique ID, name, and salary.
- Delete an existing employee by ID.
- Update employee information (name or salary) based on ID.
- List all employees currently stored in the system.
- Search for an employee by ID to view their details.

## Compilation

1. Compile the Project:
- Use the provided Makefile to compile the project
```console
make
```
- This will compile all source files (`main.c`, `employee.c`, `utils.c`) and generate an executable `employee_management` in the `build/` directory.

2. Run the Program:
- Execute the program from the `build/` directory
- The program will load existing employee data from `data.txt` and present a menu for operations.

3. Menu Options:
- Choose options from the menu to add, delete, update, list, or search employees.
- Modifications to employee data are automatically saved to data.txt.
4. Exiting the Program:
- Choose option `6` in the menu to exit the program cleanly.

## Cleanup

To remove the executables and the object files run:
```console
make clean
```

## Notes
- Ensure that `data.txt` remains in the root directory for the program to read and write employee data.