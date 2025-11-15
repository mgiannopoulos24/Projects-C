# Project Aliquot

This is a program for calculating and analyzing **Aliquot Sequences**. An [Aliquot Sequence](https://en.wikipedia.org/wiki/Aliquot_sequence) starts with a positive integer $n$, and each subsequent term is defined as the sum of the proper divisors of the preceding term. The sequence terminates when it reaches the number 0.

Denoting $s(n)$ as the sum of the proper divisors of $n$, the sequence is defined as:

$$
s(n) = \sum_{d|n, d\neq n} d
$$

where $d$ is a proper divisor of $n$.

The Aliquot Sequence for $n$ is: $n$, $s(n)$, $s(s(n))$, \ldots and the **aliquot length** $l$ is the smallest integer for which $s^{l}(n) = 0$.

## Functionality

- The program reads three values from standard input (stdin):
1. The positive integer to start the sequence from.
2. The maximum length of the sequence to look for (0 for unlimited length).
3. A character ('f' for printing the full sequence, 'l' for printing only the length).
- It calculates the sum of proper divisors $s(n)$ for each term in the sequence.
- It prints either the full sequence ('f') or only the length ('l') to standard output.

## Examples

### Example n=12 - Full Sequence

```bash
$ ./aliquot
Please give the number to start the aliquot sequence from: 12
Provide the max aliquot length to look for (0 for unlimited): 0
Do you want to print the full sequence ('f') or just the length ('l')? f
12
16
15
9
4
3
1
0
$ echo $?
0
```

### Example n=12 - Length Only
```bash
$ ./aliquot
Please give the number to start the aliquot sequence from: 12
Provide the max aliquot length to look for (0 for unlimited): 0
Do you want to print the full sequence ('f') or just the length ('l')? l
Length of aliquot sequence: 7
$ echo $?
0
```

### Example Limit Exceeded
```bash
$ ./aliquot
Please give the number to start the aliquot sequence from: 276
Provide the max aliquot length to look for (0 for unlimited): 0
Do you want to print the full sequence ('f') or just the length ('l')? f
276
396
...
749365894850244
1414070378301756
Number exceeds maximum supported integer (1000000000000000). Stopping.
$ echo $?
1
```

**Note:** This project is the 1st assignment of Introduction to Programming 2025-26 (Κ04) course of DIT NKUA.