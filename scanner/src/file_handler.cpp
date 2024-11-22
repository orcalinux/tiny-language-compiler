/**
 * @file file_handler.cpp
 * @brief Implements the FileHandler class for managing file input and output operations in the TINY language scanner.
 *
 * This file provides the implementation of the FileHandler class, which abstracts file I/O operations, ensuring
 * separation of concerns between file handling and other parts of the application. The key functionalities include:
 * - Reading the content of a file into a string.
 * - Writing tokens or text content to a specified file.
 *
 * The FileHandler class is designed to provide robust error handling and ensure smooth interaction with the filesystem.
 */

#include "file_handler.hpp"

namespace TINY
{
    /**
     * @namespace SCANNER
     * @brief Contains all components related to the lexical analysis (scanning) of TINY language.
     */
    namespace SCANNER
    {

        std::string FileHandler::readFile(const std::string &filePath)
        {
            // Open the file at the given path
            std::ifstream file(filePath);

            // Check if the file was opened successfully
            if (!file.is_open())
            {
                throw std::runtime_error("Failed to open file: " + filePath);
            }

            // Read the entire file content into a string
            return std::string(
                (std::istreambuf_iterator<char>(file)),
                std::istreambuf_iterator<char>());
        }

        void FileHandler::writeTokens(const std::string &filePath, const std::vector<Token> &tokens,
                                      bool includePosition)
        {
            // Create a string file content from the tokens
            std::ostringstream contentStream;
            for (const Token &token : tokens)
            {
                contentStream << token.toString(includePosition) << "\n";
            }

            // Write the file content to the file at the given path
            FileHandler::writeFile(filePath, contentStream.str());
        }

        void FileHandler::writeFile(const std::string &filePath, const std::string &content)
        {
            // Open the file at the given path
            std::ofstream file(filePath);

            // Check if the file was opened successfully
            if (!file.is_open())
            {
                throw std::runtime_error("Failed to open file: " + filePath);
            }

            // Write the content to the file
            file << content;
        }
    } // namespace SCANNER

} // namespace TINY
