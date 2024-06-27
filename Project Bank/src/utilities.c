#include <stdio.h>
#include <stdlib.h>

void clearInputBuffer() {
    while (getchar() != '\n');
}

void clearScreen() {
    system("clear"); // For Linux/Unix
    //system("cls"); // For Windows
}
