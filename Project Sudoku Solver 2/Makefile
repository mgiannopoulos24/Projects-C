CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -Iinclude
SRC_DIR = src
OBJ_DIR = obj
BUILD_DIR = build
TARGET = $(BUILD_DIR)/sudoku_solver

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm -rf $(OBJ_DIR)/* $(BUILD_DIR)/*

.PHONY: all clean
