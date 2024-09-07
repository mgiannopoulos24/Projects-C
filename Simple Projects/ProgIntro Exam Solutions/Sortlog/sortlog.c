#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Δομή για αποθήκευση μιας εγγραφής καταγραφής
typedef struct {
    char datetime[20];
    char message[256];
} LogEntry;

// Συνάρτηση συγκρίσης για τη συνάρτηση qsort
int compare(const void *a, const void *b) {
    return strcmp(((LogEntry*)a)->datetime, ((LogEntry*)b)->datetime);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <logfile>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    LogEntry entries[1000];
    int count = 0;

    // Διαβάστε το αρχείο και αποθηκεύστε τις εγγραφές
    while (fgets(entries[count].datetime, sizeof(entries[count].datetime), file)) {
        // Αφαιρέστε το νέο χαρακτήρα της γραμμής
        size_t len = strlen(entries[count].datetime);
        if (len > 0 && entries[count].datetime[len - 1] == '\n') {
            entries[count].datetime[len - 1] = '\0';
        }

        // Αντιγράψτε το μήνυμα της καταγραφής
        if (fgets(entries[count].message, sizeof(entries[count].message), file)) {
            // Αφαιρέστε το νέο χαρακτήρα της γραμμής
            len = strlen(entries[count].message);
            if (len > 0 && entries[count].message[len - 1] == '\n') {
                entries[count].message[len - 1] = '\0';
            }
        }

        count++;
    }

    fclose(file);

    // Ταξινομήστε τις εγγραφές με βάση την ημερομηνία και την ώρα
    qsort(entries, count, sizeof(LogEntry), compare);

    // Εκτυπώστε τις ταξινομημένες εγγραφές
    for (int i = 0; i < count; i++) {
        printf("%s%s\n", entries[i].datetime, entries[i].message);
    }

    return 0;
}

// Μεταγλώττιση:
// gcc sortlog.c -o sortlog
// Δοκιμές:
// ./sortlog logs.txt