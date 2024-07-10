The mirror program efficiently identifies and sums up numbers within a specified range that meet a unique set of criteria. Specifically, it finds all numbers that are squares of prime numbers. Additionally, it ensures that the mirror (reverse) of these square numbers is also a prime square but not palindromic (the same forwards as backwards).

## How it works

1. **Input Range**: The program accepts two command-line arguments representing the lower and upper bounds of the range to be analyzed.
2. **Prime Identification**: Utilizing the Sieve of Eratosthenes algorithm, the program precomputes prime numbers up to the square root of the upper limit to optimize performance.
3. **Square and Mirror Validation**: For each number in the range that is a square of a prime, the program computes its mirror. It then checks if this mirror is also a prime square and ensures it's not palindromic.
4. **Summation**: All numbers meeting the above criteria are summed together and the total sum is output.

## How to run it

Both on Linux and Windows: 

`gcc -o mirror mirror.c -lm`

## Example executions

- `./mirror 1 100000`<br>
The sum is: 110620
- `./mirror 1 10000000`<br>
The sum is: 15633754
- `./mirror 1 100000000000`<br>
The sum is: 53009475688

## Special thanks

I would like to thank [Danae](https://github.com/danaemav) for helping me understand how to make the program handle the range `./mirror 1 100000000000`.

**Note:** This project is the 2nd exercise of 2nd assignment of Introduction to Programming 2023-24 (Κ04) course of DIT NKUA.