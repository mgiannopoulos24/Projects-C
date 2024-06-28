CC = gcc
CFLAGS = -lncurses -I$(IDIR)

IDIR = include/
SRCDIR = src/

SOURCES = $(SRCDIR)*.c

all: sudoku run clean

sudoku: $(SOURCES)
	$(CC) -o $@ $^ $(CFLAGS)

run:
	./sudoku

clean:
	rm -f sudoku