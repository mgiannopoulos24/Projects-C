#include <stdio.h>
#include <math.h>
#include "operations.h"
#include "input.h"

int main() {
    char operator;
    double num1, num2, result;

    printf("Enter an operator (+, -, *, /, ^, sqrt, %%, sin, cos, tan): ");
    operator = get_operator();

    if (operator == 's' || operator == 'c' || operator == 't' || operator == 'r') {
        // Single operand operations
        printf("Enter one operand: ");
        get_operand(&num1);

        switch (operator) {
            case 's':
                result = sine(num1);
                printf("sin(%.2lf) = %.2lf\n", num1, result);
                break;
            case 'c':
                result = cosine(num1);
                printf("cos(%.2lf) = %.2lf\n", num1, result);
                break;
            case 't':
                result = tangent(num1);
                printf("tan(%.2lf) = %.2lf\n", num1, result);
                break;
            case 'r':
                if (num1 >= 0) {
                    result = square_root(num1);
                    printf("sqrt(%.2lf) = %.2lf\n", num1, result);
                } else {
                    printf("Error! Square root of a negative number is not real.\n");
                }
                break;
            default:
                printf("Error! Operator is not correct\n");
                break;
        }
    } else {
        // Double operand operations
        printf("Enter two operands: ");
        get_operands(&num1, &num2);

        switch (operator) {
            case '+':
                result = add(num1, num2);
                break;
            case '-':
                result = subtract(num1, num2);
                break;
            case '*':
                result = multiply(num1, num2);
                break;
            case '/':
                if (num2 != 0) {
                    result = divide(num1, num2);
                } else {
                    printf("Error! Division by zero.\n");
                    return 1;
                }
                break;
            case '^':
                result = power(num1, num2);
                break;
            case '%':
                result = modulus((int)num1, (int)num2);
                break;
            default:
                printf("Error! Operator is not correct\n");
                return 1;
        }

        printf("%.2lf %c %.2lf = %.2lf\n", num1, operator, num2, result);
    }

    return 0;
}
