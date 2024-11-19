/**
 * @file scanner.hpp
 * @brief Provides the Scanner class for orchestrating the tokenization process.
 *
 * The Scanner handles file I/O and interacts with the Lexer to tokenize the input.
 */

#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <string>

/**
 * @class Scanner
 * @brief Manages the scanning process for TINY language source code.
 *
 * The Scanner reads input files, tokenizes their content using the Lexer,
 * and writes the tokens to an output file.
 */
class Scanner
{
public:
    /**
     * @brief Runs the scanner with the specified input and output files.
     *
     * @param inputFile Path to the input file containing TINY source code.
     * @param outputFile Path to the output file where tokens will be written.
     */
    static void run(const std::string &inputFile, const std::string &outputFile);
};

#endif // SCANNER_HPP
