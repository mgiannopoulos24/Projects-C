CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 `pkg-config --cflags gtk+-3.0` -Iinclude -w
LDFLAGS = `pkg-config --libs gtk+-3.0`
SRC_DIR = src
OBJ_DIR = obj
BUILD_DIR = build
TARGET = $(BUILD_DIR)/sudoku_solver_gui

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)/* $(OBJ_DIR)/*

.PHONY: all clean
