CC = gcc
CFLAGS = -Wall -g
OBJDIR = obj
SRCDIR = src
INCDIR = include
BINDIR = build

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

TARGET = $(BINDIR)/mvote

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o $(TARGET) registeredvoters.csv
