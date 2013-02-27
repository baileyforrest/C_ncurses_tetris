/*
 * Bailey Forrest - bcforres
 * baileycforrest@gmail.com
 *
 * tetris.c
 * 
 * Main control loop for tetris
 *
 */

#include <time.h>
#include "board.h"
#include "interface.h"
#include "tetris.h"

static board *mainBoard = NULL;
static int score;
static int level;

int main()
{
    for(;;)
    {
        if(initGame() < 0)
            exit(1);

        dispMenu();
        if(runGame()) break;
    }
    return 0;
}

int initGame()
{
    score = 0;
    level = 0;

    if(mainBoard != NULL)
        freeBoard(mainBoard);

    if(initInter() < 0)
        return -1;
    
    if((mainBoard = createBoard()) == NULL)
        return -1;

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
    int delay = 250;

    for(;;)
    {

    }
    
    
    return 0;
}

void dispMenu()
{
}
