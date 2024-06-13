# Compiler
CC = gcc
# Compiler flags
CFLAGS = -Wall -Wextra -Iinclude

# Directories
SRCDIR = src
INCLUDEDIR = include
BUILDDIR = build

# Source files
SRCS = $(wildcard $(SRCDIR)/*.c)
# Object files
OBJS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRCS))

# Executable
TARGET = bus_reservation_system

# Default rule
all: $(TARGET)

# Linking step
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Compilation step
$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directory if it doesn't exist
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Clean build files
clean:
	rm -rf $(BUILDDIR) $(TARGET)

# Phony targets
.PHONY: all clean
