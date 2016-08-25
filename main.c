#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

const int convertTo49[25] = { //Only listing the array values that reside within the borders
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
        board[convertTo49[i]] = empty;
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

int hasEmpty(const int *board) {
    int i = 0;
    int empty = 0;
    
    for(i = 0; i < 25; ++i) {
        if(board[convertTo49[i]] == empty)
            return 1;
    }
    return 0;
}

void makeMove(int *board, const int square, const int side) {
    board[square] = side;
}


int getHumanMove(const int *board) {
    char userInput[4]; //4 chars because we'll only receive 2 inputs from user: a number and the enter key
    
    int moveOk = 0;
    int move = -1;
    
    while (moveOk == 0) {
        printf("Enter a number between 1 and 25: ");
        fgets(userInput, 3, stdin);
        fflush(stdin); //Gets rid of extra strings after fgets retreives the first 3
        moveOk = 1;
    }
    
    printf("Making move...%d\n", (move + 1));
    return convertTo49[move];
}

void runGame() {
    int gameOver = 0;
    int side = nought;
    int lastMoveMade = 0;
    int board[49];
    
    initializeBoard(&board[0]);
    printBoard(&board[0]);
    
    while(!gameOver) {
        if(side==nought) {
            getHumanMove(&board[0]);
        }
        else {
            printBoard(&board[0]);
        }
        
        gameOver = 1;
    }
}

int main(void) {
    
    srand(time(NULL)); //Random seed generation
    runGame();
    
    return 0;
}











