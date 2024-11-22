# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Iinclude -I/usr/include/gtest -Wall -Wextra -Werror
GTEST_DIR := /usr/include/gtest
GTEST_LIB_DIR := /usr/lib/x86_64-linux-gnu

# Directories
SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
OUTPUT_DIR := output
TEST_DIR := test

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Object files excluding the main program
TEST_OBJS := $(filter-out $(BUILD_DIR)/mian.o, $(OBJS))

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

# Build and run a specific test
test: $(TEST_OBJS) | $(BUILD_DIR)
	@echo "TEST_FILE is $(TEST_FILE)"
	@if [ -z "$(TEST_FILE)" ]; then \
		echo "Error: Please specify a test file using TEST_FILE=<test_file>"; \
		echo "Example: make test TEST_FILE=token"; \
		exit 1; \
	else \
		echo "Compiling $(TEST_DIR)/$(TEST_FILE)_test.cpp"; \
		$(CXX) $(CXXFLAGS) -I$(GTEST_DIR) -L$(GTEST_LIB_DIR) \
		$(TEST_DIR)/$(TEST_FILE)_test.cpp $(TEST_OBJS) -lgtest -lgtest_main -pthread \
		-o $(BUILD_DIR)/$(TEST_FILE)_test && ./$(BUILD_DIR)/$(TEST_FILE)_test; \
	fi


.PHONY: all clean run test
