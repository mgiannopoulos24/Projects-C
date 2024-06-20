CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OBJDIR = obj
OBJ = $(OBJDIR)/main.o $(OBJDIR)/palindrome.o
TARGET = palindrome_checker

# Default target
all: $(TARGET)

# Link the target executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Compile main.c to obj/main.o
$(OBJDIR)/main.o: main.c palindrome.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c main.c -o $(OBJDIR)/main.o

# Compile palindrome.c to obj/palindrome.o
$(OBJDIR)/palindrome.o: palindrome.c palindrome.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c palindrome.c -o $(OBJDIR)/palindrome.o

# Create the obj directory if it does not exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean up build files
clean:
	rm -f $(OBJ)
	rm -f $(TARGET)

# Phony targets to avoid conflicts with file names
.PHONY: all clean
