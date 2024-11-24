/**
 * @file scanner.cpp
 * @brief Implements the Scanner class for tokenizing TINY language source code.
 *
 * This file contains the implementation of the Scanner class, which is responsible for
 * performing lexical analysis on TINY language source code. It identifies tokens such as
 * keywords, operators, delimiters, and literals.
 */


#include "Scanner.h"

namespace Tiny::Scanner {

using namespace Tiny::Data;

Scanner::Scanner(const QString &input, QObject *parent)
    : input(input), QObject(parent) {}

Token Scanner::getNextToken()
{
    // Skip any whitespace and comments before processing the next token
    bool unclosedComment = skipWhitespaceAndComments();

    // If an unclosed comment was detected, return an UNKNOWN token with an error message
    if (unclosedComment)
    {
        return Token(Token::TokenType::UNKNOWN, "Unclosed comment", line, column);
    }

    // Check if we've reached the end of the input
    if (pos >= input.size())
    {
        // Return an UNKNOWN token to indicate end of input (or define an EOF token if desired)
        return Token(Token::TokenType::UNKNOWN, "", line, column);
    }

    // Get the next character from the input
    QChar current = get();

    // Handle single-character tokens using a switch statement
    switch (current.unicode())
    {
    case '+':
        return Token(Token::TokenType::PLUS, "+", line, column);
    case '-':
        return Token(Token::TokenType::MINUS, "-", line, column);
    case '*':
        return Token(Token::TokenType::MULT, "*", line, column);
    case '/':
        return Token(Token::TokenType::DIV, "/", line, column);
    case '(':
        return Token(Token::TokenType::OPENBRACKET, "(", line, column);
    case ')':
        return Token(Token::TokenType::CLOSEDBRACKET, ")", line, column);
    case ';':
        return Token(Token::TokenType::SEMICOLON, ";", line, column);
    case ':':
        // Check if the next character is '=' to form the ':=' token
        if (peek() == '=')
        {
            get(); // Consume '='
            return Token(Token::TokenType::ASSIGN, ":=", line, column);
        }
        // If not, return an UNKNOWN token for ':'
        return Token(Token::TokenType::UNKNOWN, ":", line, column);
    case '<':
        return Token(Token::TokenType::LESSTHAN, "<", line, column);
    case '=':
        return Token(Token::TokenType::EQUAL, "=", line, column);
    }

    // Identifiers and keywords
    if (current.isLetter())
    {
        QString identifier(1, current); // Start building the identifier

        // Continue consuming alphabetic characters
        while (peek().isLetter())
        {
            identifier += get();
        }

        // Check if the identifier matches any reserved keywords
        if (identifier == "if")
            return Token(Token::TokenType::IF, identifier, line, column);
        if (identifier == "then")
            return Token(Token::TokenType::THEN, identifier, line, column);
        if (identifier == "end")
            return Token(Token::TokenType::END, identifier, line, column);
        if (identifier == "repeat")
            return Token(Token::TokenType::REPEAT, identifier, line, column);
        if (identifier == "until")
            return Token(Token::TokenType::UNTIL, identifier, line, column);
        if (identifier == "read")
            return Token(Token::TokenType::READ, identifier, line, column);
        if (identifier == "write")
            return Token(Token::TokenType::WRITE, identifier, line, column);

        // If not a keyword, it's an identifier
        return Token(Token::TokenType::IDENTIFIER, identifier, line, column);
    }

    // Numbers (integer literals)
    if (current.isDigit())
    {
        QString number(1, current); // Start building the number literal

        // Continue consuming digit characters
        while (peek().isDigit())
        {
            number += get();
        }

        // Return a NUMBER token
        return Token(Token::TokenType::NUMBER, number, line, column);
    }

    // If the character doesn't match any known token patterns, return an UNKNOWN token
    return Token(Token::Token::TokenType::UNKNOWN, QString(1, current), line, column);
}

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

QChar Scanner::peek() const
{
    // Return the next character if within bounds, or '\0' if at the end
    return pos < input.size() ? input[pos] : '\0';

}

QChar Scanner::get()
{
    // Check if at the end of input
    if (pos >= input.size())
    {
        return '\0';
    }

    QChar currentChar = input[pos++]; // Get the current character and advance position

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

void Scanner::skipWhitespace()
{
    // Consume all consecutive whitespace characters
    while (pos < input.size() && peek().isSpace())
    {
        get(); // Consume the whitespace character
    }
}

bool Scanner::skipComments()
{
    if (pos < input.size() && peek() == '{')
    {
        get(); // Consume initial '{'
        QStack<QChar> commentStack;
        commentStack.push('{'); // Push the initial '{' onto the stack

        while (pos < input.size())
        {
            QChar currentChar = get();

            if (currentChar == '{')
            {
                commentStack.push('{'); // Push nested '{' onto the stack
            }
            else if (currentChar == '}')
            {
                commentStack.pop(); // Pop a '{' from the stack

                if (commentStack.isEmpty())
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
        if (!peek().isSpace() && peek() != '{')
        {
            break;
        }
    }
    // No unclosed comment detected
    return false;
}

}  // namespace Tiny::Scanner
