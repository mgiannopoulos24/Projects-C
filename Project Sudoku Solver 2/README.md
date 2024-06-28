## Sudoku Solver 2
The Sudoku Solver 2 project is a C-based program that reads a Sudoku puzzle from a file, solves it using a backtracking algorithm, and prints both the original and solved puzzles in a readable format with grid separators. The project is organized into multiple files for better maintainability and readability.

## Files
- `include/sudoku.h`: Header file containing function declarations and constants.
- `src/main.c`: Contains the main function which drives the program.
- `src/sudoku.c`: Contains the implementation of the Sudoku solver and grid printing functions.
- `src/utils.c`: Contains utility functions for reading the Sudoku grid from a file.
- `sudoku.txt`: Text file containing the Sudoku puzzle to be solved.
- `Makefile`: Makefile for compiling and building the project.

## Usage
### Steps to Run
1. Place the Sudoku Puzzle in sudoku.txt:

Ensure that the sudoku.txt file in the root directory contains the Sudoku puzzle you want to solve. The format should be a 9x9 grid of numbers separated by spaces, with 0 representing empty cells.

Example of `sudoku.txt`:

```txt
7 2 0 0 0 0 0 0 5
0 1 0 0 8 0 0 2 0
0 0 0 0 0 0 0 7 0
0 0 0 0 0 5 9 0 0
0 0 0 7 1 2 0 0 0
0 0 0 0 0 8 5 3 0
0 0 3 0 0 0 4 0 6
5 0 0 0 6 0 0 0 0
0 0 8 1 0 0 0 0 0
```

2. Build the Project:

Open a terminal in the project directory and run:

```bash
make
```

3. Run the Solver:

Execute the compiled binary:

```bash
./build/sudoku_solver
```

The program will read the puzzle from `sudoku.txt`, solve it, and print both the original and solved Sudoku grids to the terminal.

## Example Output
```console
User@Github:~$ ./build/sudoku_solver 
Original Sudoku:
7 2 0 | 0 0 0 | 0 0 5
0 1 0 | 0 8 0 | 0 2 0
0 0 0 | 0 0 0 | 0 7 0
------+-------+------
0 0 0 | 0 0 5 | 9 0 0
0 0 0 | 7 1 2 | 0 0 0
0 0 0 | 0 0 8 | 5 3 0
------+-------+------
0 0 3 | 0 0 0 | 4 0 6
5 0 0 | 0 6 0 | 0 0 0
0 0 8 | 1 0 0 | 0 0 0

Solved Sudoku:
7 2 4 | 3 9 1 | 8 6 5
9 1 6 | 5 8 7 | 3 2 4
8 3 5 | 4 2 6 | 1 7 9
------+-------+------
4 8 7 | 6 3 5 | 9 1 2
3 5 9 | 7 1 2 | 6 4 8
2 6 1 | 9 4 8 | 5 3 7
------+-------+------
1 7 3 | 2 5 9 | 4 8 6
5 4 2 | 8 6 3 | 7 9 1
6 9 8 | 1 7 4 | 2 5 3
```

## Cleaning Up
To remove the compiled binary and object files, run: