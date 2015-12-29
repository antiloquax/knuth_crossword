/* 
 * Knuth TAOCP, Volume 1.
 * Section 1.3.2 ex. 23. Crossword printing. 
 */

#include<stdio.h>
#include<string.h>
/* NB. use -lm when compiling. */
#include<math.h>

/* Number of  user inputted rows, plus 2 to allow for border of -1s. */
#define NROWS (6 + 2)


void blank(int puzzle[][NROWS], int row, int col);

int main(void)
{
    /* Loop counters. */
    int i, j;
    const int LIM = NROWS - 1;

    int xword[NROWS][NROWS];
    int cellValue;
    int clueNum;
    int cellHeight;
    int row, col;
    char ch;
    char *blackRow  = "+++++";
    char *numRow    = "%02d  +";
    char *borderRow = "    +";
    char *emptyRow  = "     ";

    /* 
     * Add -1s around the border of the pattern.
     * Visits corner squares twice, but is simpler this way.
     */
    for(i = 0; i < NROWS; i++)
        xword[0][i] = xword[LIM][i] = xword[i][0] = xword[i][LIM] = -1;

    /* Get user data. */
    printf("*** Knuth Crossword Exercise. ***\n\n");
    printf("Please enter %d rows of %d numbers.\n", NROWS - 2, NROWS - 2);
    printf("Separate with single spaces.\n");

    /* Get the user's numbers and populate the array. */
    for(row = 1; row < LIM; row++){
        col = 1;
        printf("\nRow %d: ", row);
        while((ch = getchar()) != '\n'){
            if(ch == '1' || ch == '0')
                xword[row][col++] = ch - '0';
        }
        if(col != LIM){
            printf("Input error.\n");
            return 1;
        }
    }
 
    /* Replace all 1s next to -1s with -1. */
    for(j = 1; j < ceil(NROWS / 2.0); j++)
        for(i = j; i < NROWS-j; i++){
            blank(xword, j, i);
            blank(xword, (LIM) - j, i);
            blank(xword, i, j);
            blank(xword, i, (LIM) - j);
        }     

    /* Print the actual puzzle. */
    printf("\n");
    for(row = 0, clueNum = 1; row < NROWS; row++){
        /* Each cell is three rows high. */
        for(cellHeight = 0; cellHeight < 3; cellHeight++) {
            /* Don't print unnecessary top and bottom rows. */
            if ((cellHeight && row == LIM) || (cellHeight < 2 && !row))
               continue; 
            printf("\n");
            for(col = 0; col < NROWS; col++){
                cellValue = xword[row][col];

                /* Black squares. */
                if(cellValue == 1){
                    printf("%s", blackRow);
                    
                /* White squares follow. */
                } else if (!cellValue){
                    /* Bottom row of a white cell needs a "black row". */
                    if (cellHeight == 2) {
                        printf("%s", blackRow);
                    /* Print a number in the square. */
                    } else if (!cellHeight &&
                             /* If cell below is white and cell below is black. */
                            ((!xword[row+1][col] && xword[row-1][col])
                            /* If cell to the right is white and cell to left is black. */
                             || (!xword[row][col+1] && xword[row][col-1]))) {
                        printf(numRow, clueNum++);
                    } else 
                        /* Otherwise, white squares just need a '+' at the end. */ 
                        printf("%s", borderRow);

                /* Deal with -1 squares. Ignore bottom row and rightmost column. */
                } else if (row != LIM && col != LIM){
                    /* Rules for rows 1 & 2. */
                    if (cellHeight < 2){
                        /* Print the final '+' if the square to the right is white. */
                        if(!xword[row][col+1])
                            printf("%s", borderRow);
                        /* Print an empty row if the cell to the right is also -1. */
                        else
                            printf("%s", emptyRow);
                    /* Rules for row 0. Add the "black row" if the cell below is white. */
                    } else if (!xword[row+1][col]){
                        printf("%s", blackRow);
                    /* Print the final '+' if cell to the right or down-and-right is white. */
                    } else if(!xword[row][col+1] || !xword[row+1][col+1]){
                        printf("%s", borderRow);
                    /* Otherwise print empty row. */
                    } else {
                        printf("%s", emptyRow);
                    }
                }
            }
        }
    }
    printf("\n");
    return 0;
}

/* 
 * Takes the array that represents the puzzle, and a cell's location.
 * Turns it to a blank square (-1) if it is black (1) and 
 * any of its neighbours is blank.
 */

void blank(int puzzle[][NROWS], int r, int c)
{
    /* Do nothing if the cell holds 0 or -1. */
    if(puzzle[r][c] < 1)
        return;
    if(puzzle[r-1][c] == -1 
            || puzzle[r+1][c] == -1 
            || puzzle[r][c-1] == -1 
            || puzzle[r][c+1] == -1)
        puzzle[r][c] = -1;
}

