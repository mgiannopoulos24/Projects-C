#include "dice.h"
#include <stdlib.h>
#include <time.h>

int rollDice() {
    srand(time(NULL));
    return (rand() % 6) + 1;
}
