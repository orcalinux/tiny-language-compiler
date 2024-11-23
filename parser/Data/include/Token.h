/**
 * @file token.h
 * @brief Defines the Token class and TokenType enumeration for the TINY language scanner.
 *
 * This file provides the representation of tokens in the TINY language. Tokens are the
 * fundamental units produced by the lexical analysis phase.
 */

#ifndef TOKEN_H
#define TOKEN_H

#include <QLatin1StringView>
#include <QObject>
#include <QString>
#include <QStringView>
#include <QTextStream>

#include <array>
#include <stdexcept>

/**
 * @namespace TINY
 * @brief Contains all components of the TINY language scanner.
 *
 * The `TINY` namespace organizes all classes, functions, and utilities
 * related to the lexical analysis of the TINY programming language.
 */
namespace Tiny::Data {
/**
 * @class Token
 * @brief Represents a single token in the TINY language.
 *
 * Each token consists of a type, value, and its position in the source code.
 */
class Token : public QObject {
   public:
    /**
     * @enum TokenType
     * @brief Enumerates the types of tokens in the TINY language.
     */
    enum class TokenType {
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
    Q_ENUM(TokenType)

    /**
     * @brief Constructs a Token object.
     *
     * @param type The type of the token.
     * @param value The string representation of the token.
     * @param line The line number where the token appears.
     * @param column The column number where the token appears.
     */
    Token(TokenType type, QStringView value, int line, int column, QObject *parent);

    /**
     * @brief Gets the type of the token.
     * @return The token's type.
     */
    TokenType getType() const;

    /**
     * @brief Gets the value of the token.
     * @return The token's value.
     */
    QString getValue() const;

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
    QString toString(bool includePosition = false) const;

   private:
    const TokenType type; /**< The type of the token */
    const QString value;  /**< The value of the token */
    const int line;       /**< The line number of the token */
    const int column;     /**< The column number of the token */

    /**
     * @brief Converts the token type to a string representation.
     *
     * @return A string representing the token type.
     *
     * @throws std::out_of_range if the token type is invalid.
     */
    QStringView getTokenTypeString() const;

    /**
     * @brief Static constexpr lookup table for token type string representations.
     *
     * This table maps each TokenType enum value to its corresponding string
     * representation for use in debugging and output.
     */
    static constexpr std::array<QLatin1StringView, 20> tokenTypeStrings = {
        QLatin1StringView("IF"),            /**< "if" keyword */
        QLatin1StringView("THEN"),          /**< "then" keyword */
        QLatin1StringView("END"),           /**< "end" keyword */
        QLatin1StringView("REPEAT"),        /**< "repeat" keyword */
        QLatin1StringView("UNTIL"),         /**< "until" keyword */
        QLatin1StringView("READ"),          /**< "read" keyword */
        QLatin1StringView("WRITE"),         /**< "write" keyword */
        QLatin1StringView("ASSIGN"),        /**< Assignment operator ":=" */
        QLatin1StringView("LESSTHAN"),      /**< Less-than operator "<" */
        QLatin1StringView("EQUAL"),         /**< Equal operator "=" */
        QLatin1StringView("PLUS"),          /**< Addition operator "+" */
        QLatin1StringView("MINUS"),         /**< Subtraction operator "-" */
        QLatin1StringView("MULT"),          /**< Multiplication operator "*" */
        QLatin1StringView("DIV"),           /**< Division operator "/" */
        QLatin1StringView("OPENBRACKET"),   /**< Open parenthesis "(" */
        QLatin1StringView("CLOSEDBRACKET"), /**< Close parenthesis ")" */
        QLatin1StringView("SEMICOLON"),     /**< Semicolon ";" */
        QLatin1StringView("IDENTIFIER"),    /**< Identifier (e.g., variable names) */
        QLatin1StringView("NUMBER"),        /**< Numeric literal */
        QLatin1StringView("UNKNOWN")        /**< Unknown or invalid token */
    };
};
}  // namespace Tiny::Data

#endif  // TOKEN_H
