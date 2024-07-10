# Flawless Squares Finder
This project is a C program designed to find and sum all "flawless squares" within a given range of natural numbers. A "flawless square" is defined as a number that is both a perfect square and equals the square of the sum of its consecutive digits when grouped in various possible ways.

## Definition
A number $n$ is a flawless square if:
1. $n$ is a perfect square, i.e., there exists an integer $x$ such that $x^2=n$.
2. $n$ equals the square of the sum of its digits when grouped in all possible ways.

## Examples
- 1 is a flawless square because 1 = $1^2$.
- 81 is a flawless square because 81 = $(8+1)^2$.
- 1296 is a flawless square because 1296 = $(1+2+9+6)^2$.
- 3025 is a flawless square because 3025 = $(30+25)^2$.

## Usage
### Compilation
To compile the program, use the following command:
```console
gcc -O3 -Wall -Wextra -Werror -pedantic -o flawless flawless.c -lm
```

### Running the Program
To run the program, use the following command:
```console
./flawless <start> <end>
```

Replace `<start>` and `<end>` with the desired range of natural numbers. For example:
```console
./flawless 1 1000
```

### Output
The program will output the sum of all flawless squares within the specified range.


## Example Outputs

```console
User@Github:~$ ./flawless 1 1000
182
```
```console
User@Github:~$ ./flawless 1 100000
184768
```
```console
User@Github:~$ ./flawless 1 10000000
30940314
```
```console
User@Github:~$ ./flawless 1 10000000000
499984803178
```
## Code Explanation
### Functions
1. **is_perfect_square:** Checks if a number is a perfect square.,
```c
int is_perfect_square(long long num);
```
2. **sum_of_digits:** Calculates the sum of the digits of a number within a specified range.
```c
long long sum_of_digits(const char *digits, int start, int end);
```
3. **check_groupings:** Recursively checks all possible groupings of digits to see if any grouping's sum, when squared, equals the original number.
```c
int check_groupings(const char *digits, int len, int start, long long current_sum, long long original_num);
```
4. **is_flawless_square:** Checks if a number is both a perfect square and a flawless square by using the above functions.
```c
int is_flawless_square(long long num);
```
5. **main:** The main function reads the range from the command line, iterates through the range, checks each number using the is_flawless_square function, and accumulates the sum of flawless squares.
```c
int main(int argc, char *argv[]);
```

**Note:** This project is the 3rd exercise of 2nd assignment of Introduction to Programming 2023-24 (Κ04) course of DIT NKUA.