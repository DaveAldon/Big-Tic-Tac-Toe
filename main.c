#include <stdio.h>

/* What the board theoretically looks like to the human mind. This is useful for me to keep track of what I'm laying out.
 ; ; ; ; ; ; ;
 ; 0 0 0 0 0 ;
 ; 0 0 0 0 0 ;
 ; 0 0 0 0 0 ;
 ; 0 0 0 0 0 ;
 ; 0 0 0 0 0 ;
 ; ; ; ; ; ; ;
 */

enum { empty, nought, cross, border }; //It's good to use enumerators here because these variables all increment from 0

const int convertTo48[25] = { //Only listing the array values that reside within the borders
    8,9,10,11,12,
    15,16,17,18,19,
    22,23,24,25,26,
    29,30,31,32,33,
    36,37,38,39,40
};

void initializeBoard(int *board) {
    int i = 0;
    
    for (i = 0; i < 49; ++i) { //Sets everything to a border first
        board[i] = border;
    }
    
    for (i = 0; i < 25; ++i) { //Then it filters out what is in-between
        board[convertTo48[i]] = empty;
    }
}

void printBoard(const int *board) {
    int i = 0;
    
    printf("\nBoard:\n");
    
    for (i = 0; i < 49; ++i) {
        if(i!=0 && i%7==0) { //Print a new line everytime we reach the end of a theoretical row
            printf("\n");
        }
        printf("%4d", board[i]);
    }
    printf("\n");
}

int main(void) {
    int board[49];
    initializeBoard(&board[0]);
    printBoard(&board[0]);
    
    return 0;
}