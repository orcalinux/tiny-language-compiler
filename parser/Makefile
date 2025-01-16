# Compiler and Flags
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra -g -MMD -MP

# Directories
SRCDIR = src
INCDIR = include
OBJDIR = obj
DEPDIR = dep
BINDIR = bin

# Source and Object Files
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
DEPS = $(patsubst $(SRCDIR)/%.cpp,$(DEPDIR)/%.d,$(SRCS))

# Target Executable
TARGET = $(BINDIR)/tiny-parser

# Phony Targets
.PHONY: all clean directories help run test

# Default Target
all: directories $(TARGET)

# Rule to Create Necessary Directories
directories:
	@mkdir -p $(OBJDIR) $(DEPDIR) $(BINDIR)

# Linking the Target Executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compiling Source Files into Object Files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -MF $(DEPDIR)/$*.d

# Include dependency files
-include $(DEPS)

# Run the Parser
run: all
	@echo "Running the parser..."
	@./$(TARGET)

# Help Target
help:
	@echo "========================================"
	@echo "          Makefile Help Menu            "
	@echo "========================================"
	@echo "Available Targets:"
	@echo "  all       Build the project."
	@echo "  run       Build and run the parser."
	@echo "  clean     Remove build artifacts."
	@echo "  help      Show this help message."
	@echo ""
	@echo "Usage Examples:"
	@echo "  make        # Builds the project."
	@echo "  make run    # Builds and runs the parser."
	@echo "  make clean  # Cleans all build artifacts."
	@echo "  make help   # Displays this help menu."
	@echo "========================================"

# Clean Target to Remove Build Artifacts
clean:
	rm -rf $(OBJDIR) $(DEPDIR) $(BINDIR)
