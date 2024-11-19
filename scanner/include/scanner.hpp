/**
 * @file Scanner.hpp
 * @brief Defines the Scanner class for tokenizing TINY language source code.
 *
 * The Scanner is responsible for reading the source code, identifying tokens,
 * and handling special cases such as invalid characters.
 */

#ifndef Scanner_HPP
#define Scanner_HPP

#include <string>
#include <vector>

#include "token.hpp"

/**
 * @class Scanner
 * @brief Performs lexical analysis on TINY language source code.
 *
 * The Scanner processes input source code to produce a sequence of tokens.
 */
class Scanner {
   public:
    /**
     * @brief Constructs a Scanner object with the given input string.
     *
     * @param input The source code to be tokenized.
     */
    Scanner(const std::string &input);

    /**
     * @brief Extracts the next token from the input.
     *
     * @return The next token.
     */
    Token getNextToken();

    /**
     * @brief Checks if there are more tokens to be extracted.
     *
     * @return True if there are more tokens, false otherwise.
     */
    bool hasMoreTokens() const;

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
};

#endif  // Scanner_HPP
