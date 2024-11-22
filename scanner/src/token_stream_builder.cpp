/**
 * @file TokenStreamBuilder.cpp
 * @brief Implements the TokenStreamBuilder class for orchestrating the tokenization process.
 *
 * The TokenStreamBuilder class handles tokenization by utilizing the Scanner
 * to generate tokens and stores them in a vector for further processing.
 */

#include "token_stream_builder.hpp"

namespace TINY
{
    namespace SCANNER
    {

        /**
         * @brief Constructs a TokenStreamBuilder object with the given Scanner object.
         *
         * @param scanner The Scanner object to be used for tokenization.
         */
        TokenStreamBuilder::TokenStreamBuilder(Scanner &scanner) : scanner(scanner) {}

        /**
         * @brief Tokenizes the input source code and stores the tokens in a vector.
         *
         * This method uses the Scanner object to generate tokens until all tokens
         * are processed. The tokens are stored in the `tokens` vector.
         */
        void TokenStreamBuilder::build()
        {
            tokens.clear(); // Clear any existing tokens in the vector
            while (scanner.hasMoreTokens())
            {
                tokens.push_back(scanner.getNextToken());
            }
        }

        /**
         * @brief Retrieves the vector of tokens generated from the input source code.
         *
         * @return A constant reference to the vector of tokens.
         */
        const std::vector<Token> &TokenStreamBuilder::getTokens() const
        {
            return tokens;
        }

    } // namespace SCANNER
} // namespace TINY
