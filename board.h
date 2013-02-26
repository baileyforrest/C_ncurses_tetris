/*
 * Bailey Forrest - bcforres
 * baileycforrest@gmail.com
 *
 * board.h - header file for tetris board
 *
 */

#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>


#define B_WIDTH 10
#define B_HEIGHT 22
#define B_HIDDEN 2

typedef unsigned char block;

//List starts at bottom of board, goes up to top
typedef struct bRow
{
    struct board *next;
    struct board *prev;
    block blocks[B_WIDTH];
} bRow;

typedef struct board
{
    struct bRow *top, *bottom;
} board;

bRow *createBRow();
board *createBoard();
bRow *getBrow(board *board, int rowN);
void removeRow(bRow *row);
bool rowFull(bRow *row);
int removeEmptyRows(board *board);


#endif
