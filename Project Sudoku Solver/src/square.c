#include "sudoku.h"

int solveSquare(Square * square){
    int i;
    
    for (i=0; i<SIZE_ROWS; i++)
    {
        if (square -> possible[i] == 0)
        {
            square->number = i + 1;
            square->solvable=0;
            UNSOLVED--;
        }
    }
}