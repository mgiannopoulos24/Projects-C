## Sudoku Solver 2 GUI
The SudokuSolverGUI project is a C-based program with a graphical user interface (GUI) using GTK+. It reads a Sudoku puzzle from a file, solves it using a backtracking algorithm, and displays both the original and solved puzzles in a user-friendly GUI.

## Files
- `include/sudoku.h`: Header file containing function declarations and constants.
- `src/main.c`: Contains the main function which drives the program.
- `src/sudoku.c`: Contains the implementation of the Sudoku solver and grid printing functions.
- `src/utils.c`: Contains utility functions for reading the Sudoku grid from a file.
- `sudoku.txt`: Text file containing the Sudoku puzzle to be solved.
- `Makefile`: Makefile for compiling and building the project.

## Usage

### Installing GTK+ 3 (on Ubuntu/Debian)

```sh
sudo apt-get update
sudo apt-get install libgtk-3-dev
```

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
./build/sudoku_solver_gui
```

The program will read the puzzle from `sudoku.txt`, solve it, and print both the original and solved Sudoku grids to the terminal.

## Example Output
```console
User@Github:~$ ./build/sudoku_solver_gui 
```
- Load Sudoku:

<p align="center">

<img src="https://i.imgur.com/aT4IGpC.png">

</p>

- Solve Sudoku:

<p align="center">

<img src="https://i.imgur.com/S5ET0ww.png">

</p>

## Cleaning Up
To remove the compiled binary and object files, run:

```console
make clean
```