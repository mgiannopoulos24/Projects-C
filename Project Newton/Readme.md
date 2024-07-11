## Newton-Raphson Implementation

The newton program implements the Newton-Raphson method to approximate roots of polynomial functions. Given a set of polynomial coefficients and an initial guess for the root, it iteratively refines the guess until convergence criteria are met. The program measures the execution time for finding the root and prints the result. 

## Termination conditions

1. The algorithm has converged and $|xn+1 - xn| < 10-6 $
2. The algorithm has deviated (e.g., divide by 0). In this case, print the result nan. 
3. The algorithm does not terminate after 1000 iterations. In this case we print the result incomplete.

## How to run it

Both on Linux and Windows: 

`gcc -O0 -o newton newton.c -lm`

## Example executions

- `./newton 1.0 2.0 3.0 4.0 5.0 6.0 1.0`<br>
   Approximate root: `-0.67`
- `./newton 1.0 0.0 1.0 0.0 0.0 0.0 2.0`<br>
   Result: `incomplete`
- `./newton 1.0 0.0 1.0 0.0 0.0 0.0 0.0`<br>
    Result: nan
 

**Note:** This project is the 1st exercise of 2nd assignment of Introduction to Programming 2023-24 (Κ04) course of DIT NKUA.