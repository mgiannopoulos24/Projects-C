CC = gcc
CFLAGS = -Os -Wall -Wextra -Werror -pedantic
TARGET = coop

all: $(TARGET)

$(TARGET): coop.o
	$(CC) $(CFLAGS) -o $(TARGET) coop.o

coop.o: coop.c
	$(CC) $(CFLAGS) -c coop.c

clean:
	rm -f *.o $(TARGET) *put
