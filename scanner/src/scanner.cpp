/**
 * @file scanner.cpp
 * @brief Implements the Scanner class for tokenizing TINY language source code.
 *
 * This file contains the implementation of the Scanner class, which is responsible for
 * performing lexical analysis on TINY language source code. It identifies tokens such as
 * keywords, operators, delimiters, and literals.
 */

#include "scanner.hpp"
#include <cctype>
#include <stdexcept>
#include <stack>

namespace TINY
{
    namespace SCANNER
    {

        // Constructor: Initializes the Scanner with the input source code
        Scanner::Scanner(const std::string &input) : input(input) {}

        // Extracts the next token from the input source code
        Token Scanner::getNextToken()
        {
            // Skip any whitespace and comments before processing the next token
            bool unclosedComment = skipWhitespaceAndComments();

            // If an unclosed comment was detected, return an UNKNOWN token with an error message
            if (unclosedComment)
            {
                return Token(TokenType::UNKNOWN, "Unclosed comment", line, column);
            }

            // Check if we've reached the end of the input
            if (pos >= input.size())
            {
                // Return an UNKNOWN token to indicate end of input (or define an EOF token if desired)
                return Token(TokenType::UNKNOWN, "", line, column);
            }

            // Get the next character from the input
            char current = get();

            // Handle single-character tokens using a switch statement
            switch (current)
            {
            case '+':
                return Token(TokenType::PLUS, "+", line, column);
            case '-':
                return Token(TokenType::MINUS, "-", line, column);
            case '*':
                return Token(TokenType::MULT, "*", line, column);
            case '/':
                return Token(TokenType::DIV, "/", line, column);
            case '(':
                return Token(TokenType::OPENBRACKET, "(", line, column);
            case ')':
                return Token(TokenType::CLOSEDBRACKET, ")", line, column);
            case ';':
                return Token(TokenType::SEMICOLON, ";", line, column);
            case ':':
                // Check if the next character is '=' to form the ':=' token
                if (peek() == '=')
                {
                    get(); // Consume '='
                    return Token(TokenType::ASSIGN, ":=", line, column);
                }
                // If not, return an UNKNOWN token for ':'
                return Token(TokenType::UNKNOWN, ":", line, column);
            case '<':
                return Token(TokenType::LESSTHAN, "<", line, column);
            case '=':
                return Token(TokenType::EQUAL, "=", line, column);
            }

            // Identifiers and keywords
            if (std::isalpha(current))
            {
                std::string identifier(1, current); // Start building the identifier

                // Continue consuming alphabetic characters
                while (std::isalpha(peek()))
                {
                    identifier += get();
                }

                // Check if the identifier matches any reserved keywords
                if (identifier == "if")
                    return Token(TokenType::IF, identifier, line, column);
                if (identifier == "then")
                    return Token(TokenType::THEN, identifier, line, column);
                if (identifier == "end")
                    return Token(TokenType::END, identifier, line, column);
                if (identifier == "repeat")
                    return Token(TokenType::REPEAT, identifier, line, column);
                if (identifier == "until")
                    return Token(TokenType::UNTIL, identifier, line, column);
                if (identifier == "read")
                    return Token(TokenType::READ, identifier, line, column);
                if (identifier == "write")
                    return Token(TokenType::WRITE, identifier, line, column);

                // If not a keyword, it's an identifier
                return Token(TokenType::IDENTIFIER, identifier, line, column);
            }

            // Numbers (integer literals)
            if (std::isdigit(current))
            {
                std::string number(1, current); // Start building the number literal

                // Continue consuming digit characters
                while (std::isdigit(peek()))
                {
                    number += get();
                }

                // Return a NUMBER token
                return Token(TokenType::NUMBER, number, line, column);
            }

            // If the character doesn't match any known token patterns, return an UNKNOWN token
            return Token(TokenType::UNKNOWN, std::string(1, current), line, column);
        }

        // Checks if there are more tokens to be extracted
        bool Scanner::hasMoreTokens()
        {
            // Save the current state to avoid modifying the scanner's actual state
            size_t tempPos = pos;
            int tempLine = line;
            int tempColumn = column;

            // Temporarily skip whitespace and comments
            bool unclosedComment = skipWhitespaceAndComments();

            // Determine if there are more tokens
            bool hasMore = (pos < input.size()) && !unclosedComment;

            // Restore the scanner's state
            pos = tempPos;
            line = tempLine;
            column = tempColumn;

            return hasMore;
        }

        // Skips over whitespace and comments in the input
        bool Scanner::skipWhitespaceAndComments()
        {
            while (true)
            {
                skipWhitespace();

                bool unclosedComment = skipComments();
                if (unclosedComment)
                {
                    // Unclosed comment detected; return true to indicate error
                    return true;
                }

                // If no more whitespace or comments, break out of the loop
                if (!std::isspace(peek()) && peek() != '{')
                {
                    break;
                }
            }
            // No unclosed comment detected
            return false;
        }

        // Skips over whitespace characters in the input
        void Scanner::skipWhitespace()
        {
            // Consume all consecutive whitespace characters
            while (pos < input.size() && std::isspace(peek()))
            {
                get(); // Consume the whitespace character
            }
        }

        // Skips over comments in the input source code
        bool Scanner::skipComments()
        {
            if (pos < input.size() && peek() == '{')
            {
                get(); // Consume initial '{'
                std::stack<char> commentStack;
                commentStack.push('{'); // Push the initial '{' onto the stack

                while (pos < input.size())
                {
                    char currentChar = get();

                    if (currentChar == '{')
                    {
                        commentStack.push('{'); // Push nested '{' onto the stack
                    }
                    else if (currentChar == '}')
                    {
                        commentStack.pop(); // Pop a '{' from the stack

                        if (commentStack.empty())
                        {
                            // All comments are closed
                            skipWhitespace(); // Skip whitespace after comment
                            return false;     // Comment was successfully skipped
                        }
                    }
                    else if (currentChar == '\0')
                    {
                        // End of input reached unexpectedly
                        return true; // Unclosed comment detected
                    }
                    // Continue consuming characters inside the comment
                }

                // EOF reached before all comments were closed
                return true; // Unclosed comment detected
            }
            return false; // No comment to skip
        }

        // Peeks at the next character in the input without advancing the position
        char Scanner::peek() const
        {
            // Return the next character if within bounds, or '\0' if at the end
            return pos < input.size() ? input[pos] : '\0';
        }

        // Gets the next character in the input and advances the position
        char Scanner::get()
        {
            // Check if at the end of input
            if (pos >= input.size())
            {
                return '\0';
            }

            char currentChar = input[pos++]; // Get the current character and advance position

            // Update line and column numbers for error reporting and tracking
            if (currentChar == '\n')
            {
                line++;     // Move to the next line
                column = 1; // Reset column number
            }
            else
            {
                column++; // Move to the next column
            }

            return currentChar;
        }

    } // namespace SCANNER
} // namespace TINY
