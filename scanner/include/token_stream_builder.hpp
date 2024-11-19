/**
 * @file TokenStreamBuilder.hpp
 * @brief Provides the TokenStreamBuilder class for orchestrating the tokenization process.
 *
 * The TokenStreamBuilder handles file I/O and interacts with the Lexer to tokenize the input.
 */

#ifndef TokenStreamBuilder_HPP
#define TokenStreamBuilder_HPP

#include <string>

/**
 * @class TokenStreamBuilder
 * @brief Manages the scanning process for TINY language source code.
 *
 * The TokenStreamBuilder reads input files, tokenizes their content using the Lexer,
 * and writes the tokens to an output file.
 */
class TokenStreamBuilder
{
public:
    /**
     * @brief Runs the TokenStreamBuilder with the specified input and output files.
     *
     * @param inputFile Path to the input file containing TINY source code.
     * @param outputFile Path to the output file where tokens will be written.
     */
    static void run(const std::string &inputFile, const std::string &outputFile);
};

#endif // TokenStreamBuilder_HPP
