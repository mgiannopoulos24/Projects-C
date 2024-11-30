# Makefile

CC = gcc
CFLAGS = -Ofast -Wall -Wextra -Werror -pedantic
LDFLAGS = -lm

all: fractal

complexlib.o: complexlib.c complexlib.h
	$(CC) $(CFLAGS) -c complexlib.c -o complexlib.o

fractal.o: fractal.c complexlib.h
	$(CC) $(CFLAGS) -c fractal.c -o fractal.o

fractal: complexlib.o fractal.o
	$(CC) $(CFLAGS) -o fractal complexlib.o fractal.o $(LDFLAGS)

clean:
	rm -f fractal complexlib.o fractal.o output.bmp
