#include "complexlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Add two complex numbers
Complex complex_add(Complex a, Complex b) {
    Complex result;
    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;
    return result;
}

// Subtract two complex numbers
Complex complex_sub(Complex a, Complex b) {
    Complex result;
    result.real = a.real - b.real;
    result.imag = a.imag - b.imag;
    return result;
}

// Multiply two complex numbers
Complex complex_mul(Complex a, Complex b) {
    Complex result;
    result.real = a.real * b.real - a.imag * b.imag;
    result.imag = a.real * b.imag + a.imag * b.real;
    return result;
}

// Divide two complex numbers
Complex complex_div(Complex a, Complex b) {
    Complex result;
    double denom = b.real * b.real + b.imag * b.imag;
    if (denom == 0.0) {
        // Handle division by zero
        result.real = NAN;
        result.imag = NAN;
        return result;
    }
    result.real = (a.real * b.real + a.imag * b.imag) / denom;
    result.imag = (a.imag * b.real - a.real * b.imag) / denom;
    return result;
}

// Compute the magnitude of a complex number
double complex_abs(Complex a) {
    return sqrt(a.real * a.real + a.imag * a.imag);
}

// Evaluate the polynomial at a complex number
Complex polynomial(Complex z, double *coeffs, int degree) {
    Complex result = {0.0, 0.0};
    Complex z_power = {1.0, 0.0}; // z^0

    for (int i = 0; i <= degree; i++) {
        Complex term = complex_mul(z_power, (Complex){coeffs[i], 0.0});
        result = complex_add(result, term);
        z_power = complex_mul(z_power, z);
    }

    return result;
}

// Derivative of the polynomial at a complex number
Complex polynomial_derivative(Complex z, double *coeffs, int degree) {
    Complex result = {0.0, 0.0};
    Complex z_power = {1.0, 0.0}; // z^0

    for (int i = 1; i <= degree; i++) {
        Complex term = complex_mul((Complex){coeffs[i] * i, 0.0}, z_power);
        result = complex_add(result, term);
        z_power = complex_mul(z_power, z);
    }

    return result;
}

// Newton-Raphson step function
Complex newton_raphson_step(Complex z, double *coeffs, int degree) {
    Complex fz = polynomial(z, coeffs, degree);
    Complex fz_prime = polynomial_derivative(z, coeffs, degree);

    // Check for division by zero
    if (complex_abs(fz_prime) < TOLERANCE) {
        Complex result = {NAN, NAN};
        return result;
    }

    return complex_sub(z, complex_div(fz, fz_prime));
}

// Print a complex number in the desired format
void print_complex(Complex z) {
    if (z.real >= 0) {
        printf("+%.2f", z.real);
    } else {
        printf("%.2f", z.real);
    }

    if (z.imag >= 0) {
        printf("+%.2fi", z.imag);
    } else {
        printf("%.2fi", z.imag);
    }
}

// Find roots using Newton-Raphson method for a range of complex numbers
void find_roots(double *coeffs, int degree, Complex min, Complex max, double step) {
    int first = 1; // Flag to handle the first print of each line

    for (double real = min.real; real <= max.real; real += step) {
        for (double imag = min.imag; imag <= max.imag; imag += step) {
            Complex z = {real, imag};
            Complex z_next = z;
            int iter;

            for (iter = 0; iter < MAX_ITER; iter++) {
                z_next = newton_raphson_step(z, coeffs, degree);
                if (isnan(z_next.real) || isnan(z_next.imag)) {
                    if (!first) {
                        printf(" ");
                    }
                    printf("nan");
                    break;
                }
                if (complex_abs(complex_sub(z_next, z)) < TOLERANCE) {
                    if (!first) {
                        printf(" ");
                    }
                    print_complex(z_next);
                    break;
                }
                z = z_next;
            }

            if (iter == MAX_ITER) {
                if (!first) {
                    printf(" ");
                }
                printf("incomplete");
            }
            first = 0; // After the first print
        }
        printf("\n");
        first = 1; // Reset flag for the next row
    }
}

// Parse the input file and extract polynomial coefficients, degree, and search window
void parse_input(const char *filename, double **coeffs, int *degree, Complex *min, Complex *max, double *step) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(1);
    }

    // Read the degree of the polynomial
    if (fscanf(file, "%d", degree) != 1) {
        fprintf(stderr, "Failed to read polynomial degree\n");
        fclose(file);
        exit(1);
    }

    // Allocate memory for coefficients
    *coeffs = malloc((*degree + 1) * sizeof(double));
    if (*coeffs == NULL) {
        perror("Failed to allocate memory for coefficients");
        fclose(file);
        exit(1);
    }

    // Read polynomial coefficients
    for (int i = 0; i <= *degree; i++) {
        if (fscanf(file, "%lf", &(*coeffs)[i]) != 1) {
            fprintf(stderr, "Failed to read coefficient at index %d\n", i);
            free(*coeffs);
            fclose(file);
            exit(1);
        }
    }

    // Read the min and max complex numbers and the step value
    if (fscanf(file, "%lf %lf %lf %lf %lf", &min->real, &min->imag, &max->real, &max->imag, step) != 5) {
        fprintf(stderr, "Failed to read search window and step values\n");
        free(*coeffs);
        fclose(file);
        exit(1);
    }

    fclose(file);
}