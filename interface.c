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
    
    tetris_win = newwin(B_HEIGHT - B_HIDDEN + 2, B_WIDTH + 2,
                        starty, startx);
    keypad(tetris_win, TRUE);
    box(tetris_win, 0, 0);
    keypad(stdscr, TRUE);
    wrefresh(tetris_win);
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
    case KEY_F(1): return QUIT; break;
    }

    return NONE;
}

void displayBoard(board *mainBoard, piece *fallingPiece, piece *nextPiece)
{
    bRow *r;
    int x, y = 0;
    for(r = mainBoard->top; r != NULL; r = r->prev, y++)
    {
        //printf("%d %d\n", x, y);
        if(y < 2)
            continue;

        for(x = 0; x < B_WIDTH; x++)
        {
            dispBlock(x, y, r->blocks[x], tetris_win);
        }
    }

    displayFallingPiece(fallingPiece);
    displayNextPiece(nextPiece);

    wrefresh(tetris_win);
    refresh();
}

void displayStats(int score, int lines)
{
    mvprintw(starty - 1, startx, "Score: %d, Lines: %d", score, lines);
}

void dispBlock(int x, int y, block b, WINDOW *win)
{
    // clear empty blocks
    if(!b)
    {
        //mvaddch(y, x, ' ');
        mvwaddch(win, y, x, ' ');
        return;
    }

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
    default: break;
    }

    wattron(win, COLOR_PAIR(color));
    mvwaddch(win, y, x, BLOCK);
    wattroff(win, COLOR_PAIR(color));
    
}

inline void displayPiece(int initx, int inity, piece *p, WINDOW *win,
                         bool ovr)
{
    int xOff, yOff;
    block b;
    for(yOff = 0; yOff < PHEIGHT; yOff++)
        for(xOff = 0; xOff < PHEIGHT; xOff++)
        {
            b = p->blocks[yOff][xOff];
            if(ovr || b)
                dispBlock(initx + xOff, inity + yOff, b, win);
        }
}

void displayFallingPiece(piece *fallingPiece)
{
    int blockx = fallingPiece->x;
    int blocky = fallingPiece->y;

    if(blocky > PHEIGHT / 2)
        displayPiece(blockx, blocky, fallingPiece, tetris_win, false);
}

void displayNextPiece(piece *nextPiece)
{
    int nextx = startx + 2 + B_WIDTH;
    int nexty = starty;

    mvprintw(nexty, nextx, "Next:");
    
    displayPiece(nextx, nexty + 1, nextPiece, stdscr, true);
}
