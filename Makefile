# -----------------------------
# Makefile for ls-v1.0.0
# Author: Your Name (BSDSF23M017)
# -----------------------------

# Compiler name
CC = gcc

# Compiler options
CFLAGS = -Wall -g

# Folder paths
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# File names
SRC = $(SRC_DIR)/ls-v1.0.0.c
OBJ = $(OBJ_DIR)/ls-v1.0.0.o
TARGET = $(BIN_DIR)/ls

# Default rule: build the executable
all: $(TARGET)

# Rule to make the executable
$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)
	@echo "✅ Build complete! Run it using: ./bin/ls"

# Rule to make the object file
$(OBJ): $(SRC)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)

# Run the program (shortcut)
run: all
	./$(TARGET)

# Clean all compiled files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "🧹 Cleaned up build files!"
