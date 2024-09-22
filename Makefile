# Directories
SRC_DIR = ./src/
BIN_DIR = ./bins/
INC_DIR = ./utils/

# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -I./utils/ -I./libcrc/include/
LDFLAGS = -L./libcrc/src/ -lcrc -lm -lssl -lcrypto

# Source files
SRC = $(wildcard $(SRC_DIR)/*.c)  # Automatically find all .c files
OBJ = $(patsubst $(SRC_DIR)%.c,$(BIN_DIR)%.o,$(SRC))

# Binaries
BINS = $(BIN_DIR)/crc16 $(BIN_DIR)/dictionary

# Targets
all: $(BINS)

$(BIN_DIR)/crc16: $(BIN_DIR)/hash.o $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(BIN_DIR)/dictionary: $(BIN_DIR)/dictionary.o $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

# Clean target
clean:
	rm -f $(BIN_DIR)/*.o $(BINS)

.PHONY: all clean
