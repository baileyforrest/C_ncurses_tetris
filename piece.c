/*
 * Bailey Forrest
 * baileycforrest@gmail.com
 *
 * piece.c
 *
 * Contains operations on pieces
 */

#include "piece.h"
#include "board.h"

// Mark all blocks in a piece as set (not falling)
void setPiece(piece *p)
{
    int i, row;
    bRow *r = p->cRow;
    for(row = 0; row < PHEIGHT; row++)
    {
        for(i = 0; i < B_WIDTH; i++)
        {
            r->blocks[i] &= NOT_FALL;
        }
    }
}

// Move a block down.  Returns 1 if block cannot move down, 0 otherwise
int moveDown(piece *p)
{
    block *level = malloc(sizeof(block) * B_WIDTH);

    int i, row;

    bRow* mRow = p->cRow;

    for(row = 0; row < PHEIGHT; row++)
    {
        for(i = 0; i < B_WIDTH; i++)
            level[i] = mRow->blocks[i];

        bRow *lower = mRow->prev;
        block *lowerA = lower->blocks;

        for(i = 0; i < B_WIDTH; i++)
        {
            // Check if any blocks are in the way of falling piece
            if((level[i] & FALL) && lowerA[i] != 0)
            {
                setPiece(p);
                return true;
            }
        }

        // If its a falling block in col, copy it to lower level
        for(i = 0; i < B_WIDTH; i++)
        {
            if(level[i] & FALL)
            {
                lowerA[i] = level[i];

                // Clear previous position
                level[i] = 0;
            }
        }

        mRow = mRow->next;
    }

    // Move down current row by 1
    p->cRow = p->cRow->prev;

    return 0;
}

