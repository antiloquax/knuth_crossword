#include<stdio.h>
#include<string.h>
/* NB. use -lm when compiling. */
#include<math.h>

/* Number of  user inputted rows, plus 2. */
#define NROWS (6 + 2)

/* Section 1.3.2 ex. 23. Crossword printing. */

void blank(int p[][NROWS], int r, int c);

int main(void)
{
    int xword[NROWS][NROWS];
    int i, j, k, n, r, l, t;
    char c;
    char *bl  = "+++++";
    char *num = "%02d  +";
    char *a   = "    +";
    char *cl  = "     ";

    /* Add -1s around the border of the pattern. */
    for(i = 0; i < NROWS; i++){
        xword[0][i] = -1;
        xword[NROWS-1][i] = -1;
        xword[i][0] = -1;
        xword[i][NROWS-1] = -1;
    }

    /* Get user data. */
    printf("*** Knuth Crossword Exercise. ***\n\n");
    printf("Please enter %d rows of %d numbers.\n", NROWS - 2, NROWS - 2);
    printf("Separate with single spaces.\n");

    for(i = 1; i < NROWS-1; i++){
        j = 1;
        printf("\nRow %d: ", i);
        while((c = getchar()) != '\n'){
            if(c == '1' || c == '0')
                xword[i][j++] = c - '0';
        }
        if(j != NROWS-1){
            printf("Input error.\n");
            return 1;
        }
    }
 
    /* Replace all 1s next to -1s with -1. */
    for(j = 1; j < ceil(NROWS / 2.0); j++)
        for(i = j; i < NROWS-j; i++){
            blank(xword, j, i);
            blank(xword, (NROWS - 1) - j, i);
            blank(xword, i, j);
            blank(xword, i, (NROWS - 1) - j);
        }     

    /* Print the actual puzzle. */
    printf("\n");
    for(r = 0, n = 1; r < NROWS; r++){
        /* Each cell is three rows high. */
        for(k = 0; k < 3; k++) {
            /* Don't bother with unnecessary top and bottom bits. */
            if ((k && r == NROWS - 1) || (k < 2 && !r))
               continue; 
            printf("\n");
            for(l = 0; l < NROWS; l++){
                t = xword[r][l];
                
                /* Black squares are simple. */
                if(t == 1){
                    printf("%s", bl);
                    
                /* White squares follow. */
                } else if (!t){
                    if (k == 2) {
                        printf("%s", bl);
                    /* Print a number in the square. */
                    } else if (!k && ((!xword[r+1][l] && xword[r-1][l]) ||
                            (!xword[r][l+1] && xword[r][l-1]))) {
                        printf(num, n++);
                    } else 
                        printf("%s", a);

                    /* Deal with -1 squares. */
                } else if (r != NROWS - 1 && l != NROWS - 1){
                    if (!k || k == 1){
                        if(!xword[r][l+1])
                            printf("%s", a);
                        else
                            printf("%s", cl);
                    } else if (!xword[r+1][l]){
                        printf("%s", bl);
                    } else if(!xword[r][l+1] || !xword[r+1][l+1]){
                        printf("%s", a);
                    } else {
                        printf("%s", cl);
                    }
                }
            }
        }
    }
    printf("\n");
    return 0;
}

void blank(int p[][NROWS], int r, int c)
{
    /* Do nothing if the cell holds 0 or -1. */
    if(p[r][c] < 1)
        return;
    if(p[r-1][c] == -1 || p[r+1][c] == -1 || 
            p[r][c-1] == -1 || p[r][c+1] == -1)
        p[r][c] = -1;
    return;
}

