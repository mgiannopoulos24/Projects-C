# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99 -Iinclude

# Linker flags
LDFLAGS = -lm

# Executable name
TARGET = calculator

# Source files
SRC = src/main.c src/operations.c src/input.c

# Object files directory
OBJDIR = obj

# Object files
OBJ = $(SRC:src/%.c=$(OBJDIR)/%.o)

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Build object files
$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create object files directory
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean up
clean:
	rm -f $(OBJ) $(TARGET)
	rm -rf $(OBJDIR)

# Phony targets
.PHONY: all clean
