#include <stdio.h>
#include "calendar.h"
#include "date.h"

int main() {
    int year, month, day;
    getCurrentDate(&year, &month, &day);

    printf("Current Date: %d-%02d-%02d\n", year, month, day);

    while (1) {
        printf("Enter year and month (YYYY MM) or year only (YYYY): ");
        char input[10];
        fgets(input, sizeof(input), stdin);

        int count = sscanf(input, "%d %d", &year, &month);
        if (count == 1) {
            displayYearCalendar(year);
        } else if (count == 2) {
            if (year < 1 || month < 1 || month > 12) {
                printf("Invalid date. Try again.\n");
                continue;
            }
            displayCalendar(year, month);
        } else {
            printf("Invalid input. Exiting...\n");
            break;
        }
    }

    return 0;
}
