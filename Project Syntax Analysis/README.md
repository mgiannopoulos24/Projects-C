# Syntax Analysis Project

This project implements a simple calculator that can parse and evaluate arithmetic expressions using a recursive descent parser in C. The project is organized into multiple source and header files for better structure and maintainability.

## Files Description

- **src/**: Contains all the source code files.
  - `main.c`: Entry point of the program, handles reading from a file and printing results.
  - `lexer.c`: Implements lexical analysis (tokenization).
  - `parser.c`: Implements syntax analysis (parsing).
  - `ast.c`: Implements the Abstract Syntax Tree (AST) structure.
  - `evaluator.c`: Implements the evaluation of the AST.
  - `utils.c`: Utility functions, such as error handling.
- **include/**: Contains all the header files corresponding to the source files.
- **obj/**: Directory to store object files.
- **build/**: Directory to store the final executable.
- **Makefile**: Build instructions for the project.

## Compilation

To compile the project, navigate to the project directory and run:

```console
make
```

This will compile all the source files and create the executable `calculator` in the `build` directory.

## Usage
The program reads arithmetic expressions from a text file and prints each expression along with its evaluated result.

Run the program with the input file:

```console
./build/calculator expressions.txt
```
The output will be:

```console
User@Github:~$ ./build/calculator expressions.txt 
Arithmetic expression: 2 + 3
Result: 5
Arithmetic expression: 7 - 4
Result: 3
Arithmetic expression: 5 * 6
Result: 30
Arithmetic expression: 8 / 2
Result: 4
Arithmetic expression: 2 + 3 * 4
Result: 14
Arithmetic expression: (2 + 3) * 4
Result: 20
Arithmetic expression: 10 / 2 + 3
Result: 8
Arithmetic expression: 10 / (2 + 3)
Result: 2
Arithmetic expression: ((2 + 3) * 4) - (5 * (3 - 1))
Result: 10
Arithmetic expression: ((10 / 2) + (3 * 4)) * 2
Result: 34
```

## Cleaning Up
To clean up the build artifacts (object files and executable), run:


## Additional Information
- **Lexer:** The lexical analyzer converts the input string into tokens.
- **Parser:** The parser uses a recursive descent approach to build an AST from the tokens.
- **AST:** The Abstract Syntax Tree represents the hierarchical structure of the arithmetic expression.
- **Evaluator:** The evaluator traverses the AST to compute the result of the expression.
- **Utils:** Utility functions include error handling.