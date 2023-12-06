# Define the compiler and compiler flags
CC := gcc
CFLAGS := -Wall -Wextra -g
INC_DIR := include
SRC_DIR := src
BUILD_DIR := obj

# Find all .c files in the source directory
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)

# Derive object file names from source file names
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

# Set the name of the executable
EXECUTABLE := my_program

# Specify the header file dependencies
DEP_FILES := $(wildcard $(INC_DIR)/*.h)
DEP_FLAGS := $(patsubst %,-I%, $(INC_DIR))

# Default target
all: $(EXECUTABLE)

# Rule to link the object files into the executable
$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(DEP_FILES)
	$(CC) $(CFLAGS) $(DEP_FLAGS) -c -o $@ $<

# Clean rule
clean:
	rm -f $(BUILD_DIR)/*.o $(EXECUTABLE)

# Phony target to prevent conflicts with files named "clean"
.PHONY: clean

