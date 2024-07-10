#include <time.h>
#include "date.h"

void getCurrentDate(int *year, int *month, int *day) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    *year = tm.tm_year + 1900;
    *month = tm.tm_mon + 1;
    *day = tm.tm_mday;
}
