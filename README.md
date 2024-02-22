# Projects C
C projects | Introduction to Programming 2020-21

## Project Kalmpr

The ```kalmpr.c``` program computes and prints the number of all k-almost prime numbers found within the interval [MINNUM,MAXNUM], for 2≤ k ≤ MAXK, and the number of those that are in particular, 2-relative prime numbers, i.e., half-primes. For the half-integers of interest, it prints the factors of which they are decomposed. Then we increase the range of the range of the [MINNUM,MAXNUM] interval to see the rate at which the execution time of our program also increases. Then the program selects 20 positive integer numbers for each of which it prints the k corresponding to it.

## Project Wavproc

The ```wavproc.c``` program which will read with getchar from the input audio data that following the wav standard described above and perform some processing on that data. Exactly what processing your program will perform will be determined by the value of a symbolic MODE constant that you set in it. The requested treatments,depending on the value of MODE are:

* MODE 1<br>
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

* MODE 2<br>
This mode transfers to the output, with the help of the putchar function, the audio data, having doubled
its playback speed, without altering the samples that make up the sampled sound.

* MODE 3<br>
This mode has a similar function to the previous section, where the sound at the input will be transferred to the output at twice the playback speed. 
Presumably, the time playback time will be doubled, since the samples that make up the sampled sound will be once again be transferred unaltered.

* MODE 4<br>
Τhis mode transfers to the output, with the help of the putchar function, the data of only the left channel of the audio, 
in case the input audio is stereo. If the input sound is mono, no signal is produced, but simply the single channel of the input.

* MODE 5<br>
With this mode the output will be the right channel of the input, in case of stereo sound at the input, or the single channel itself, in case of mono sound.

* MODE 6<br>
This mode switches to the output, with the help of the putchar function, the sound of the input to the output, but with reduced its intensity to 1/8 of the original.

* MODE 7<br>
This mode, it does not read data from the input, but to produce wav data at the output, based on the following mathematical formula:

$f(t)=my \cdot sin(2\pi f_c t - m_i \cdot sin (2\pi f_m t))$

For this purpose, I made a C function `void mysound(int dur, int sr, double fm, double fc, double mi, double mv);`
The arguments are:

- dur is the duration of the sound in seconds,
- sr is the SampleRate for the pitch of the sound and 
- fm, fc, mi, mv are the parameters given in the formula (for p I used the symbolic constant M PI, defined in math.h). 

The sound to be produced should be mono (MonoStereo = 1) and represented by 2 bytes per sample (BitsPerSample = 16)

Note: Mode 7 doesnt work properly.

## Project Shop

For this project we have a certain amount of money available, let's say M, and we want to buy N products with it. For each product i (1 ≤ i ≤ N), there are Ki model choices available, each costing Cij (1 ≤ j ≤ Ki , Cij > 0). 

For example, suppose we have 500 euros available and we want to buy a computer, a printer and an external disk, spending as much money as we can. Let's say that for the computer we have three choices, an HP, a Dell and an Asus. For the printer we have two choices, an Epson and a Lexmark, and for the external drive we have four choices, a Seagate, a Samsung, a Maxtor and a Toshiba. For each possible model of the products we want to buy, we know the cost. 

What is the maximum amount we can spend, at most M, to buy one model of each of the N products?

This project was solved with 3 different methods.

* Recursive method (```shoprec.c```):<br>

This method solves the problem using recursive logic. We start from the products and the amount of money available. For each product, we consider all possible options and calculate the maximum amount we can spend. This is repeated recursively for each product, taking into account the amount of money available and the options for each product.

* Recursive method with memorization(```shopmem.c```):<br>

In this method, we use a memory table (or cache) to store intermediate results so that they are not recalculated. Whenever we need an intermediate result, we first check if it already exists in memory. If so, we use it directly, otherwise we compute it and store it in memory for future use.

* Iterative method with dynamic programming(```shopdp.c```): <br>

This method uses dynamic programming to solve the problem. We start from the smallest problems and gradually construct solutions for larger and larger sub-problems. We keep a table that stores the optimal solutions for each subproblem so that we do not compute the same subproblems multiple times. In this way, we arrive at an optimal solution for the original problem.

The files ```shopdpcost.c``` and ```shopmemcost.c``` also are modified so that the costs of the models to be purchased are also found, in order to spend the largest possible amount of money from the initially available amount. If there is more than one combination of model costs that leads to the optimal solution, your program only needs to print one of them. Whether or not the costs are printed depends on whether or not the symbolic constant COSTS is set. 

## Project IPL

Needs a lot of changes. For fully implemented version follow [IPL Fast](https://github.com/chatziko/ipli-fast)
