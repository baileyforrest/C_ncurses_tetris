/*
 * Bailey Forrest
 * baileycforrest@gmail.com
 *
 * piece.h
 *
 * Contains operations on pieces
 */

#ifndef PIECE_H
#define PIECE_H

#include "board.h"

#define PHEIGHT 4
#define FALL 0x8
#define NOT_FALL 0x7

typedef enum { I, J, L, O, S, T, Z } pieceType;

typedef struct piece
{
    pieceType t;
    bRow* cRow; // Points to lowest row piece is in
} piece;

#endif
