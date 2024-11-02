# TINY Language Scanner

## Table of Contents

1. [Overview](#overview)
2. [List of Tokens](#list-of-tokens)
3. [Project Structure](#project-structure)
4. [How to Use](#how-to-use)
5. [Deliverables](#deliverables)
6. [Team](#team)
7. [Technical Requirements](#technical-requirements)
8. [Deadline](#deadline)

## Overview

This project is a scanner for the **TINY language**, which is a simple language often used in educational settings for teaching compiler design concepts. The scanner processes code written in the TINY language and identifies its lexical components, converting them into tokens.

### Inputs

The scanner reads a text file containing TINY language syntax, which can span multiple lines.

### Output

The scanner generates a list of tokens in the format `(token value, token type)` and writes the results to an output file.

#### Example

Given the input code:

```
x := 4;
```

The scanner produces the following output:

```
x  , Identifier
:= , ASSIGN
4  , NUMBER
;  , SEMICOLON
```

## List of Tokens

The scanner identifies the following tokens in the TINY language:

| Token Type    | Example     |
| ------------- | ----------- |
| SEMICOLON     | `;`         |
| IF            | `if`        |
| THEN          | `then`      |
| END           | `end`       |
| REPEAT        | `repeat`    |
| UNTIL         | `until`     |
| IDENTIFIER    | `x`, `abc`  |
| ASSIGN        | `:=`        |
| READ          | `read`      |
| WRITE         | `write`     |
| LESSTHAN      | `<`         |
| EQUAL         | `=`         |
| PLUS          | `+`         |
| MINUS         | `-`         |
| MULT          | `*`         |
| DIV           | `/`         |
| OPENBRACKET   | `(`         |
| CLOSEDBRACKET | `)`         |
| NUMBER        | `12`, `289` |

## Project Structure

The project repository is structured as follows:

```
Scanner/
│
├── src/
│   ├── scanner.cpp       # Implementation of the Scanner class
│   ├── token.cpp         # Implementation of the Token class
│   ├── lexer.cpp         # Implementation of the Lexer class
│   └── utils.cpp         # Implementation of utility functions
│
├── include/
│   ├── scanner.hpp       # Header for the Scanner class
│   ├── token.hpp         # Header for the Token class
│   ├── lexer.hpp         # Header for the Lexer class
│   └── utils.hpp         # Header for utility functions
│
├── examples/
│   ├── example1.txt      # Sample TINY language code for testing
│   └── example2.txt      # Another sample input file
│
├── output/
│   └── output.txt        # Output file for scanner results
│
├── docs/
│   └── scanner_doc.md    # Documentation for the scanner
│
└── README.md             # Documentation for the project
```

## How to Use

### Prerequisites

- **C++ Compiler**: Ensure you have a C++ compiler installed (e.g., `g++`).
- **Git**: To clone the repository and manage version control.

### Steps to Run

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/OrcaLinux/Design-of-Compilers
   cd Design-of-Compilers/scanner
   ```

2. **Compile the Scanner**:

   ```bash
   g++ src/scanner.cpp src/utils.cpp -Iinclude -o scanner
   ```

3. **Run the Scanner**:

   ```bash
   ./scanner examples/example1.txt output/output.txt
   ```

4. **View the Output**:
   Open `output/output.txt` to see the list of generated tokens.

## Deliverables

- **Executable**: Compiled scanner that can run as an independent executable.
- **Snapshots**: Screenshots demonstrating the scanner’s functionality.
- **Source Code**: All source code files related to the scanner.

## Team

The project allows teams of up to 6 members. Each member contributes to the development, testing, and documentation of the scanner.

## Technical Requirements

- The scanner must be developed in C++ and compiled into an executable format compatible with Windows and Linux.
- The program should run independently without the need for third-party tools.

## Deadline

The scanner project must be submitted by **Saturday, November 23**.
