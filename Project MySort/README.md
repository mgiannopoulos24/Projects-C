# Project MySort - Multi-Process Sorting System

## Overview
This project implements a multi-process sorting system that sorts records contained in a binary input file using two different sorting algorithms. The project leverages multiple child processes, each executing different sorting algorithms, to achieve parallel sorting. The goal is to create an executable called `mysort` which uses two different sorting programs (`sorter1` and `sorter2`) to sort records alphabetically by surname, then by name, and finally by ID.

## Files in the Project

### 1. **mysort.c**
   - This is the main entry point for the program.
   - It parses command-line arguments and creates a process hierarchy to manage sorting tasks.
   - Calls `coordinator` to manage the sorting process using child processes.

### 2. **coordinator.c**
   - Implements the `coordinator` function which creates multiple child processes to handle sorting tasks.
   - Each child process is assigned either `sorter1` or `sorter2` to sort a portion of the records.

### 3. **sorter1.c**
   - Implements a quicksort algorithm to sort the records.
   - Sorts the records by surname, name, and ID in ascending order.
   - Includes debugging messages that print records before and after sorting.

### 4. **sorter2.c**
   - Implements a merge sort algorithm to sort the records.
   - Sorts the records by surname, name, and ID in ascending order.
   - Includes debugging messages that print records before and after sorting.

### 5. **mysort.h**
   - Header file containing shared definitions and function prototypes.
   - Defines the `Record` structure and provides function declarations for shared functionality.

### 6. **sorter.h**
   - Header file for the sorting programs (`sorter1` and `sorter2`).
   - Contains function prototypes for the sorting algorithms.

### 7. **read_bin.c**
   - C script to read and display the contents of the binary files.
   - Allows users to input the path of a binary file and print its contents for verification purposes.

## Compilation
The project is compiled using a `Makefile` which includes all the necessary compilation commands for creating object files and executables.

### **Makefile Targets**
- **all**: Compiles all source files and creates the executables (`mysort`, `sorter1`, and `sorter2`).
- **clean**: Removes all object files and executables.

To compile the project, use:
```sh
make
```

To clean the project, use:
```sh
make clean
```

## Running the Program
The `mysort` program can be run with the following command:
```sh
./build/mysort -i <input_file> -k <num_children> -e1 ./build/sorter1 -e2 ./build/sorter2
```
Where:
- **`-i <input_file>`**: Specifies the binary input file containing the records to be sorted (e.g., `voters50.bin`).
- **`-k <num_children>`**: Specifies the number of child processes to create.
- **`-e1 ./build/sorter1`**: Specifies the executable for the first sorting program.
- **`-e2 ./build/sorter2`**: Specifies the executable for the second sorting program.

### Example Usage
```sh
./build/mysort -i ./tests/voters50.bin -k 2 -e1 ./build/sorter1 -e2 ./build/sorter2
```

## Sorting Logic
- The `sorter1` and `sorter2` executables sort the records alphabetically:
  - **Primary Key**: Surname
  - **Secondary Key**: Name
  - **Tertiary Key**: ID
- `sorter1` uses **quicksort**, while `sorter2` uses **merge sort**.

## Handling Large Inputs
- For large input files (e.g., `voters50000.bin`, `voters100000.bin`), the input is split into smaller chunks to avoid memory issues.
- Each chunk is sorted independently by child processes, and the sorted chunks are then merged.
- The `coordinator` function manages the splitting, sorting, and merging of these chunks.

## Debugging Output
- Both `sorter1` and `sorter2` include debug messages to print the records before and after sorting.
- This helps verify that the sorting is happening correctly and allows you to trace any issues.

## Viewing the Output
To verify the content of the output files (`output_0.bin`, `output_1.bin`, etc.), you can use the `read_bin.c` script.

### Running the Reader Script
```sh
./read_bin
```
You will be prompted to enter the path of the binary file you want to read, such as `./output_0.bin`. The script will then print the contents of the file.

## Directory Structure
```
project_root/
├── build/               # Directory for executables
├── include/             # Header files (mysort.h, sorter.h)
├── src/                 # Source files (mysort.c, coordinator.c, sorter1.c, sorter2.c)
├── tests/               # Test input files (e.g., voters50.bin)
├── Makefile             # Makefile for building the project
└── read_bin.c           # C script for reading binary files
```

## Notes
- The input files (`voters50.bin`, etc.) must be properly formatted binary files containing `Record` structures as defined in `mysort.h`.

## Error Handling
- If an input or output file cannot be opened, appropriate error messages will be displayed, and the program will exit.
- Invalid arguments will also result in usage instructions being printed to guide the user.
- For large input files, memory allocation errors are handled gracefully by splitting the input into manageable chunks.

## License
This project is open source. Feel free to modify and use it as needed.

**Note:** This project is the 2nd assignment of Operating Systems 2023-24 (K22) course of DIT NKUA.