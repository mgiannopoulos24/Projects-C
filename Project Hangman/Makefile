# Define directories
INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj
BUILD_DIR = build

# Compiler and flags
CC = gcc
CFLAGS = -I$(INCLUDE_DIR) -Wall

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Executable name
TARGET = hangman

# Default rule
all: $(BUILD_DIR)/$(TARGET)

# Link object files to create the executable
$(BUILD_DIR)/$(TARGET): $(OBJS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove build artifacts
clean:
	rm -rf $(OBJ_DIR)/* $(BUILD_DIR)/*

.PHONY: all clean
