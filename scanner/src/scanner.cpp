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

namespace TINY
{
    /**
     * @namespace SCANNER
     * @brief Contains all components related to the lexical analysis (scanning) of TINY language.
     */
    namespace SCANNER
    {

        Scanner::Scanner(const std::string &input) : input(input) {}

        Token Scanner::getNextToken()
        {
            skipWhitespace();

            if (pos >= input.size())
            {
                return Token(TokenType::UNKNOWN, "", line, column);
            }

            char current = get();

            // Single character tokens
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
                if (peek() == '=')
                {
                    get(); // Consume '='
                    return Token(TokenType::ASSIGN, ":=", line, column);
                }
                return Token(TokenType::COLON, ":", line, column);
            case '<':
                return Token(TokenType::LESSTHAN, "<", line, column);
            case '=':
                return Token(TokenType::EQUAL, "=", line, column);
            }

            // Identifiers and keywords
            if (std::isalpha(current))
            {
                std::string identifier(1, current);
                while (std::isalnum(peek()))
                {
                    identifier += get();
                }

                // Check for keywords
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

                return Token(TokenType::IDENTIFIER, identifier, line, column);
            }

            // Numbers
            if (std::isdigit(current))
            {
                std::string number(1, current);
                while (std::isdigit(peek()))
                {
                    number += get();
                }
                return Token(TokenType::NUMBER, number, line, column);
            }

            // Unknown token
            return Token(TokenType::UNKNOWN, std::string(1, current), line, column);
        }

        bool Scanner::hasMoreTokens() const
        {
            return pos < input.size();
        }

        char Scanner::peek() const
        {
            return pos < input.size() ? input[pos] : '\0';
        }

        char Scanner::get()
        {
            if (pos >= input.size())
            {
                return '\0';
            }

            char currentChar = input[pos++];
            if (currentChar == '\n')
            {
                line++;
                column = 1;
            }
            else
            {
                column++;
            }

            return currentChar;
        }

        void Scanner::skipWhitespace()
        {
            while (std::isspace(peek()))
            {
                get();
            }
        }
    } // namespace SCANNER
} // namespace TINY
