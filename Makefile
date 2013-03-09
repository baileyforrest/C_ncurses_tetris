CC = gcc
CFLAGS = -Wall -g
LIBS = -lncurses

all: tetris

tetris.o: tetris.c tetris.h
	$(CC) $(CFLAGS) -c tetris.c

board.o: board.c board.h
	$(CC) $(CLFAGS) -c board.c

piece.o: piece.c piece.h
	$(CC) $(CFLAGS) -c piece.c

interface.o: interface.c interface.h
	$(CC) $(CFLAGS) -c interface.c

tetris: tetris.o board.o piece.o interface.o $(LIBS)

clean:
	rm -rf *~ *.o 
