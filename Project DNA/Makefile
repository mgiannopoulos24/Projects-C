CC = gcc
CFLAGS = -Ofast -Wall -Wextra -Werror -pedantic
LIBS = -lm

SRCS = dna.c
OBJS = $(SRCS:.c=.o)
TARGET = dna

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
