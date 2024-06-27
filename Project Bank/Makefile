# Compiler
CC = gcc
# Compiler flags
CFLAGS = -Wall -Wextra -I$(INCDIR)

# Directories
SRCDIR = src
INCDIR = include
OBJDIR = obj
BUILDDIR = build

# Source files
SRCS = $(wildcard $(SRCDIR)/*.c)
# Object files
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

# Executable name
EXEC = $(BUILDDIR)/bank_management_system

# Default target
all: $(EXEC)

# Linking the executable
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

# Compiling each source file into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@ 

# Clean rule
clean:
	rm -f $(OBJDIR)/* $(EXEC)

# PHONY targets
.PHONY: all clean
