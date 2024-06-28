#include "sudoku.h"

int checkRows(Square *** sudoku, Box ** boxes)
{
    int i, j, k;
    int sum[9];
    int place[9];

    // Loop through rows
    for (i = 0; i < 9; i++){

        // Initialize sum and place
        for (j = 0; j < 9; j++){
            place[j] = 0;
            sum[j] = 0;
        }
        // Loop through each square in the row
        for (j =0; j < 9; j++){
            if (sudoku[i][j]->number != 0)
            {
                continue;
            }

            // Loop through all possibilities
            for (k = 0; k < 9; k++)
            {   
                //Check if number possible
                if (sudoku[i][j]->possible[k] == 0){
                    sum[k]++;
                    place[k]=j;
                }


            }
        }

        for (k = 0; k < 9; k++){
            if(sum[k] == 1){
                sudoku[i][place[k]]->number= k + 1;
                sudoku[i][place[k]]->solvable=0;
                UNSOLVED--;

                updateSudoku(sudoku, i, place[k]);
                updateBoxes(sudoku, i, place[k]);

                return 1;
            }
        }
    }
    return 0;
}