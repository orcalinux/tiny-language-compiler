#include "Token.h"

/**
 * @file token.cpp
 * @brief Implements the Token class and related functionality for the TINY language scanner.
 *
 * This file contains the implementation of the Token class, which represents the fundamental units
 * of the TINY language. The key functionalities provided by the Token class include:
 * - Storing information about a token's type, value, and position in the source code.
 * - Converting token details into a string representation for easy debugging and reporting.
 * - Mapping the TokenType enumeration to human-readable strings for better interpretability.
 *
 * The Token class ensures encapsulation and provides a clean interface for interacting
 * with tokens during the lexical analysis phase.
 */

namespace Tiny::Data {
// Constructor to initialize the token with its type, value, and position
Token::Token(TokenType type, QStringView value, int line, int column)
    : type(type), value(value.toString()), line(line), column(column) {}

// Constructor to initialize the token with its type, value, and position
Token::Token(TokenType type, std::string value, int line, int column)
    : type(type), value(QString::fromStdString(value)), line(line), column(column) {}

// Move constructor to efficiently transfer ownership of the token data
Token::Token(Token &&other)
    : type(other.type), value(std::move(other.value)), line(other.line), column(other.column) {}

// Move assignment operator to efficiently transfer ownership of the token data
Token &Token::operator=(Token &&other)
{
    if(this != &other)
    {
        type = other.type;
        value = std::move(other.value);
        line = other.line;
        column = other.column;
    }
    return *this;
}

QStringView Token::getTokenTypeString(TokenType type)
{
    size_t index = static_cast<size_t>(type);

    // Ensure the index is valid and within range
    if (index >= tokenTypeStrings.size()) {
        throw std::out_of_range("Invalid TokenType index");
    }

    // Return the string representation of the token type
    return QStringView(tokenTypeStrings[index].toString());
}

// Returns the type of the token
Token::TokenType Token::getType() const {
    return type;
}

// Returns the value of the token as a string
QString Token::getValue() const {
    return value;
}

// Returns the line number where the token was found
int Token::getLine() const {
    return line;
}

// Returns the column number where the token was found
int Token::getColumn() const {
    return column;
}

// Converts the token to a detailed string representation
QString Token::toString(bool includePosition) const {
    QString str;
    QTextStream stream(&str);

    // Include the token type and value
    stream << value << ", " << getTokenTypeString(type);

    // Optionally include the token's line and column positions
    if (includePosition) {
        stream << " [Line: " << line << ", Column: " << column << "]";
    }

    // Return the final string representation
    return str;
}

QString Token::toHTMLString(bool includePosition) const
{
    QString str;
    QTextStream stream(&str);

    // Use light gray for token value
    if (value == "<"){
        stream << "<span style='color:#c0c0c0;'>&lt;" << value << "&gt;</span>, ";

    } else {
    stream << "<span style='color:#c0c0c0;'>" << value << "</span>, ";
    }

    // Conditional formatting for token type
    if (type == TokenType::UNKNOWN) {
        // Bright red for unknown type
        stream << "<span style='color:#ff5555; font-weight:bold;'>" << getTokenTypeString(type) << "</span>";
    } else if (type != TokenType::NUMBER && type != TokenType::IDENTIFIER && type != TokenType::UNKNOWN) {
        // Light blue for reserved types
        stream << "<span style='color:#5555ff; font-weight:bold;'>" << getTokenTypeString(type) << "</span>";
    } else {
        // Default white for known types
        stream << "<span style='color:#ffffff; font-weight:bold;'>" << getTokenTypeString(type) << "</span>";
    }

    // Optionally include the token's line and column positions
    if (includePosition) {
        stream << " <span style='color:#ff9900;'>[Line: " << line << ", Column: " << column << "]</span>";
    }

    return str;
}

}  // namespace Tiny::Data
