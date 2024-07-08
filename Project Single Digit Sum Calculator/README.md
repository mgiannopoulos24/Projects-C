# Single Digit Sum Calculator
This project is a simple C program that repeatedly calculates the sum of the digits of an integer until the result is a single-digit number. The program prompts the user to enter an integer, and then it processes this integer to reduce it to a single-digit number, displaying the sum of digits at each step.

## Features
- Prompts the user to enter an integer.
- Calculates the sum of the digits of the integer.
- Repeats the calculation with the resulting sum until a single-digit number is obtained.
- Displays the sum of digits at each step.
- Displays the final single-digit number.

## Usage

1. Compile the program:
```console
gcc -o sdsum sdsum.c
```

2. Run the compiled program:
```console
./sdsum
```

3. Follow the on-screen instructions: Enter an integer when prompted. The program will display the sum of the digits at each step until it reduces the number to a single digit.


### Example
Here's an example of how the program works:
```console
User@Github:~$ ./sdsum
Enter an integer: 9875
Sum of digits: 29
Sum of digits: 11
Sum of digits: 2
The single-digit number is: 2
```

## Code Explanation
The main logic of the program is as follows:

1. User Input: The program prompts the user to enter an integer.
2. Digit Sum Calculation: 
- The program calculates the sum of the digits of the entered integer.
- It repeats this process with the resulting sum until the number becomes a single digit.
3. Display Results:
- At each step, the sum of the digits is displayed.
- Finally, the single-digit number is displayed.


**Note:** This project is an assignment of the 1st series of exercises of the Algorithms, Programming and Data Structures (104) course of AST NKUA.