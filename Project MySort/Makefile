CC = gcc
CFLAGS = -Wall -Iinclude
LDFLAGS = 

SRC_DIR = src
OBJ_DIR = obj
BUILD_DIR = build
INCLUDE_DIR = include

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(filter-out $(OBJ_DIR)/sorter1.o $(OBJ_DIR)/sorter2.o, $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS)))

TARGET = $(BUILD_DIR)/mysort
SORTER1 = $(BUILD_DIR)/sorter1
SORTER2 = $(BUILD_DIR)/sorter2

all: $(TARGET) $(SORTER1) $(SORTER2)

$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(SORTER1): $(OBJ_DIR)/sorter1.o
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(SORTER2): $(OBJ_DIR)/sorter2.o
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ_DIR)/* $(BUILD_DIR)/*

.PHONY: all clean
