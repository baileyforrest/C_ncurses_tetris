/*
 * Bailey Forrest - bcforres
 * baileycforrest@gmail.com
 *
 * board.c - main functions for tetris board
 *
 */

#include "board.h"

inline bRow* createBRow()
{
    bRow* newR = calloc(1, sizeof(bRow));
    newR->next = NULL;
    newR->prev = NULL;

    return newR;
}

board *createBoard()
{
    board *output = malloc(sizeof(board));
    output->bottom = createBRow();
    bRow *prev = output->bottom;
    
    bRow *new;

    int i;
    for(i = 0; i < B_HEIGHT - 1; i++)
    {
        new = createBRow();
        prev->next = new;
        new->prev = prev;
        prev = new;
    }
    output->top = new;

    return output;
}

void freeBoard(board *board)
{
    bRow *p = board->top, *next;;
    while(p != NULL)
    {
        next = p->next;
        free(p);
        p = next;
    }

    free(board);
}

// Gets row number from board
inline bRow *getBrow(board *board, int rowN)
{
    register bRow *row = board->bottom;
    while(rowN--)
        row = row->next;

    return row;
}

// Remove row, Responsibility of calling function to put new rows at top
void removeRow(board* board, bRow *row)
{
    if(row == board->bottom)
    {
        board->bottom = board->bottom->next;
        board->bottom->prev = NULL;
    }
    else if(row == board->top)
    {
        board->top = board->top->prev;
        board->top->next = NULL;
    }
    else
    {
        row->prev->next = row->next;
        row->next->prev = row->prev;
    }

    free(row);
}

// Returns true if the row is full, else false
bool rowFull(bRow* row)
{
    int i;
    for(i = 0; i < B_WIDTH; i++)
        if(!row->blocks[i])
            return false;

    return true;
}

// Removes empty rows from the board
// Returns the number of rows removed
int removeEmptyRows(board* board)
{
    int removed = 0;
    bRow *next, *row = board->bottom;
    while(row)
    {
        next = row->next;
        if(rowFull(row))
        {
            removeRow(board, row);
            removed++;
        }
        row = next;
    }
    
    int i;
    for(i = 0; i < removed; i++)
    {
        bRow *new = createBRow();
        board->top->next = new;
        new->prev = board->top;
        board->top = new;
    }

    return removed;
}
