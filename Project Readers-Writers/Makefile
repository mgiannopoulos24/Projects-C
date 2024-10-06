CC = gcc
CFLAGS = -Iinclude -Wall -g
LDFLAGS = -lrt

SRC_DIR = src
OBJ_DIR = obj
BUILD_DIR = build
INCLUDE_DIR = include

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TARGETS = reader writer

all: $(TARGETS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

reader: $(OBJ_DIR)/reader.o $(OBJ_DIR)/shared_memory.o $(OBJ_DIR)/semaphores.o
	$(CC) $^ -o $(BUILD_DIR)/reader $(LDFLAGS)

writer: $(OBJ_DIR)/writer.o $(OBJ_DIR)/shared_memory.o $(OBJ_DIR)/semaphores.o
	$(CC) $^ -o $(BUILD_DIR)/writer $(LDFLAGS)

clean:
	rm -f $(OBJ_DIR)/*.o $(BUILD_DIR)/*

.PHONY: clean all
