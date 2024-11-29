# Makefile

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iscanner/include -Iparser/include

# Directories
SCANNER_SRCDIR = scanner/src
PARSER_SRCDIR = parser/src
BUILDDIR = build
BINDIR = bin

# Source files
SCANNER_SOURCES = $(wildcard $(SCANNER_SRCDIR)/*.cpp)
PARSER_SOURCES = $(wildcard $(PARSER_SRCDIR)/*.cpp)

# Object files
SCANNER_OBJECTS = $(patsubst $(SCANNER_SRCDIR)/%.cpp, $(BUILDDIR)/scanner/%.o, $(SCANNER_SOURCES))
PARSER_OBJECTS = $(patsubst $(PARSER_SRCDIR)/%.cpp, $(BUILDDIR)/parser/%.o, $(PARSER_SOURCES))
OBJECTS = $(SCANNER_OBJECTS) $(PARSER_OBJECTS)

# Target executable
TARGET = $(BINDIR)/tiny_parser

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILDDIR)/scanner/%.o: $(SCANNER_SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR)/parser/%.o: $(PARSER_SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR) $(BINDIR)

.PHONY: all clean
