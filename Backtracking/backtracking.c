#include <stdio.h>
#include <stdlib.h>

#define TRUE (1 == 1)
#define FALSE (1 == 0)
#define EMPTY 0


// size of output board
int size;

// output board
int **board;

// input options board
int ***options;

// functions taken from sudoku practice problem
void readBoard();
void printBoard();
int isValid();
int backTrack(int, int);

int main()
{
    // take in input for size
    scanf("%d", &size);

    // allocate memory for board output
    board = (int **)calloc(size, sizeof(int *));
    for (int i = 0; i < size; i++)
    {
        board[i] = (int *)calloc(size, sizeof(int));

        // initilize board to all empty
        for (int j = 0; j < size; j++)
            board[i][j] = 0;
    }

    // allocate input options board
    options = (int ***)calloc(size, sizeof(int **));
    for (int i = 0; i < size; i++)
    {
        options[i] = (int **)calloc(size, sizeof(int *));
        for (int j = 0; j < size; j++)
            options[i][j] = (int *)calloc(3, sizeof(int));
    }

    // read input options board
    readBoard();

    // if bakctrack doesn't return false, print the output board
    if (backTrack(0, 0))
    {
        printBoard();
    }

    return 0;
}

int isValid()
{
    int row, col, subRow, subCol, value, r, c;

    // Check each row
    for (row = 0; row < size; row++)
    {
        // Set that no value exists
        int contains[size];
        for (value = 0; value < size; value++)
        {
            contains[value] = FALSE;
        }

        // Loop through the row
        for (col = 0; col < size; col++)
        {
            // Check if a value is present
            if (board[row][col] != EMPTY)
            {
                // Check if the value is already in the row
                if (contains[board[row][col] - 1])
                {
                    return FALSE;
                }

                // Set the value is in the row
                contains[board[row][col] - 1] = TRUE;
            }
        }
    }

    // Check each column
    for (col = 0; col < size; col++)
    {
        // Set that no value exists
        int contains[size];
        for (value = 0; value < size; value++)
        {
            contains[value] = FALSE;
        }

        // Loop through the column
        for (row = 0; row < size; row++)
        {
            // Check if a value is present
            if (board[row][col] != EMPTY)
            {
                // Check if the value is already in the row
                if (contains[board[row][col] - 1])
                {
                    return FALSE;
                }

                // Set the value is in the row
                contains[board[row][col] - 1] = TRUE;
            }
        }
    }

    // No invalid row, column, or nonet was found
    return TRUE;
}

int backTrack(int r, int c)
{
    // THIS IS BACKTRACKING : Check validity
    if (!isValid())
    {
        return FALSE;
    }

    // Check if col index (c) is off the board
    if (c == size)
    {
        return backTrack(r + 1, 0);
    }

    // Check if row index (r) is off the board
    if (r == size)
    {
        return TRUE;
    }

    // Check if forced
    if (board[r][c] != 0)
    {
        return backTrack(r, c + 1);
    }

    // Try all possible decisions
    int attempt;
    for (attempt = 0; attempt < 3; attempt++)
    {
        board[r][c] = options[r][c][attempt];
        if (backTrack(r, c + 1))
            return TRUE;

        // Undo the choice
        board[r][c] = EMPTY;
    }

    // No solution found
    return FALSE;
}

void printBoard()
{
    int i, j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
            printf("%d ", board[i][j]);
        printf("\n");
    }
}

void readBoard()
{
    int i, j, k;
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            for (k = 0; k < 3; k++)
                scanf("%d", &options[i][j][k]);
}
