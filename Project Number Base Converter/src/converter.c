#include "converter.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


// Function to reverse a string
void strrev(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; ++i) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

// Function to convert decimal to binary
char* decimalToBinary(int decimal) {
    char* binary = (char*)malloc(33 * sizeof(char)); // Room for 32 bits + '\0'
    if (binary == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    int index = 0;
    if (decimal == 0) {
        binary[index++] = '0';
    } else {
        while (decimal > 0) {
            binary[index++] = (decimal % 2) + '0';
            decimal /= 2;
        }
    }
    binary[index] = '\0';
    strrev(binary); // Reverse the string to get correct binary representation
    return binary;
}

// Function to convert binary to decimal
int binaryToDecimal(const char* binary) {
    int decimal = 0;
    int len = strlen(binary);

    for (int i = 0; i < len; ++i) {
        decimal = decimal * 2 + (binary[i] - '0');
    }

    return decimal;
}

// Function to convert decimal to octal
char* decimalToOctal(int decimal) {
    char* octal = (char*)malloc(12 * sizeof(char)); // Room for 11 digits + '\0'
    if (octal == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    int index = 0;
    while (decimal > 0) {
        octal[index++] = (decimal % 8) + '0';
        decimal /= 8;
    }
    octal[index] = '\0';
    strrev(octal); // Reverse the string to get correct octal representation
    return octal;
}

// Function to convert octal to decimal
int octalToDecimal(const char* octal) {
    int decimal = 0;
    int len = strlen(octal);

    for (int i = 0; i < len; ++i) {
        decimal = decimal * 8 + (octal[i] - '0');
    }

    return decimal;
}

// Function to convert hexadecimal to binary
char* hexadecimalToBinary(const char* hex) {
    // Initialize a lookup table for hexadecimal to binary conversion
    const char* hexToBin[16] = {
        "0000", "0001", "0010", "0011",
        "0100", "0101", "0110", "0111",
        "1000", "1001", "1010", "1011",
        "1100", "1101", "1110", "1111"
    };

    int len = strlen(hex);
    char* binary = (char*)malloc((4 * len + 1) * sizeof(char)); // Each hex digit is 4 bits
    if (binary == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    binary[0] = '\0'; // Start with an empty string

    // Convert each hexadecimal digit to binary and concatenate
    for (int i = 0; i < len; ++i) {
        if (hex[i] >= '0' && hex[i] <= '9') {
            strcat(binary, hexToBin[hex[i] - '0']);
        } else if (hex[i] >= 'A' && hex[i] <= 'F') {
            strcat(binary, hexToBin[hex[i] - 'A' + 10]);
        } else if (hex[i] >= 'a' && hex[i] <= 'f') {
            strcat(binary, hexToBin[hex[i] - 'a' + 10]);
        } else {
            fprintf(stderr, "Invalid hexadecimal digit '%c'\n", hex[i]);
            free(binary);
            exit(EXIT_FAILURE);
        }
    }

    return binary;
}

// Function to convert binary to hexadecimal
char* binaryToHexadecimal(const char* binary) {
    int len = strlen(binary);
    if (len % 4 != 0) {
        fprintf(stderr, "Binary length must be a multiple of 4\n");
        exit(EXIT_FAILURE);
    }

    static const char* binToHex[16] = {
        "0", "1", "2", "3",
        "4", "5", "6", "7",
        "8", "9", "A", "B",
        "C", "D", "E", "F"
    };

    int numGroups = len / 4;
    char* hex = (char*)malloc((numGroups + 1) * sizeof(char)); // Each group of 4 bits forms one hex digit
    if (hex == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numGroups; ++i) {
        int sum = 0;
        for (int j = 0; j < 4; ++j) {
            sum = sum * 2 + (binary[i * 4 + j] - '0');
        }
        hex[i] = binToHex[sum][0]; // Assign the first character of the hexadecimal string
    }
    hex[numGroups] = '\0';
    return hex;
}