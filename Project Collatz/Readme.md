## Collatz Conjecture

The Collatz conjecture, also known as the $3n + 1$ conjecture, is a mathematical hypothesis that applies to a sequence defined for any positive integer. It suggests that no matter what value of $n$ you start with, the sequence will always reach 1. The sequence is defined as follows:

1. If $n$ is 1, the sequence has ended.
2. If $n$ is even, the next $n$ of the sequence becomes $n/2$.
3. If $n$ is odd, the next $n$ of the sequence becomes $3n+1$.

### collatz.c

This program calculates the length of the Collatz sequence for numbers within a specified range (start number to end number), provided as command-line arguments. It identifies the number within this range that produces the longest Collatz sequence. The Collatz sequence for a number is computed using a while loop that divides even numbers by 2 and multiplies odd numbers by 3 and adds 1, continuing until the number reaches 1. It measures the execution time for this computation. Finally, it prints the number with the longest sequence, the length of that sequence, and the execution time.

### collatz_fast.c

This multithreaded C program calculates the Collatz sequence lengths for numbers in a specified range, distributing the workload across multiple threads to utilize parallel processing for efficiency. It uses a shared cache to store Collatz sequence lengths to avoid recalculating sequences for previously encountered numbers, enhancing performance. The program synchronizes access to shared resources using a read-write lock to safely update the maximum sequence length and the corresponding number among all threads. It divides the input range into equal parts, assigning each part to a separate thread, and then each thread computes the longest Collatz sequence within its range. 

## Execution times (with a range of 100 to 100000000)

On Linux:

1. collatz.c
- O0 Optimization: ≈ 117 sec
- 03 Optimization: ≈ 36 sec

2. collatz_fast.c
- O0 Optimization: ≈ 6 sec
- O3 Optimization: ≈ 4 sec

On Windows:

1. collatz.c
- O0 Optimization: ≈ 67 sec
- 03 Optimization: ≈ 30 sec

2. collatz_fast.c
- O0 Optimization: ≈ 1.8 - 1.85 sec
- O3 Optimization: ≈ 1.2-1.3 sec

## How to run it

On Linux:

1. collatz.c
- O0 Optimization: `gcc -O0 -m32 -Wall -Wextra -Werror -pedantic -o collatz collatz.c`
- 03 Optimization: `gcc -O3 -m32 -Wall -Wextra -Werror -pedantic -o collatz collatz.c`

2. collatz_fast.c
- O0 Optimization: `gcc -O0 -m32 -Wall -Wextra -Werror -pedantic -o collatz_fast collatz_fast.c -lpthread`
- O3 Optimization: `gcc -O3 -m32 -Wall -Wextra -Werror -pedantic -o collatz_fast collatz_fast.c -lpthread`

On Windows:

1. collatz.c
- O0 Optimization: `gcc -O0 -o collatz collatz.c`
- 03 Optimization: `gcc -O3 -o collatz collatz.c`

2. collatz_fast.c
- O0 Optimization: `gcc -O0 -o collatz_fast .\collatz_fast.c`
- O3 Optimization: `gcc -O3 -o collatz_fast .\collatz_fast.c`


**Note:** This project is the 3rd exercise of 1st assignment of Introduction to Programming 2023-24 (Κ04) course of DIT NKUA.