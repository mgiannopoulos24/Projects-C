#ifndef COMPLEXLIB_H
#define COMPLEXLIB_H

#define MAX_ITER 1000
#define TOLERANCE 1e-6

// Define a complex number structure
typedef struct {
    double real;
    double imag;
} Complex;

// Function prototypes
Complex complex_add(Complex a, Complex b);
Complex complex_sub(Complex a, Complex b);
Complex complex_mul(Complex a, Complex b);
Complex complex_div(Complex a, Complex b);
double complex_abs(Complex a);
Complex polynomial(Complex z, double *coeffs, int degree);
Complex polynomial_derivative(Complex z, double *coeffs, int degree);
Complex newton_raphson_step(Complex z, double *coeffs, int degree);
void find_roots(double *coeffs, int degree, Complex min, Complex max, double step);
void parse_input(const char *filename, double **coeffs, int *degree, Complex *min, Complex *max, double *step);

#endif // COMPLEXLIB_H
