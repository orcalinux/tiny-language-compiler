#include "file_handler.hpp"

std::string FileHandler::readFile(const std::string& filePath) {
    // Open the file at the given path
    std::ifstream file(filePath);

    // Check if the file was opened successfully
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filePath);
    }

    // Read the entire file content into a string
    return std::string(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());
}

void FileHandler::writeTokens(const std::string& filePath, const std::vector<Token>& tokens,
                              bool includePosition) {
    // Create a string file content from the tokens
    std::ostringstream contentStream;
    for (const Token& token : tokens) {
        contentStream << token.toString(includePosition) << "\n";
    }

    // Write the file content to the file at the given path
    FileHandler::writeFile(filePath, contentStream.str());
}

void FileHandler::writeFile(const std::string& filePath, const std::string& content) {
    // Open the file at the given path
    std::ofstream file(filePath);

    // Check if the file was opened successfully
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filePath);
    }

    // Write the content to the file
    file << content;
}
