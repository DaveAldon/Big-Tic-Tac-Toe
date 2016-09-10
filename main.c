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

void initializeBoard(int *board);
void printBoard(const int *board);
int hasEmpty(const int *board);
void makeMove(int *board, const int square, const int side);
int findThreeInARowHuman(const int *board, const int ourindex, const int us);
int findThreeInARowComputer(const int *board, const int ourindex, const int us);
int getNumForDirection(int startSq, const int dir, const int *board, const int us);
int getHumanMove(const int *board);
int getComputerMove(const int *board);
void runGame();
int main(void);

enum { empty, nought, cross, border }; //It's good to use enumerators here because these variables all increment from 0
enum { humanwin, computerwin, draw };

const int directions[16] = {
    1,2,3,4,
    6,12,18,24,
    7,14,21,28,
    8,16,24,32};

const int convertTo49[25] = { //Only listing the array values that reside within the borders
    8,9,10,11,12,
    15,16,17,18,19,
    22,23,24,25,26,
    29,30,31,32,33,
    36,37,38,39,40
};

int getNumForDirection(int startSq, const int dir, const int *board, const int us) {
    int found = 0;
    while(board[startSq] != border) {
        if(board[startSq] != us) {
            break;
        }
        found++;
        startSq += dir;
    }
    return found;
}

int findThreeInARowHuman(const int *board, const int ourindex, const int us) {
    int dirIndex = 0;
    int dir = 0;
    int threeCount = 1;
    int i = 0;
    
    for (i = 0; i < 49; i++) {
        if(board[i] == nought) {
            for(dirIndex = 0; dirIndex < 17; ++dirIndex) {
                dir = directions[dirIndex];
                threeCount += getNumForDirection(ourindex + dir, dir, board, i);
                threeCount += getNumForDirection(ourindex + dir * -1, dir * -1, board, i);
                if(threeCount > 3) {
                    printf("%d", threeCount);
                    break;
                }
            }
        }
    }
        return threeCount;
}

int findThreeInARowComputer(const int *board, const int ourindex, const int us) {
    int dirIndex = 0;
    int dir = 0;
    int threeCount = 1;
    int i = 0;
    
    for (i = 0; i < 49; i++) {
        if(board[i] == cross) {
            for(dirIndex = 0; dirIndex < 17; ++dirIndex) {
                dir = directions[dirIndex];
                threeCount += getNumForDirection(ourindex + dir, dir, board, i);
                threeCount += getNumForDirection(ourindex + dir * -1, dir * -1, board, i);
                if(threeCount > 3) {
                    printf("%d", threeCount);
                    break;
                }
            }
        }
    }
    return threeCount;
}

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

int getComputerMove(const int *board) {
    int index = 0;
    int numFree = 0;
    int availableMoves[25];
    int randomMove = 0;
    
    for(index = 0; index < 25; ++index) {
        if(board[convertTo49[index]] == empty) {
            availableMoves[numFree++] = convertTo49[index];
        };
    }
    
    randomMove = (rand() % numFree);
    return availableMoves[randomMove];
}

int getHumanMove(const int *board) {
    char userInput[4]; //4 chars because we'll only receive 2 inputs from user: a number and the enter key
    
    int moveOk = 0;
    int move = -1;
    
    while (moveOk == 0) {
        printf("Enter a number between 1 and 25: ");
        fgets(userInput, 3, stdin);
        fflush(stdin); //Gets rid of extra strings after fgets retrieves the first 3
    
        if(strlen(userInput) != 2) {
            //printf("Invalid input()\n");
            continue; //The continues are necessary in order to not have a segmentation fault. We need to immediately skip to the next iteration of the loop if the condition is met
        }
        
        if(sscanf(userInput, "%d", &move) != 1) {
            move = -1;
            printf("Invalid input\n");
            continue;
        }
        
        if(move < 1 || move > 25) {
            move = -1;
            printf("Invalid range\n");
            continue;
        }
        
        move--;
        
        if(board[convertTo49[move]] != empty) {
            move=-1;
            printf("Not available\n");
            continue;
        }
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
            lastMoveMade = getHumanMove(&board[0]);
            makeMove(&board[0], lastMoveMade, side);
            side = cross;
            
            if(findThreeInARowHuman(board, lastMoveMade, side ^ 1) == 3) {
                printf("Game over\n");
                gameOver = 1;
                if(side == nought) {
                    printf("Human Wins\n");
                }
                else {
                    printf("Computer wins\n");
                }
            }

        }
        else {
            lastMoveMade = getComputerMove(&board[0]);
            makeMove(&board[0], lastMoveMade, side);
            side = nought;
            printBoard(&board[0]);
            
            if(findThreeInARowComputer(board, lastMoveMade, side ^ 1) == 3) {
                printf("Game over\n");
                gameOver = 1;
                if(side == nought) {
                    printf("Human Wins\n");
                }
                else {
                    printf("Computer wins\n");
                }
            }

        }
        
        
        if(!hasEmpty(board)) {
            printf("Game over\n");
            gameOver = 1;
            printf("Draw\n");
        }
    }
    printBoard(&board[0]);
}

int main(void) {
    srand(time(NULL)); //Random seed generation
    runGame();
    
    return 0;
}











