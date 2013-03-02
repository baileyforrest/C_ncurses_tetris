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

// place a piece on the board
void setPiece(piece *p)
{
    int i, row;
    bRow *r = p->cRow;
    for(row = 0; row < PHEIGHT; row++)
    {
        for(i = 0; i < PHEIGHT; i++)
        {
            r->blocks[p->x + i] = p->blocks[PHEIGHT - 1 - row][i];
        }

        r = r->next;
    }
}


bool validLocation(piece *p)
{
    int row = 0, col = 0;
    bRow*  rp = p->cRow;
    for(row = 0; row < PHEIGHT; row++)
    {
        for(col = 0; col < PHEIGHT; col++)
        {
            // If there's a block here
            if(p->blocks[row][col])
            {
                // Check if block out of bounds
                if((p->y + row < 0) || (p->x + col < 0) ||
                   (p->x + col > B_HEIGHT))
                    return false;

                // Check if there is an overlapping block
                if(rp->blocks[p->x + col])
                    return false;
            }
        }
        rp = rp->next;
    }

    return true;
}

// Move a block.  Returns true if piece moved successfully
// dir: -1 (left), 0 (down), 1 (right)
bool movePiece(piece *p, int dir)
{
    // Moving down
    if(!dir)
    {
        p->y++;
        p->cRow = p->cRow->prev;
    }
    else
        p->x += dir;

    if(validLocation(p))
        return true;

    // Move wasn't valid, undo it
    if(!dir)
    {
        p->y--;
        p->cRow = p->cRow->next;
    }
    else
        p->x -= dir;
    
    return false;
}

void swap(block *b1, block *b2)
{
    block t;
    t = *b1;
    *b1 = *b2;
    *b2 = t;
}

// Transpose PHEIGHTxPHEIGHT 2d array
void trans(block blocks[PHEIGHT][PHEIGHT])
{
    int i, j;
    for(i = 0; i < PHEIGHT - 2; i++)
    {
        for(j = i + 1; j < PHEIGHT; j++)
        {
            swap(&blocks[i][j], &blocks[j][i]);
        }
    }
}

// Rotate upper 3x3 square of block matrix
void rotate(block blocks[PHEIGHT][PHEIGHT])
{
    block temp[PHEIGHT][PHEIGHT];
    bzero(temp, sizeof(block) * PHEIGHT * PHEIGHT);
    
    int oRow, oCol;
    for(oRow = 0; oRow < 3; oRow++)
        for(oCol = 0; oCol < 3; oCol++)
        {
            temp[oCol][2 - oRow] = blocks[oRow][oCol];
        }

    memcpy(blocks, temp, sizeof(block) * PHEIGHT * PHEIGHT);
}



// Rotates a piece clockwise.  Returns false if rotation could not be completed
bool rotatePiece(piece *p)
{
    bool success = false;
    piece *testPiece = malloc(sizeof(piece));
    memcpy(testPiece, p, sizeof(piece));
    
    switch(p->t)
    {
    case O: break; // Do nothing for O pieces
    case I:
    case S:
    case Z: trans(testPiece->blocks); break;
        
    case J:
    case L:
    case T: rotate(testPiece->blocks); break;
    default: break; // Should not get here
    }

    // If the move was successful, copy it to the original piece
    if(validLocation(testPiece))
    {
        memcpy(p, testPiece, sizeof(piece));
        success = true;
    }
    
    free(testPiece);

    return success;
}

// Initializes piece with I pattern
// Assumes 2d array currently clear
void initI(piece *p)
{
    int i;
    for(i = 0; i < 4; i++)
        p->blocks[PHEIGHT / 2][i] = (block)I;
}

// Initializes piece with J pattern
// Assumes 2d array currently clear
void initJ(piece *p)
{
    int i;
    for(i = 0; i < 3; i++)
        p->blocks[PHEIGHT / 2][i] = (block)I;
    p->blocks[PHEIGHT / 2 + 1][2] = (block)J;
}

// Initializes piece with L pattern
// Assumes 2d array currently clear
void initL(piece *p)
{

}

// Initializes piece with O pattern
// Assumes 2d array currently clear
void initO(piece *p)
{

}

// Initializes piece with S pattern
// Assumes 2d array currently clear
void initS(piece *p)
{

}

// Initializes piece with T pattern
// Assumes 2d array currently clear
void initT(piece *p)
{

}

// Initializes piece with Z pattern
// Assumes 2d array currently clear
void initZ(piece *p)
{

}


// Creates new piece of specified type
piece *newPiece(pieceType t, board *b)
{
    piece* p = calloc(1, sizeof(piece));
    p->y = 0;
    p->x = B_WIDTH / 2 - PHEIGHT / 2;
    p->t = t;

    bRow *r = b->top;
    int rIdx;
    for(rIdx = 0; rIdx < PHEIGHT - 1; rIdx++)
        r = r->prev;

    p->cRow = r;

    switch(t)
    {
    case I: initI(p); break;
    case J: initJ(p); break;
    case L: initL(p); break;
    case O: initO(p); break;
    case S: initS(p); break;
    case T: initT(p); break;
    case Z: initZ(p); break;
    }


    

    

    return p;
}
