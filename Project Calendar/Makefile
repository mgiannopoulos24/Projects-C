# Compiler
CC = gcc

# Directories
INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj
BUILD_DIR = build

# Compiler flags
CFLAGS = -I$(INCLUDE_DIR) -Wall -Wextra -std=c11

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Target executable
TARGET = $(BUILD_DIR)/calendar

# Default rule
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJ_FILES) | $(BUILD_DIR)
	$(CC) $(OBJ_FILES) -o $@

# Rule to build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directory if it does not exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Create object directory if it does not exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean up the build and object files
clean:
	rm -rf $(OBJ_DIR)/* $(BUILD_DIR)/*

.PHONY: all clean
