#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LogEntry {
    char datetime[20]; // Date Format "YYYY-MM-DD HH:MM"
    char message[256];
} LogEntry;

int compareLogEntries(const void *a, const void *b) {
    LogEntry *logA = (LogEntry *)a;
    LogEntry *logB = (LogEntry *)b;
    return strcmp(logA->datetime, logB->datetime);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <logfile>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    LogEntry logs[1000]; // Assume we dont have more than 1000 entries
    int count = 0;

    while (fscanf(file, "%19s : %255[^\n]\n", logs[count].datetime, logs[count].message) == 2) {
        count++;
    }

    fclose(file);

    qsort(logs, count, sizeof(LogEntry), compareLogEntries);

    for (int i = 0; i < count; i++) {
        printf("%s : %s\n", logs[i].datetime, logs[i].message);
    }

    return 0;
}
