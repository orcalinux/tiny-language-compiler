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

#include "token.hpp"
#include <sstream>
#include <stdexcept>

namespace TINY
{

    // Constructor to initialize the token with its type, value, and position
    Token::Token(TokenType type, std::string_view value, int line, int column)
        : type(type), value(value), line(line), column(column) {}

    // Returns the type of the token
    TokenType Token::getType() const
    {
        return type;
    }

    // Returns the value of the token as a string
    std::string Token::getValue() const
    {
        return value;
    }

    // Returns the line number where the token was found
    int Token::getLine() const
    {
        return line;
    }

    // Returns the column number where the token was found
    int Token::getColumn() const
    {
        return column;
    }

    // Converts the token type to its string representation using a lookup table
    std::string_view Token::getTokenTypeString() const
    {
        size_t index = static_cast<size_t>(type);

        // Ensure the index is valid and within range
        if (index >= tokenTypeStrings.size())
        {
            throw std::out_of_range("Invalid TokenType index");
        }

        // Return the string representation of the token type
        return tokenTypeStrings[index];
    }

    // Converts the token to a detailed string representation
    std::string Token::toString(bool includePosition) const
    {
        std::ostringstream oss;

        // Add the token type as a string
        oss << getTokenTypeString();

        // Include the token's value, if it exists
        if (!value.empty())
        {
            oss << " (" << value << ")";
        }

        // Optionally include the token's line and column positions
        if (includePosition)
        {
            oss << " [Line: " << line << ", Column: " << column << "]";
        }

        // Return the final string representation
        return oss.str();
    }

} // namespace TINY