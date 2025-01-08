# Tiny Language Compiler

![License](https://img.shields.io/badge/license-MIT-blue.svg) ![CPP](https://img.shields.io/badge/language-CPP-brightgreen.svg) ![SDL2](https://img.shields.io/badge/SDL2-yes-blue.svg)


## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Directory Structure](#directory-structure)
- [Installation](#installation)
- [Usage](#usage)
- [Documentation](#documentation)F
- [Testing](#testing)
- [Contributing](#contributing)
- [License](#license)

## Overview

The **Tiny Language Compiler** is a comprehensive project designed to demonstrate the principles and practices of compiler construction for a simplified programming language. This project encompasses all major components of a compiler, including lexical analysis (scanner), parsing, and a graphical user interface (GUI) for interacting with the compiler. It serves as an educational tool for understanding compiler design and implementation.

## Features

- **Lexical Analysis (Scanner):** Tokenizes the source code into meaningful symbols.
- **Parsing:** Analyzes the token stream to construct a parse tree based on the Tiny Language grammar.
- **Graphical User Interface (GUI):** Provides an intuitive interface to input code, view tokens, parse trees, and syntax trees.
- **Comprehensive Documentation:** Includes detailed PDFs on compiler construction and project-specific documentation.
- **Testing Suite:** Ensures the reliability and correctness of the scanner and parser components.
- **Extensible Design:** Modular architecture allows for easy extension and modification of language features.

## Directory Structure

```
.
├── docs
│   ├── compiler-construction-principles-and-practice.pdf
│   ├── compilers-principles-techniques-and-tools.pdf
│   ├── crafting-interpreters-compress.pdf
│   ├── keith-cooper-linda-torczon-engineering-a-compiler-en.pdf
│   └── modern-compiler-implementation-in-c.pdf
├── LICENSE
├── parser
│   ├── include
│   │   ├── parser.hpp
│   │   ├── parsing_table.hpp
│   │   ├── stack.hpp
│   │   └── token.hpp
│   ├── Makefile
│   ├── README.md
│   ├── src
│   │   ├── main.cpp
│   │   ├── parser.cpp
│   │   ├── parsing_table.cpp
│   │   ├── stack.cpp
│   │   └── token.cpp
│   └── tests
├── parser_gui
│   ├── CMakeLists.txt
│   ├── Data
│   │   ├── include
│   │   │   ├── Node.h
│   │   │   └── Token.h
│   │   └── src
│   │       ├── Node.cpp
│   │       └── Token.cpp
│   ├── FileHandling
│   │   ├── include
│   │   │   └── FileHandler.h
│   │   └── src
│   │       └── FileHandler.cpp
│   ├── main.cpp
│   ├── MainWindow.cpp
│   ├── MainWindow.h
│   ├── Parser
│   │   ├── include
│   │   │   └── Parser.h
│   │   └── src
│   │       └── Parser.cpp
│   ├── resources
│   │   ├── About.png
│   │   ├── Copy.png
│   │   ├── Cut.png
│   │   ├── Help.png
│   │   ├── New Text File.png
│   │   ├── New Tokens File.png
│   │   ├── Open File.png
│   │   ├── Paste.png
│   │   ├── Save As File.png
│   │   ├── Save File.png
│   │   ├── View Parse Tree.png
│   │   ├── View Syntax Tree.png
│   │   ├── View Text.png
│   │   └── View Tokens.png
│   ├── resources.qrc
│   ├── Scanner
│   │   ├── include
│   │   │   ├── Scanner.h
│   │   │   └── TokenStreamBuilder.h
│   │   └── src
│   │       ├── Scanner.cpp
│   │       └── TokenStreamBuilder.cpp
│   └── Widgets
│       ├── include
│       │   ├── TabContent.h
│       │   ├── TabWidget.h
│       │   ├── TextEditor.h
│       │   ├── ToolBar.h
│       │   └── TreeVisualiser.h
│       └── src
│           ├── TabContent.cpp
│           ├── TabWidget.cpp
│           ├── TextEditor.cpp
│           ├── ToolBar.cpp
│           └── TreeVisualiser.cpp
├── README.md
└── scanner
    ├── build.bat
    ├── docs
    │   ├── flex__bison.pdf
    │   └── ScannerProjectDescription_2024.pdf
    ├── examples
    │   ├── example1.txt
    │   ├── example2.txt
    │   ├── example3.txt
    │   ├── example4.txt
    │   └── example5.txt
    ├── include
    │   ├── app.hpp
    │   ├── file_handler.hpp
    │   ├── scanner.hpp
    │   ├── token.hpp
    │   └── token_stream_builder.hpp
    ├── Makefile
    ├── output
    │   └── output.txt
    ├── README.md
    ├── src
    │   ├── app.cpp
    │   ├── file_handler.cpp
    │   ├── main.cpp
    │   ├── scanner.cpp
    │   ├── token.cpp
    │   └── token_stream_builder.cpp
    └── test
        ├── scanner_test.cpp
        └── token_test.cpp

30 directories, 83 files
```

## Installation

### Prerequisites

- **C++ Compiler:** Ensure you have a C++ compiler installed (e.g., GCC, Clang, MSVC).
- **CMake:** Required for building the GUI component.
- **Make:** For building the scanner and parser components.
- **Qt Framework:** Required for the GUI (parser_gui).

### Clone the Repository

```bash
git clone https://github.com/orcalinux/tiny-language-compiler.git
cd tiny-language-compiler
```

### Build Scanner

The scanner component is responsible for lexical analysis.

```bash
cd scanner
make
```

*For Windows users, you can use the provided `build.bat` script:*

```bash
build.bat
```

### Build Parser

The parser component handles syntactic analysis.

```bash
cd ../parser
make
```

### Build GUI

The GUI provides an interface to interact with the compiler components.

```bash
cd ../parser_gui
mkdir build
cd build
cmake ..
make
```

*Ensure that the Qt framework is properly installed and configured on your system.*

## Usage

### Scanner

After building, you can run the scanner to tokenize your Tiny Language source code.

```bash
./scanner <source_file>
```

*Example:*

```bash
./scanner examples/example1.txt
```

### Parser

After building, run the parser to generate the parse tree from the token stream.

```bash
./parser <token_stream_file>
```

*Example:*

```bash
./parser output/output.txt
```

### GUI

Launch the GUI to interact with the scanner and parser visually.

```bash
./parser_gui
```

The GUI allows you to:

- Open and edit Tiny Language source files.
- View tokens generated by the scanner.
- Visualize the parse tree and syntax tree.
- Save and manage token and parse tree files.

## Documentation

Comprehensive documentation is available in the `docs` directory, including:

- **Compiler Construction Principles and Practice:** An in-depth guide on compiler design.
- **Compilers: Principles, Techniques, and Tools:** Reference material for compiler construction.
- **Crafting Interpreters:** Insights into building interpreters, applicable to compiler design.
- **Engineering a Compiler:** Best practices for compiler engineering.
- **Modern Compiler Implementation in C:** Practical implementation details.

Additional project-specific documentation can be found within the `scanner/docs` and `parser/docs` directories.

## Testing

A suite of tests ensures the reliability and correctness of the compiler components.

### Scanner Tests

Navigate to the `scanner` directory and run the tests:

```bash
cd scanner
make test
```

### Parser Tests

Navigate to the `parser` directory and run the tests:

```bash
cd ../parser
make test
```

*Ensure that all dependencies are met before running the tests.*

## Contributing

Contributions are welcome! To contribute to this project, follow these steps:

1. **Fork the Repository**

   Click the "Fork" button at the top-right corner of this page to create your own fork.

2. **Clone Your Fork**

   ```bash
   git clone https://github.com/orcalinux/tiny-language-compiler.git
   cd tiny-language-compiler
   ```

3. **Create a New Branch**

   ```bash
   git checkout -b feature/YourFeature
   ```

4. **Commit Your Changes**

   ```bash
   git commit -m "Add some feature"
   ```

5. **Push to the Branch**

   ```bash
   git push origin feature/YourFeature
   ```

6. **Open a Pull Request**

   Go to the original repository and click the "New Pull Request" button.

### Code of Conduct

Please adhere to the [Contributor Covenant Code of Conduct](https://www.contributor-covenant.org/version/2/0/code_of_conduct/) in all your interactions with the project.

## License

This project is licensed under the [MIT License](LICENSE). You are free to use, modify, and distribute this software as per the terms of the license.
