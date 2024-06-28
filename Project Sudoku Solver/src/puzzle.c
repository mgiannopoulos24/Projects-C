#include "sudoku.h"

Sudoku * createSudoku(Square *** squares, Box ** boxes){
    Sudoku * sudoku;
    sudoku = malloc(sizeof(Sudoku));

    sudoku->squares = squares;
    sudoku-> boxes = boxes;

    return sudoku;
}

Sudoku * setUpPuzzle(int ** puzzle){
    Square *** sudoku;
    Box ** boxes;
    int i, j, k;
    int currentBox=0;

    sudoku = (Square ***)malloc(sizeof(Square **) * 9);
    boxes = createBoxes();

    // Create the 9x9 sudoku board
    for (i=0; i<SIZE_ROWS; i++)
    {   
        sudoku[i] = (Square **)malloc(sizeof(Square *) * 9);

        // Create each square in the board
        for (j=0; j<SIZE_COLUMNS; j++)
        {   
            sudoku[i][j] = (Square *)malloc(sizeof(Square *) * 9);
            sudoku[i][j] -> number = puzzle[i][j];  
            sudoku[i][j] -> row = i;
            sudoku[i][j] -> column = j;
            sudoku[i][j] -> solvable = 9;


            boxes[currentBox]->squares[boxes[currentBox]->numbers] = sudoku[i][j];
            sudoku[i][j]->box = boxes[currentBox];
            boxes[currentBox]->numbers++;

            for (k=0; k<SIZE_ROWS; k++)
            {
                sudoku[i][j] -> possible[k] = 0;
            }

            if (j == 2){
                currentBox++;
            }

            if (j == 5){
                currentBox++;
            }
        }

        currentBox -= 2;
        if (i == 2){
            currentBox = 3;
        }
        if (i == 5){
            currentBox = 6;
        }
    }

    for (i=0; i<SIZE_ROWS; i++)
    {   
        // Create each square in the board
        for (j=0; j<SIZE_COLUMNS; j++)
        {
            if (sudoku[i][j] -> number != 0)
            {
                sudoku[i][j] -> solvable = 0;
                updateSudoku(sudoku, i, j);
                updateBoxes(sudoku, i, j);
                UNSOLVED--;
            }
        }
    }

    return createSudoku(sudoku, boxes);
}

int updateSudoku(Square *** sudoku, int row, int column){
    int k;
    int number = sudoku[row][column] -> number;

    for (k=0; k<SIZE_ROWS; k++)
    {
        if (sudoku[k][column] -> possible[number -1] == 0)
        {
            sudoku[k][column] -> solvable--;
        }
        sudoku[k][column] -> possible[number - 1] = 1;
    }

    for (k=0; k<SIZE_COLUMNS; k++)
    {
        if (sudoku[row][k] -> possible[number -1] == 0)
        {
            sudoku[row][k] -> solvable--;
        }
        sudoku[row][k] -> possible[number - 1] = 1;
    }

    return 1;
}

int checkPuzzle(Square *** sudoku, Box ** boxes){
    int i, j, k;

    for (i=0; i<SIZE_ROWS; i++)
    {   

        // Create each square in the board
        for (j=0; j<SIZE_COLUMNS; j++)
        {
            if (sudoku[i][j] -> solvable == 1)
            {
                solveSquare(sudoku[i][j]);
                updateSudoku(sudoku, i, j);
                updateBoxes(sudoku, i, j);

                return 1;
            }
        }
    }

    if (boxSingles(sudoku, boxes)){
        return 1;
    }

    return checkRows(sudoku, boxes);
}



int ** createPuzzle()
{
    int ** puzzle;
    int i, j;   
    int array[9][9]={0,1,9, 0,0,2, 0,0,0,
                     4,7,0, 6,9,0, 0,0,1,
                     0,0,0, 4,0,0, 0,9,0,

                     8,9,4, 5,0,7, 0,0,0,
                     0,0,0, 0,0,0, 0,0,0,
                     0,0,0, 2,0,1, 9,5,8,

                     0,5,0, 0,0,6, 0,0,0,
                     6,0,0, 0,2,8, 0,7,9,
                     0,0,0, 1,0,0, 8,6,2};

    puzzle = (int**)malloc(sizeof(int *) * 9);

    for (i=0; i<9; i++)
    {
        puzzle[i] = (int*)malloc(sizeof(int) * 9);
        for (j=0; j<9; j++)
        {
            puzzle[i][j] = array[i][j];
        }
    }

    return puzzle;
}

void printPuzzle(Square *** puzzle)
{
    int i, j;

    printf("-------------------------\n");
    for (i=0; i<SIZE_ROWS; i++)
    {   
        printf("| ");
        // Print each row of the puzzle
        for (j=0; j<SIZE_COLUMNS; j++)
        {
            printf("%d ", puzzle[i][j] -> number);

            if ((j+1) % 3 == 0)
            {
                printf("| ");
            }

        }
        printf("\n");

        if ((i+1) % 3 == 0)
        {
            printf("-------------------------\n");
        }
    }
}