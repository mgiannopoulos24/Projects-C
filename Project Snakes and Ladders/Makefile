# Compiler
CC = gcc

# Directories
SRC_DIR = src
OBJ_DIR = obj
BUILD_DIR = build
INC_DIR = include

# Executable name
TARGET = $(BUILD_DIR)/snakes_and_ladders

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Compiler flags
CFLAGS = -I$(INC_DIR) -Wall

# Linker flags
LDFLAGS = -lSDL2 -lSDL2_ttf

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BUILD_DIR)
	$(CC) -o $@ $^ $(LDFLAGS)

# Object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create obj directory if it does not exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Clean target
clean:
	rm -rf $(OBJ_DIR)/* $(BUILD_DIR)/*

# Phony targets
.PHONY: all clean
