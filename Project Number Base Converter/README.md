# Number System Conversion Utility
This C program provides functionality to convert numbers between different number systems. It supports conversions for:

- Decimal to Binary
- Binary to Decimal
- Decimal to Octal
- Octal to Decimal
- Hexadecimal to Binary
- Binary to Hexadecimal

The program is structured with modular code and organized into directories for ease of maintenance and compilation.

## Usage
1. Compilation: To compile the program, navigate to the project root directory and run the following command:
```console
make
```

This command compiles all source files (`main.c` and `converter.c`) into object files and links them into the executable `build/converter`.

2. Running the Program: After compilation, you can run the program by executing the following command:

```console
./build/converter
```

3. Cleaning Up: To clean up build artifacts (object files and the executable), run:
```console
make clean
```
## How to Use
Upon running the executable `converter`, you will be presented with a menu-driven interface. Choose the desired conversion option from the menu and follow the prompts to enter the number you wish to convert. The program will then display the converted result.

## Example
Here's an example of using the program:

```console
User@Github:~$ ./build/converter 

Number System Conversion Menu:
1. Decimal to Binary
2. Binary to Decimal
3. Decimal to Octal
4. Octal to Decimal
5. Hexadecimal to Binary
6. Binary to Hexadecimal
7. Exit
Enter your choice: 1
Enter a decimal number: 25
Binary equivalent: 11001

Number System Conversion Menu:
1. Decimal to Binary
2. Binary to Decimal
3. Decimal to Octal
4. Octal to Decimal
5. Hexadecimal to Binary
6. Binary to Hexadecimal
7. Exit
Enter your choice: 4
Enter an octal number: 34
Decimal equivalent: 28

Number System Conversion Menu:
1. Decimal to Binary
2. Binary to Decimal
3. Decimal to Octal
4. Octal to Decimal
5. Hexadecimal to Binary
6. Binary to Hexadecimal
7. Exit
Enter your choice: 7
Exiting...
```