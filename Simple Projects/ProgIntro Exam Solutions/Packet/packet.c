#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MAX_PACKETS 100

// Δομή για να αποθηκεύουμε τα πακέτα
typedef struct {
    char data[MAX_LINE_LENGTH];
    int id;
} Packet;

// Συνάρτηση για σύγκριση πακέτων με βάση το id τους
int compare_packets(const void *a, const void *b) {
    Packet *packet_a = (Packet *)a;
    Packet *packet_b = (Packet *)b;
    return packet_a->id - packet_b->id;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    Packet packets[MAX_PACKETS];
    int count = 0;

    // Ανάγνωση των γραμμών από το αρχείο
    while (fgets(packets[count].data, MAX_LINE_LENGTH, file) != NULL) {
        char *comma_pos = strchr(packets[count].data, ',');
        if (comma_pos != NULL) {
            *comma_pos = '\0';  // Κόβουμε το κόμμα
            packets[count].id = atoi(comma_pos + 1);  // Διαβάζουμε το id
            count++;
        }
        if (count >= MAX_PACKETS) {
            fprintf(stderr, "Error: Too many packets\n");
            fclose(file);
            return EXIT_FAILURE;
        }
    }

    fclose(file);

    // Ταξινόμηση των πακέτων με βάση το id τους
    qsort(packets, count, sizeof(Packet), compare_packets);

    // Εκτύπωση των πακέτων με την ταξινομημένη σειρά
    for (int i = 0; i < count; i++) {
        printf("%s,%d\n", packets[i].data, packets[i].id);
    }

    return EXIT_SUCCESS;
}

// Μεταγλώττιση:
// gcc packet.c -o packet
// Εκτέλεση:
// ./packet unordered.txt