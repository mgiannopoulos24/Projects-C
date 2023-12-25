# Projects C
C projects | Introduction to Programming 2020-21

## Kalmpr.c

The kalmpr.c program computes and prints the number of all k-almost prime numbers found within the interval [MINNUM,MAXNUM], for 2≤ k ≤ MAXK, and the number of those that are in particular, 2-relative prime numbers, i.e., half-primes. For the half-integers of interest, it prints the factors of which they are decomposed. Then we increase the range of the range of the [MINNUM,MAXNUM] interval to see the rate at which the execution time of our program also increases. Then the program selects 20 positive integer numbers for each of which it prints the k corresponding to it.

## Wavproc.c 

The wavproc.c program which will read with getchar from the input audio data that following the wav standard described above and perform some processing
on that data. Exactly what processing your program will perform will be determined by the value of a symbolic MODE constant that you set in it. The requested treatments,depending on the value of MODE are:

* MODE 1
The program should check if the data read follows the wav standard that
previously described and print the relevant audio information. i.e.

- size of file (in bytes)
- size of format chunk 
- WAVE type format
- mono/stereo
- sample rate
- bytes per second
- block alignment
- bits/sample
- size of data chunk

* MODE 2
This mode transfers to the output, with the help of the putchar function, the audio data, having doubled
its playback speed, without altering the samples that make up the sampled sound.

* MODE 3
This mode has a similar function to the previous section, where the sound at the input will be transferred to the output at twice the playback speed. 
Presumably, the time playback time will be doubled, since the samples that make up the sampled sound will be once again be transferred unaltered.

* MODE 4
Τhis mode transfers to the output, with the help of the putchar function, the data of only the left channel of the audio, 
in case the input audio is stereo. If the input sound is mono, no signal is produced, but simply the single channel of the input.

* MODE 5
With this mode the output will be the right channel of the input, in case of stereo sound at the input, or the single channel itself, in case of mono sound.

* MODE 6
This mode switches to the output, with the help of the putchar function, the sound of the input to the output, but with reduced its intensity to 1/8 of the original.

* MODE 7

## Shoprec.c (TBA)



