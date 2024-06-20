# Palindrome Checker

This project provides a simple palindrome checker implemented in C. It includes functionality to check if a given input (either a string or an integer) is a palindrome.

## Files
The project consists of the following files:

- `main.c`: Contains the main function where the user inputs a string or integer and calls the appropriate palindrome checking functions.

- `palindrome.h`: Header file that declares the functions used for palindrome checking (is_string_palindrome and is_int_palindrome).

- `palindrome.c`: Implementation file that defines the palindrome checking functions (is_string_palindrome and is_int_palindrome).

- `Makefile`: Makefile for compiling the project, organizing object files, and cleaning up build artifacts.

## Functionality
`is_string_palindrome(const char *str)`
- Checks if the given string `str` is a palindrome.
- Ignores non-alphanumeric characters and case differences.
`is_int_palindrome(int num)`
- Checks if the given integer `num` is a palindrome.
- Converts the integer to a string and uses `is_string_palindrome` to perform the palindrome check.
## Usage
To use the palindrome checker:

1. Compile the program: Use the provided Makefile to compile the program.
```bash
make
```
2. Run the program: Execute the compiled binary `palindrome_checker`.
```bash
./palindrome_checker
```

## Examples
- String Input:
```console
User@Github:~$ ./palindrome_checker 
Enter a string or an integer: radar
"radar" is a palindrome.
```
- Integer Input:
```console
User@Github:~$ ./palindrome_checker 
Enter a string or an integer: 12321
12321 is a palindrome.
```
- Mixed Characters and Numbers:
```console
User@Github:~$ ./palindrome_checker 
Enter a string or an integer: A man, a plan, a canal, Panama!
"A man, a plan, a canal, Panama!" is a palindrome.
```
- Not a Palindrome:
```console
User@Github:~$ ./palindrome_checker 
Enter a string or an integer: Hello!
"Hello!" is not a palindrome.
```
## Cleaning Up
To clean up the build artifacts (object files and executable), use:
```bash
make clean
```