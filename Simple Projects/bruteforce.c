#include <stdio.h>
#include <stdbool.h>

//Bruteforce until we find the correct 4-digit PIN
bool checkPIN(int pin);

int main() {
    int pin;
    for (pin = 0; pin <= 9999; pin++) {
        if (checkPIN(pin)) {
            printf("Access granted. The PIN is: %04d\n", pin);
            return 0;
        }
    }

    printf("Access denied. The PIN was not found.\n");
    return 1;
}
