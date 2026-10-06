CC := gcc
CFLAGS := -Wall -Wextra

SRC_FILES := ./src/*.c
TARGET_EXEC = ./lc3-vm

$(TARGET_EXEC): $(SRC_FILES)
	$(CC) $(CFLAGS) $^ -o $@

run: $(TARGET_EXEC)
	$(TARGET_EXEC)
