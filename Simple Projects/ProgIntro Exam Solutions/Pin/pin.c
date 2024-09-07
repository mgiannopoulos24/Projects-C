#include <stdio.h>
#include <stdlib.h>

// Δηλώση εξωτερικής συνάρτησης που ελέγχει το PIN
int check_pin(int pin) {
    // Για παράδειγμα, αν το σωστό PIN είναι 1234:
    return pin == 1234;
}

int main() {
    int pin;
    for (pin = 0; pin <= 9999; pin++) {
        if (check_pin(pin) == 1) {
            printf("The correct PIN is: %04d\n", pin);
            break;
        }
    }
    return 0;
}

// Μεταγλώττιση:
// gcc pin.c -o pin
// Δοκιμές:
// ./pin