CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = obj

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
# Object files
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Executable name
EXEC = school_management

# Default target
all: $(EXEC)

# Linking object files to executable
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(BUILD_DIR)/$(EXEC)

# Compiling each source file into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files and executable
clean:
	rm -rf $(OBJ_DIR)/* $(BUILD_DIR)/*

# Phony targets
.PHONY: all clean
