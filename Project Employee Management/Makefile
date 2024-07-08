# Compiler options
CC = gcc
CFLAGS = -Wall -g
INCLUDES = -Iinclude

# Directories
SRCDIR = src
OBJDIR = obj
INCDIR = include
BUILDDIR = build

# Source files and executable name
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
EXECUTABLE = $(BUILDDIR)/employee_management

# Targets
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJDIR)/* $(BUILDDIR)/*
