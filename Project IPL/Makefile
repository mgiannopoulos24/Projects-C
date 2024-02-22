CC=gcc
CFLAGS=-Wall -g
LDFLAGS=
OBJFILES=main.o parser.o executor.o
TARGET=ipli

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

main.o: main.c parser.h executor.h
	$(CC) $(CFLAGS) -c main.c

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c

executor.o: executor.c executor.h
	$(CC) $(CFLAGS) -c executor.c

clean:
ifeq ($(OS),Windows_NT)
	del /Q main.o parser.o executor.o ipli *~
else
	rm -f main.o parser.o executor.o ipli *~
endif

