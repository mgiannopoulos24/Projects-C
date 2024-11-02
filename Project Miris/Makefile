CC = gcc
CFLAGS = -Wall -g
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include
BUILD_DIR = build

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# Default target: Build everything
all: miris

# Ensure that the obj and build directories exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Target to build the executable
miris: $(OBJ_DIR) $(BUILD_DIR) $(OBJ)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/miris $(OBJ)

# Rule to compile each source file to an object file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Clean up the build directory
clean:
	rm -f $(OBJ_DIR)/*.o $(BUILD_DIR)/miris *.txt

# Phony targets
.PHONY: all clean miris
