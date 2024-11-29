/**
 * @file token.hpp
 * @brief Defines the Token class and TokenType enumeration for the TINY language scanner.
 *
 * This file provides the representation of tokens in the TINY language. Tokens are the
 * fundamental units produced by the lexical analysis phase.
 */

#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <array>
#include <stdexcept>
#include <string>
#include <string_view>

/**
 * @namespace TINY::SCANNER
 * @brief Contains all components related to the lexical analysis (scanning) of the TINY programming language.
 *
 * The `TINY::SCANNER` namespace organizes all classes, functions, and utilities
 * that are specifically responsible for the lexical analysis phase of the TINY programming language.
 * This includes tokenization, character stream management, and other related components.
 */
namespace TINY::SCANNER
{

    /**
     * @enum TokenType
     * @brief Enumerates the types of tokens in the TINY language.
     */
    enum class TokenType
    {
        IF,            /**< "if" keyword */
        THEN,          /**< "then" keyword */
        END,           /**< "end" keyword */
        REPEAT,        /**< "repeat" keyword */
        UNTIL,         /**< "until" keyword */
        READ,          /**< "read" keyword */
        WRITE,         /**< "write" keyword */
        ASSIGN,        /**< Assignment operator ":=" */
        LESSTHAN,      /**< Less-than operator "<" */
        EQUAL,         /**< Equal operator "=" */
        PLUS,          /**< Addition operator "+" */
        MINUS,         /**< Subtraction operator "-" */
        MULT,          /**< Multiplication operator "*" */
        DIV,           /**< Division operator "/" */
        OPENBRACKET,   /**< Open parenthesis "(" */
        CLOSEDBRACKET, /**< Close parenthesis ")" */
        SEMICOLON,     /**< Semicolon ";" */
        IDENTIFIER,    /**< Identifier (e.g., variable names) */
        NUMBER,        /**< Numeric literal */
        UNKNOWN        /**< Unknown or invalid token */
    };

    /**
     * @class Token
     * @brief Represents a single token in the TINY language.
     *
     * Each token consists of a type, value, and its position in the source code.
     */
    class Token
    {
    public:
        /**
         * @brief Constructs a Token object.
         *
         * @param type The type of the token.
         * @param value The string representation of the token.
         * @param line The line number where the token appears.
         * @param column The column number where the token appears.
         */
        Token(TokenType type, std::string_view value, int line, int column);

        /**
         * @brief Gets the type of the token.
         * @return The token's type.
         */
        TokenType getType() const;

        /**
         * @brief Gets the value of the token.
         * @return The token's value.
         */
        std::string getValue() const;

        /**
         * @brief Gets the line number of the token.
         * @return The line number.
         */
        int getLine() const;

        /**
         * @brief Gets the column number of the token.
         * @return The column number.
         */
        int getColumn() const;

        /**
         * @brief Converts the token to a string representation.
         * @return A string representing the token type and value and optionally its position.
         */
        std::string toString(bool includePosition = false) const;

    private:
        const TokenType type;    /**< The type of the token */
        const std::string value; /**< The value of the token */
        const int line;          /**< The line number of the token */
        const int column;        /**< The column number of the token */

        /**
         * @brief Converts the token type to a string representation.
         *
         * @return A string representing the token type.
         *
         * @throws std::out_of_range if the token type is invalid.
         */
        std::string_view getTokenTypeString() const;

        /**
         * @brief Static constexpr lookup table for token type string representations.
         *
         * This table maps each TokenType enum value to its corresponding string
         * representation for use in debugging and output.
         */
        static constexpr std::array<std::string_view, 20> tokenTypeStrings = {
            "IF",            /**< "if" keyword */
            "THEN",          /**< "then" keyword */
            "END",           /**< "end" keyword */
            "REPEAT",        /**< "repeat" keyword */
            "UNTIL",         /**< "until" keyword */
            "READ",          /**< "read" keyword */
            "WRITE",         /**< "write" keyword */
            "ASSIGN",        /**< Assignment operator ":=" */
            "LESSTHAN",      /**< Less-than operator "<" */
            "EQUAL",         /**< Equal operator "=" */
            "PLUS",          /**< Addition operator "+" */
            "MINUS",         /**< Subtraction operator "-" */
            "MULT",          /**< Multiplication operator "*" */
            "DIV",           /**< Division operator "/" */
            "OPENBRACKET",   /**< Open parenthesis "(" */
            "CLOSEDBRACKET", /**< Close parenthesis ")" */
            "SEMICOLON",     /**< Semicolon ";" */
            "IDENTIFIER",    /**< Identifier (e.g., variable names) */
            "NUMBER",        /**< Numeric literal */
            "UNKNOWN"        /**< Unknown or invalid token */
        };
    };
} // namespace TINY::SCANNER

#endif // TOKEN_HPP
