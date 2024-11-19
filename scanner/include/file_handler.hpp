/**
 * @file file_handler.hpp
 * @brief Defines the FileHandler class for handling file input and output operations.
 *
 * This class abstracts file I/O operations, ensuring separation of concerns
 * between file handling and other parts of the application.
 */

#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "token.hpp"

/**
 * @class FileHandler
 * @brief Provides utility functions for file input and output.
 */
class FileHandler {
   public:
    /**
     * @brief Reads the entire content of a file into a string.
     *
     * @param filePath Path to the file to be read.
     * @return A string containing the file's content.
     * @throws std::runtime_error if the file cannot be opened.
     */
    static std::string readFile(const std::string &filePath);

    /**
     * @brief Writes a vector of strings to a file, each string on a new line.
     *
     * @param filePath Path to the file to be written.
     * @param lines A vector of strings to write to the file.
     * @throws std::runtime_error if the file cannot be opened.
     */
    static void writeTokens(const std::string &filePath, const std::vector<Token> &tokens, bool includePosition = false);

    /**
     * @brief Writes a string to a file.
     *
     * @param filePath Path to the file to be written.
     * @param content A string to write to the file.
     * @throws std::runtime_error if the file cannot be opened.
     */
    static void writeFile(const std::string &filePath, const std::string &content);
};

#endif  // FILE_HANDLER_HPP
