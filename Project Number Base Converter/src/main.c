#include <stdio.h>
#include <stdlib.h>
#include "converter.h"

int main() {
    int choice;
    int decimal;
    char binary[33];
    char octal[12];
    char hex[20]; // Allow for reasonably large hexadecimal inputs

    while (1) {
        printf("\nNumber System Conversion Menu:\n");
        printf("1. Decimal to Binary\n");
        printf("2. Binary to Decimal\n");
        printf("3. Decimal to Octal\n");
        printf("4. Octal to Decimal\n");
        printf("5. Hexadecimal to Binary\n");
        printf("6. Binary to Hexadecimal\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter a decimal number: ");
                scanf("%d", &decimal);
                printf("Binary equivalent: %s\n", decimalToBinary(decimal));
                break;
            case 2:
                printf("Enter a binary number: ");
                scanf("%s", binary);
                printf("Decimal equivalent: %d\n", binaryToDecimal(binary));
                break;
            case 3:
                printf("Enter a decimal number: ");
                scanf("%d", &decimal);
                printf("Octal equivalent: %s\n", decimalToOctal(decimal));
                break;
            case 4:
                printf("Enter an octal number: ");
                scanf("%s", octal);
                printf("Decimal equivalent: %d\n", octalToDecimal(octal));
                break;
            case 5:
                printf("Enter a hexadecimal number: ");
                scanf("%s", hex);
                printf("Binary equivalent: %s\n", hexadecimalToBinary(hex));
                break;
            case 6:
                printf("Enter a binary number: ");
                scanf("%s", binary);
                printf("Hexadecimal equivalent: %s\n", binaryToHexadecimal(binary));
                break;
            case 7:
                printf("Exiting...\n");
                exit(EXIT_SUCCESS);
            default:
                printf("Invalid choice. Please enter a number between 1 and 7.\n");
                break;
        }
    }

    return 0;
}
