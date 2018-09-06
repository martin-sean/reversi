# Sourced from http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
IDIR=/header
CC=gcc
CFLAGS=-ansi -pedantic -Wall -I.
_DEPS=reversi.h game.h gameboard.h player.h utility.h
DEPS=%($(IDIR)/%,$(_DEPS))
OBJ=reversi.o game.o gameboard.o player.o utility.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

reversi: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o