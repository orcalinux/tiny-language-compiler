/**
 * @file lexer.hpp
 * @brief Defines the Lexer class for tokenizing TINY language source code.
 *
 * The Lexer is responsible for reading the source code, identifying tokens,
 * and handling special cases such as comments and invalid characters.
 */

#ifndef LEXER_HPP
#define LEXER_HPP

#include <vector>
#include <string>
#include "token.hpp"

/**
 * @class Lexer
 * @brief Performs lexical analysis on TINY language source code.
 *
 * The Lexer processes input source code to produce a sequence of tokens.
 */
class Lexer
{
public:
    /**
     * @brief Constructs a Lexer object with the given input string.
     *
     * @param input The source code to be tokenized.
     */
    Lexer(const std::string &input);

    /**
     * @brief Tokenizes the input source code.
     *
     * @return A vector of tokens produced from the source code.
     */
    std::vector<Token> tokenize();

private:
    std::string input; /**< The source code to be tokenized */
    size_t pos = 0;    /**< Current position in the input string */
    int line = 1;      /**< Current line number */
    int column = 1;    /**< Current column number */

    /**
     * @brief Peeks at the next character in the input without advancing the position.
     *
     * @return The next character.
     */
    char peek() const;

    /**
     * @brief Gets the next character in the input and advances the position.
     *
     * @return The next character.
     */
    char get();

    /**
     * @brief Skips over whitespace characters in the input.
     */
    void skipWhitespace();

    /**
     * @brief Extracts the next token from the input.
     *
     * @return The next token.
     */
    Token getToken();
};

#endif // LEXER_HPP
