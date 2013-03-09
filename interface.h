/*
 * Bailey Forrest - bcforres
 * baileycforrest@gmail.com
 *
 * interface.h
 *
 * Controls Display and Key commands using ncurses
 *
 */

#ifndef INTERFACE_H
#define INTERFACE_H

#include <ncurses.h>
#include "board.h"
#include "piece.h"

#define BLOCK (' ' | A_REVERSE)

typedef enum { MOVE_DOWN,
               MOVE_LEFT,
               MOVE_RIGHT,
               FLIP,
               DROP,
               NONE,
               QUIT
} moveCommand;

int initInter();
void closeInter();
moveCommand getInput();
void displayBoard(board *mainBoard, piece *fallingPiece, piece *nextPiece);
void displayStats(int score, int lines);
void dispBlock(int x, int y, block b, WINDOW *win);
void displayPiece(int initx, int inity, piece *p, WINDOW *win, bool ovr);
void displayFallingPiece(piece *fallingPiece);
void displayNextPiece(piece *nextPiece);
void dispGameOver();

#endif
