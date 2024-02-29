#include <stdio.h>
#include <math.h>
#include <time.h>

// Function to calculate the value of the polynomial at a given point
double polynomial(double coefficients[], double x) {
    double result = 0.0;
    for (int i = 0; i <= 5; i++) {
        result += coefficients[i] * pow(x, i);
    }
    return result;
}

// Function to calculate the value of the derivative of the polynomial at a given point
double derivative(double coefficients[], double x) {
    double result = 0.0;
    for (int i = 0; i < 5; i++) {
        result += (5 - i) * coefficients[i] * pow(x, 4 - i);
    }
    return result;
}

// Function to perform the Newton-Raphson iteration
double newtonRaphson(double coefficients[], double x0) {
    double x1 = x0 - polynomial(coefficients, x0) / derivative(coefficients, x0);
    return x1;
}

int main(int argc, char *argv[]) {
    double coefficients[6];
    double x0;
    double x1;

    clock_t start, end;
    double cpu_time_used;

    // Parse input coefficients and initial root approximation from command line
    for (int i = 1; i <= 6; i++) {
        coefficients[i-1] = atof(argv[i]);
    }
    x0 = atof(argv[7]);

    start = clock(); // Start measuring the execution time

    // Perform the Newton-Raphson iteration with termination conditions
    int iterations = 0;
    while (iterations < 1000) {
        x1 = newtonRaphson(coefficients, x0);
        if (isnan(x1)) {
            printf("Result: nan\n");
            return 0;
        }
        if (fabs(x1 - x0) < 1e-6) {
            printf("Approximate root: %.2f\n", x1);
            end = clock(); // Stop measuring the execution time
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("Execution time: %f seconds\n", cpu_time_used);
            return 0;
        }
        x0 = x1;
        iterations++;
    }
    printf("Result: incomplete\n");
    end = clock(); // Stop measuring the execution time
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", cpu_time_used);

    return 0;
}