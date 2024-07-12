# DNA Common Substring Finder
This C program reads two DNA sequence files and finds the maximum common substring using dynamic programming.

## Features:
- Input: Takes two DNA sequence files as command line arguments.
- Processing: Filters out non-DNA characters (anything other than A, G, T, C) from the input files.
- Algorithm: Uses a dynamic programming approach to find the longest common substring between the two sequences.
- Output: Prints the maximum common substring found between the two sequences

## Compilation:

To compile the code run `make` and to remove the executable run `make clean`.

## Notes
The program assumes that input DNA sequences are provided in text files.
It uses dynamic memory allocation to handle potentially large DNA sequences up to 1,000,000 characters long.
Ensure that the input files contain valid DNA sequences consisting only of the characters A, G, T, and C.

## Examples

```console
User@Github:~$ ./dna ./dnas/sample1.dna ./dnas/sample2.dna 
Maximum common substring is: TAGATATAG
User@Github:~$ echo -e "CTATAGAT\nHello WORLDATAGGG" > ./dnas/split.dna
User@Github:~$ ./dna ./dnas/split.dna ./dnas/split.dna 
Maximum common substring is: CTATAGATATAGGG
User@Github:~$ ./dna ./dnas/carsonella-ruddii.dna ./dnas/sample1.dna 
Maximum common substring is: ATATAGACG
User@Github:~$ ./dna ./dnas/escherichia-coli.dna ./dnas/carsonella-ruddii.dna 
Maximum common substring is: AATTAAAATTTTATT
User@Github:~$ ./dna ./dnas/claviceps-purpurea.dna ./dnas/carsonella-ruddii.dna 
Maximum common substring is: GTTTTTTTTTTCT
User@Github:~$ time ./dna ./dnas/theobroma-cacao.dna ./dnas/escherichia-coli.dna 
Maximum common substring is: GGTTTGCTTTTATG

real    0m9.457s
user    0m6.236s
sys     0m3.203s
User@Github:~$ time ./dna ./dnas/theobroma-cacao.dna ./dnas/alien.dna
Maximum common substring is: AAAAAAAAAAAAAAAAACC

real    0m3.155s
user    0m3.136s
sys     0m0.000s
User@Github:~$ time ./dna ./dnas/theobroma-cacao.dna ./dnas/theobroma-cacao.dna > shared.dna

real    0m22.433s
user    0m22.409s
sys     0m0.000s
User@Github:~$  wc -c shared.dna
98165 shared.dna
User@Github:~$  md5sum shared.dna
5ca8c9e6fd76d46221d3beadd610b165  shared.dna
User@Github:~$ time ./dna ./dnas/alien.dna ./dnas/alien.dna > shared.dna 

real    0m2.301s
user    0m2.281s
sys     0m0.000s
User@Github:~$ wc -c shared.dna
62488 shared.dna
User@Github:~$ wc -c shared.dna
62488 shared.dna
User@Github:~$  md5sum shared.dna
d4544ab6971c6a54bb375159adc5852b  shared.dna
```

**Note:** This project is the 2nd exercise of 2nd assignment of Introduction to Programming 2023-24 (Κ04) course of DIT NKUA.