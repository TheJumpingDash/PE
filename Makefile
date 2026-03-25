# Compiler
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -O2

# Directories
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

# Target name
TARGET := $(BIN_DIR)/app

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/*.cc)
OBJS := $(SRCS:$(SRC_DIR)/%.cc=$(OBJ_DIR)/%.o)

# Default rule
all: $(TARGET)

# Link
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create directories if they don't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Rebuild
re: clean all

# Run
run: all
	./$(TARGET)

.PHONY: all clean re run