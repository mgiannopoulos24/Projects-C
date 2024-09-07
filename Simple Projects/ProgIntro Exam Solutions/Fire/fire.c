#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];

    // Διαβάστε από την πρότυπη είσοδο μέχρι το τέλος του αρχείου
    while (fgets(buffer, sizeof(buffer), stdin)) {
        // Εκτύπωση του εικονίδιου φωτιάς ακολουθούμενου από κενό και το περιεχόμενο της γραμμής
        printf("🔥 %s", buffer);
    }

    return 0;
}
