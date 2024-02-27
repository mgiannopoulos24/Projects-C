The Collatz conjecture, also known as the $3n + 1$ conjecture, is a mathematical hypothesis that applies to a sequence defined for any positive integer. It suggests that no matter what value of $n$ you start with, the sequence will always reach 1. The sequence is defined as follows:

1. If $n$ is 1, the sequence has ended.
2. If $n$ is even, the next $n$ of the sequence becomes $n/2$.
3. If $n$ is odd, the next $n$ of the sequence becomes $3n+1$.

The program calculates the length of Collatz sequences for a range of integers provided as command-line arguments. It leverages OpenMP for parallel processing to speed up the computation. The program is designed to handle large ranges efficiently by using a cache to store the lengths of sequences that have already been computed.

Times of execution:

1. collatz.c
- O0 complexity: 
- 03 complexity: 

2. collatz_fast.c
- O0 complexity: ~30 sec
- O3 complexity: ~15 sec