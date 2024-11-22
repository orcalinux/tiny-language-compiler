/**
 * @file Scanner.hpp
 * @brief Defines the Scanner class for tokenizing TINY language source code.
 *
 * The Scanner is responsible for reading the source code, identifying tokens,
 * and handling special cases such as invalid characters.
 */

#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <string>
#include <vector>

#include "token.hpp"

/**
 * @namespace TINY
 * @brief Contains all components of the TINY language scanner.
 *
 * The `TINY` namespace organizes all classes, functions, and utilities
 * related to the lexical analysis of the TINY programming language.
 */
namespace TINY
{
    /**
     * @namespace SCANNER
     * @brief Contains all components related to the lexical analysis (scanning) of TINY language.
     */
    namespace SCANNER
    {

        /**
         * @class Scanner
         * @brief Performs lexical analysis on TINY language source code.
         *
         * The `Scanner` processes input source code to produce a sequence of tokens.
         * It identifies keywords, operators, delimiters, and literals, and it reports
         * invalid characters as necessary.
         */
        class Scanner
        {
        public:
            /**
             * @brief Constructs a `Scanner` object with the given input string.
             *
             * This constructor initializes the `Scanner` with the source code that
             * needs to be tokenized.
             *
             * @param input The source code to be tokenized.
             */
            Scanner(const std::string &input);

            /**
             * @brief Extracts the next token from the input source code.
             *
             * This method processes the source code and returns the next token
             * identified by the `Scanner`.
             *
             * @return The next token.
             */
            Token getNextToken();

            /**
             * @brief Checks if there are more tokens to be extracted.
             *
             * This method determines if the end of the source code has been reached.
             *
             * @return True if there are more tokens, false otherwise.
             */
            bool hasMoreTokens() const;

        private:
            std::string input; /**< The source code to be tokenized. */
            size_t pos = 0;    /**< Current position in the input string. */
            int line = 1;      /**< Current line number in the source code. */
            int column = 1;    /**< Current column number in the source code. */

            /**
             * @brief Peeks at the next character in the input without advancing the position.
             *
             * This method allows inspecting the next character in the source code
             * without consuming it.
             *
             * @return The next character in the input.
             */
            char peek() const;

            /**
             * @brief Gets the next character in the input and advances the position.
             *
             * This method reads the next character from the source code and moves
             * the cursor forward.
             *
             * @return The next character in the input.
             */
            char get();

            /**
             * @brief Skips over whitespace characters in the input.
             *
             * This method advances the cursor past any whitespace characters
             * encountered in the source code.
             */
            void skipWhitespace();
        };
    } // namespace SCANNER

} // namespace TINY

#endif // SCANNER_HPP
