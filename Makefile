# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -I./utils -I./libcrc/include
LDFLAGS = -L./libcrc/src -lcrc -lm

# Directories
SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = ./bins
LIBCRC_DIR = ./libcrc

# Source and object files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

# Output binary
TARGET = $(BIN_DIR)/hashing

# Rule to create the binary
$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Build target
.PHONY: all
all: $(TARGET)

# Clean up
.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)
