CC = gcc
CFLAGS = -Wall -lncurses

all: tetris

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

board.o: board.c board.h
	$(CC) $(CLFAGS) -c board.c

tetris: main.o board.o

clean:
	rm -rf *~ *.o 
