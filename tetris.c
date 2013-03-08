/*
 * Bailey Forrest - bcforres
 * baileycforrest@gmail.com
 *
 * tetris.c
 * 
 * Main control loop for tetris
 *
 */

#include "tetris.h"

static board *mainBoard = NULL;
static piece *fallingPiece = NULL;
static piece *nextPiece = NULL;
static int score;
static int lines;

int main()
{
    for(;;)
    {
        if(initGame() < 0)
            exit(1);

        if(runGame()) break;
    }

    cleanUp();
    return 0;
}

int initGame()
{
    score = 0;
    lines = 0;

    if(mainBoard != NULL)
        freeBoard(mainBoard);

    if(initInter() < 0)
        return -1;
    
    if((mainBoard = createBoard()) == NULL)
        return -1;

    if(fallingPiece == NULL)
        fallingPiece = newPiece(mainBoard);
    
    if(nextPiece == NULL)
        nextPiece = newPiece(mainBoard);

    // seed random number generator
    srand(time(NULL));

    return 0;
}

int delayMili(int delay)
{
    static struct timespec tim1, tim2;
    tim1.tv_sec = 0;
    tim1.tv_nsec = 1000000;

    int i;
    for(i = 0; i < delay; i++)
        nanosleep(&tim1, &tim2);

    return 0;
}

int runGame()
{
    //int delay = 250;

    for(;;)
    {
        if(handleInput(getInput()))
            return 1;
        displayBoard(mainBoard, fallingPiece, nextPiece);
        displayStats(score, lines);
    }
    
    return 0;
}

inline void dropPiece(piece *p)
{
    while(moveDown(p));
}

// Tries to move a piece down, if it can't place it, get new piece
// returns true if piece placed sucessfully
bool moveDown(piece *p)
{
    if(!movePiece(fallingPiece, DOWN))
    {
        setPiece(fallingPiece);
        freePiece(fallingPiece);
        lines += removeEmptyRows(mainBoard);
        getNextPiece();
        return false;
    }

    return true;
}

int handleInput(moveCommand c)
{
    switch(c)
    {
    case MOVE_LEFT: movePiece(fallingPiece, LEFT); break;
    case MOVE_RIGHT: movePiece(fallingPiece, RIGHT); break;
    case MOVE_DOWN: moveDown(fallingPiece); break;
    case FLIP: rotatePiece(fallingPiece); break;
    case DROP: dropPiece(fallingPiece); break;
    case NONE: break;
    case QUIT: return 1; break;
    }

    return 0;
}

// Get the next piece
inline void getNextPiece()
{
    fallingPiece = nextPiece;
    nextPiece = newPiece(mainBoard);
}

void cleanUp()
{
    closeInter();
    freeBoard(mainBoard);
}
