/**
 * @file file_handler.hpp
 * @brief Defines the FileHandler class for handling file input and output operations.
 *
 * This class abstracts file I/O operations, ensuring separation of concerns
 * between file handling and other parts of the application.
 */

#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
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
namespace TINY {
/**
 * @namespace SCANNER
 * @brief Contains all components related to the lexical analysis (scanning) of TINY language.
 */
namespace SCANNER {

/**
 * @class FileHandler
 * @brief Provides utility functions for file input and output.
 *
 * The `FileHandler` class offers static methods to perform file operations,
 * including reading files, writing tokens to files, and writing content to files.
 */
class FileHandler {
   public:
    /**
     * @brief Reads the entire content of a file into a string.
     *
     * This method opens the file at the specified path and reads its contents into a single string.
     * If the file cannot be opened, it throws a runtime exception.
     *
     * @param filePath Path to the file to be read.
     * @return A string containing the file's content.
     * @throws std::runtime_error if the file cannot be opened.
     */
    static std::string readFile(const std::string &filePath);

    /**
     * @brief Writes a vector of tokens to a file, each token on a new line.
     *
     * This method takes a vector of `Token` objects and writes their string representation to the file.
     * If the `includePosition` flag is true, the position of each token is also included in the output.
     *
     * @param filePath Path to the file to be written.
     * @param tokens A vector of `Token` objects to write to the file.
     * @param includePosition Whether to include token position in the output (default is false).
     * @throws std::runtime_error if the file cannot be opened.
     */
    static void writeTokens(const std::string &filePath, const std::vector<Token> &tokens, bool includePosition = false);

    /**
     * @brief Writes a string to a file.
     *
     * This method writes the provided string to the file at the specified path.
     * If the file cannot be opened, it throws a runtime exception.
     *
     * @param filePath Path to the file to be written.
     * @param content A string to write to the file.
     * @throws std::runtime_error if the file cannot be opened.
     */
    static void writeFile(const std::string &filePath, const std::string &content);
};
}  // namespace SCANNER
}  // namespace TINY

#endif  // FILE_HANDLER_HPP
