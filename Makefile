# Compiler and flags
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Iinclude

# Directories
SRC_DIR = src
BIN_DIR = bin
INC_DIR = include

# Target executable name
TARGET = $(BIN_DIR)/Lab010

# Source files and Object files
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/helpers.c $(SRC_DIR)/algorithms.c
OBJS = $(BIN_DIR)/main.o $(BIN_DIR)/helpers.o $(BIN_DIR)/algorithms.o

# Default rule to build everything
all: $(BIN_DIR) $(TARGET)

# Rule to link the object files and create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rules to compile each .c file into a .o object file
$(BIN_DIR)/main.o: $(SRC_DIR)/main.c $(INC_DIR)/simulator.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/helpers.o: $(SRC_DIR)/helpers.c $(INC_DIR)/simulator.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/algorithms.o: $(SRC_DIR)/algorithms.c $(INC_DIR)/simulator.h
	$(CC) $(CFLAGS) -c $< -o $@

# Create the bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean rule to remove compiled files
clean:
	rm -rf $(BIN_DIR)/*.o $(TARGET)