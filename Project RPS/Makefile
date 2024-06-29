CC = gcc
CFLAGS = -Wall -std=c99
TARGET = rock_paper_scissors
SRCS = rps.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
