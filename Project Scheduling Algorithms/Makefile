CC = gcc
CFLAGS = -Wall -Wextra
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
INCLUDE_DIR = include

all: $(BIN_DIR)/fcfs $(BIN_DIR)/srtf $(BIN_DIR)/priority_rr $(BIN_DIR)/monotonic $(BIN_DIR)/edf

$(BIN_DIR)/fcfs: $(BUILD_DIR)/schedule_fcfs.o $(BUILD_DIR)/list.o $(BUILD_DIR)/CPU.o
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR)/srtf: $(BUILD_DIR)/schedule_srtf.o $(BUILD_DIR)/list.o $(BUILD_DIR)/CPU.o
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR)/priority_rr: $(BUILD_DIR)/schedule_priority_rr.o $(BUILD_DIR)/list.o $(BUILD_DIR)/CPU.o
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR)/monotonic: $(BUILD_DIR)/schedule_monotonic.o $(BUILD_DIR)/list.o $(BUILD_DIR)/CPU.o
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR)/edf: $(BUILD_DIR)/schedule_edf.o $(BUILD_DIR)/list.o $(BUILD_DIR)/CPU.o
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INCLUDE_DIR)

clean:
	rm -f $(BUILD_DIR)/*.o $(BIN_DIR)/fcfs $(BIN_DIR)/srtf $(BIN_DIR)/priority_rr $(BIN_DIR)/monotonic $(BIN_DIR)/edf

.PHONY: all clean fcfs srtf priority_rr monotonic edf

fcfs: $(BIN_DIR)/fcfs
srtf: $(BIN_DIR)/srtf
priority_rr: $(BIN_DIR)/priority_rr
monotonic: $(BIN_DIR)/monotonic
edf: $(BIN_DIR)/edf
