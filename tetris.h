/*
 * Bailey Forrest - bcforres
 * baileycforrest@gmail.com
 *
 * tetris.h - header file for main tetris game
 *
 */

#ifndef TETRIS_H
#define TETRIS_H

#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include "board.h"
#include "interface.h"

int initGame();
int runGame();
void dropPiece(piece *p);
bool moveDown(piece *p);
int handleInput(moveCommand c);
void getNextPiece();
void cleanUp();

#endif
