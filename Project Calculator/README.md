# Advanced Calculator

## Overview
This is an advanced calculator implemented in C that supports basic arithmetic operations as well as more advanced functions such as exponentiation, square root, modulus, and trigonometric functions (sine, cosine, tangent). The project is structured into multiple files and directories for better modularity and maintainability.

## Features
- Basic arithmetic: addition, subtraction, multiplication, and division
- Exponentiation
- Square root calculation
- Modulus operation
- Trigonometric functions: sine, cosine, and tangent

## Files
- **include/input.h**: Header file for input functions.
- **include/operations.h**: Header file for arithmetic and advanced operations functions.
- **src/input.c**: Implementation of input functions.
- **src/main.c**: Main file and entry point of the application.
- **src/operations.c**: Implementation of arithmetic and advanced operations functions.
- **Makefile**: Makefile to compile and link the source files.

## Usage
### Compilation
To compile the program, navigate to the directory containing the `Makefile` and run:
```bash
make
```
And for removing it run:
```bash
make clean
```
This will compile the source files and create an executable named calculator.

## Running the Program
To run the compiled program, use:
```bash
./calculator
```

Follow the on-screen prompts to enter an operator and operands. The supported operators are:

- `+` for addition
- `-` for subtraction
- `*` for multiplication
- `/` for division
- `^` for exponentiation
- `sqrt` for square root
- `%` for modulus
- `sin` for sine
- `cos` for cosine
- `tan` for tangent

For single operand operations (`sqrt`, `sin`, `cos`, `tan`), enter only one operand when prompted.

## Examples

### Example 1: Basic Arithmetic
```bash
User@Github:~$ ./calculator 
Enter an operator (+, -, *, /, ^, sqrt, %, sin, cos, tan): +
Enter two operands: 3 5
3.00 + 5.00 = 8.00
```
### Example 2: Trigonometric Function
```bash
User@Github:~$ ./calculator 
Enter an operator (+, -, *, /, ^, sqrt, %, sin, cos, tan): sin
Enter one operand: 0.5
sin(0.50) = 0.48
```
### Example 3: Square Root
```bash
User@Github:~$ ./calculator 
Enter an operator (+, -, *, /, ^, sqrt, %, sin, cos, tan): sqrt
Enter one operand: 16
sqrt(16.00) = 4.00
```


## Contributing
Feel free to fork this repository, make improvements, and submit pull requests. Contributions are welcome!