#include <stdio.h>
#include "calendar.h"
#include "date.h"

void displayCalendar(int year, int month) {
    const char *months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    printf("  %s %d\n", months[month - 1], year);
    printf("Su Mo Tu We Th Fr Sa\n");

    int startDay = getStartDayOfMonth(year, month);
    int daysInMonth = getDaysInMonth(year, month);

    for (int i = 0; i < startDay; i++) {
        printf("   ");
    }

    for (int day = 1; day <= daysInMonth; day++) {
        printf("%2d ", day);
        if ((day + startDay) % 7 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

void displayYearCalendar(int year) {
    const char *months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    // Print headers for each row of months
    for (int row = 0; row < 2; row++) {
        for (int col = 0; col < 6; col++) {
            int month = row * 6 + col + 1;
            if (month > 12) {
                break; // Exit loop if all months have been printed
            }
            printf("     %-5s %d   ", months[month - 1], year);
            if (col < 5) {
                printf("  ");
            }
        }
        printf("\n");

        // Print days of the week header for each month
        for (int col = 0; col < 6; col++) {
            if (row == 0) {
                printf("Su Mo Tu We Th Fr Sa  ");
            } else {
                printf("--------------------- ");
            }
            if (col < 5) {
                printf("| ");
            }
        }
        printf("\n");

        // Print days for each month
        int days[6][6][7] = {0};
        int startDays[6];
        int daysInMonths[6];

        for (int col = 0; col < 6; col++) {
            int month = row * 6 + col + 1;
            if (month > 12) {
                break; // Exit loop if all months have been processed
            }
            startDays[col] = getStartDayOfMonth(year, month);
            daysInMonths[col] = getDaysInMonth(year, month);

            int day = 1;
            for (int week = 0; week < 6; week++) {
                for (int weekday = 0; weekday < 7; weekday++) {
                    if (week == 0 && weekday < startDays[col]) {
                        days[col][week][weekday] = 0;
                    } else if (day <= daysInMonths[col]) {
                        days[col][week][weekday] = day++;
                    } else {
                        days[col][week][weekday] = 0;
                    }
                }
            }
        }

        // Print weeks for each month
        for (int week = 0; week < 6; week++) {
            for (int col = 0; col < 6; col++) {
                for (int weekday = 0; weekday < 7; weekday++) {
                    if (days[col][week][weekday] != 0) {
                        printf("%2d ", days[col][week][weekday]);
                    } else {
                        printf("   ");
                    }
                }
                if (col < 5) {
                    printf("|  ");
                }
            }
            printf("\n");
        }

        // Print a horizontal separator between month rows
        if (row < 1) {
            for (int col = 0; col < 6; col++) {
                printf("--------------------- ");
                if (col < 5) {
                    printf("| ");
                }
            }
            printf("\n");
        }
    }
}

int getDaysInMonth(int year, int month) {
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (month == 2 && isLeapYear(year)) {
        return 29;
    } else {
        return daysInMonth[month - 1];
    }
}

int getStartDayOfMonth(int year, int month) {
    // Zeller's Congruence Algorithm to find the day of the week
    if (month < 3) {
        month += 12;
        year -= 1;
    }
    int K = year % 100;
    int J = year / 100;
    int q = 1; // Day of the month
    int m = month;
    int h = (q + (13 * (m + 1)) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;
    return (h + 5) % 7; // Adjusting result to make Sunday = 0, Monday = 1, ...
}

int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
