# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Iinclude -Wall -Wextra -Werror

# Directories
SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
OUTPUT_DIR := output

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Target executable
TARGET := scanner

# Default target
all: $(TARGET)

# Build the target executable
$(TARGET): $(OBJS) | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create build and output directories if they don't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

# Clean up build files and executable
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Run the scanner with example input and output
run: $(TARGET)
	./$(TARGET) examples/example1.txt $(OUTPUT_DIR)/output.txt
	cat $(OUTPUT_DIR)/output.txt

.PHONY: all clean run

