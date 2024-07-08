# Compiler and Linker
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99

# Directories
INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj
BUILD_DIR = build

# The target executable
TARGET = $(BUILD_DIR)/converter

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Build target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Clean up build artifacts
clean:
	rm -rf $(OBJ_DIR)/* $(BUILD_DIR)/*

# Phony targets
.PHONY: all clean
