/* kalmpr.c */

//Kalmpr.c is a program that counts the semiprimes and the kprimes between the defined MINNUM and MAXNUM values.

#include <stdio.h>
#include <stdlib.h>                    //Header file for srand and rand functions
#define MINNUM 2100000000              //Minimum number
#define MAXNUM 2101000000              //Maximum number
//#define MINNUM 100                   //Minimum number
//#define MAXNUM 100000                //Maximum number
#define MAXK 5
#include <time.h>				       //Header file for time function
#define COMPUTATIONS 20				   //Pairs of numbers to compute
int k, num, divisor, piliko;           //Initialization of variables
int count_sem=0;                       //Semiprimes Counter
int count_kprim=0;                     //K-Primes Counter
int x, y, z, i;                        //Initialization of variables
long curtime;                          //Initialize current Unix Time


int main (void)
{
    printf("Checking numbers in [%d,%d]\n", MINNUM, MAXNUM);
    for(num=MINNUM; num<=MAXNUM; num++)
    {
        k=0;
        divisor=2;
        piliko=num;

        while (divisor<=piliko && k<=MAXK)
        {
            if (piliko%divisor==0)
            {
                k++;
                piliko=piliko/divisor;
            }
            else
            {
                if (piliko>1 && divisor*divisor>piliko)
                {
                    divisor = piliko;
                }
                else
                {
                    if (divisor == 2) divisor++; else divisor+=2;
                }
            }
        }
        if (k==2)
        {
            count_sem++;
            if (num/divisor!=divisor && (divisor - num/divisor) <= 0.01*divisor ) //The first two factors are unequal, but the smaller of them is not more than 1% of the largest.
            {
                printf("%d * %d = %d is an interesting semiprime\n", num/divisor, divisor, num);
            }
        }
        if ( k >= 2 & k<= MAXK)
        {
            count_kprim++;
        }
    }
    printf("Found %d K-almost prime numbers (2<=K<=%d)\n", count_kprim, MAXK);
    printf("Found %d semiprimes\n\n", count_sem);

    curtime = time(NULL); /* Current time (in seconds since 1/1/1970) */
    printf("Current time is %ld\n\n", curtime); //Print current UNIX time
    srand((unsigned int) curtime); /* Seed for random number generator */
    printf("Checking 20 random numbers\n\n");
    for(i=1; i<=COMPUTATIONS; i++) 
    {
        y = rand();
        z = rand();
        x = ((y % 32768)+1)*((z % 32768)+1)+1;
        k=0;
        divisor=2;
        piliko=x;

        while (divisor<=piliko)
        {
            if (piliko%divisor==0)
            {
                k++;
                piliko=piliko/divisor;
            }
            else
            {
                if (piliko>2 && divisor*divisor>piliko)
                {
                    divisor = piliko;
                }
                else
                {
                    divisor++;
                }
            }
        }
        printf("%d is a %d-almost prime number\n", x, k);
    }
}
