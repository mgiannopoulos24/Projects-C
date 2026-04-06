CC = gcc
CFLAGS = -Wall -Wextra -I include
SRCDIR = src
OBJDIR = obj
BINDIR = bin

TARGET = $(BINDIR)/voting

SRCS = $(SRCDIR)/main.c $(SRCDIR)/voting.c
OBJS = $(OBJDIR)/main.o $(OBJDIR)/voting.o

all: $(TARGET)

$(TARGET): $(OBJS) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR) $(BINDIR):
	mkdir -p $@

clean:
	rm -rf $(OBJDIR)/*.o $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
