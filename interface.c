/*
 * Bailey Forrest - bcforres
 * baileycforrest@gmail.com
 *
 * interface.c
 *
 * Controls Display and Key commands using ncurses
 *
 */

#include "interface.h"

static WINDOW *tetris_win;

// dimensions of upper left corner of the board
static int startx;
static int starty;

// Initialize ncurses interface
int initInter()
{
    initscr();
    clear();
    noecho();
    cbreak();
    start_color();

    startx = (COLS - (B_WIDTH + 2)) / 2;
    starty = (LINES - (B_HEIGHT - B_HIDDEN + 2)) / 2;

    init_pair(RED, COLOR_RED, COLOR_BLACK);
    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
    
    tetris_win = newwin(B_HEIGHT - B_HIDDEN + 2, B_WIDTH + 2, starty, startx);
    keypad(tetris_win, TRUE);
    mvprintw(0, 0, "Tetris! Left/Right/Down arrow keys to move, Up to flip. "
             "Space bar to hard drop");
    
    
    return 0;
}

// Clean up function
void closeInter()
{
    endwin(); // Exit ncurses mode
}


// Get a command from the user
moveCommand getInput()
{
    int ch;
    
    ch = getch();
    
    switch(ch)
    {
    case KEY_LEFT: return MOVE_LEFT; break;
    case KEY_RIGHT: return MOVE_RIGHT; break;
    case KEY_UP: return FLIP; break;
    case KEY_DOWN: return MOVE_DOWN; break;
    case ' ': return DROP; break;
    }

    // Should not get here
    return FLIP;
}

void displayBoard(board *mainBoard, piece *fallingPiece, piece *nextPiece)
{
    bRow *r;

    int x, y = 0;
    for(r = mainBoard->bottom; r != NULL; r = r->next)
    {
        for(x = 0; x < B_WIDTH; x++)
        {
            dispBlock(startx + x, starty + y, r->blocks[x]);
        }

        y++;
    }

    displayFallingPiece(fallingPiece);
    displayNextPiece(nextPiece);
    refresh();
}

void displayStats(int score, int lines)
{
    mvprintw(starty - 1, startx, "Score: %d, Lines: %d", score, lines);
}

void dispBlock(int x, int y, block b)
{
    int color;
    switch((pieceType)b)
    {
    case I: color = RED; break;
    case J: color = GREEN; break;
    case L: color = YELLOW; break;
    case O: color = BLUE; break;
    case S: color = MAGENTA; break;
    case T: color = CYAN; break;
    case Z: color = WHITE; break;
    }

    attron(COLOR_PAIR(color));
    mvaddch(x, y, BLOCK);
    attroff(COLOR_PAIR(color));
    
}

inline void displayPiece(int initx, int inity, piece *p)
{
    int xOff, yOff;
    for(yOff = 0; yOff < PHEIGHT; yOff++)
        for(xOff = 0; xOff < PHEIGHT; xOff++)
        {
            dispBlock(initx + xOff, inity + yOff,
                      p->blocks[yOff][xOff]);
        }
}

void displayFallingPiece(piece *fallingPiece)
{
    int blockx = startx + fallingPiece->x;
    int blocky = starty + fallingPiece->y;


    displayPiece(blockx, blocky, fallingPiece);
}

void displayNextPiece(piece *nextPiece)
{
    int nextx = startx + 2 + B_WIDTH;
    int nexty = starty;

    mvprintw(nexty, nextx, "Next:");
    
    displayPiece(nextx, nexty + 1, nextPiece);
}
