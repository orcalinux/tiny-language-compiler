#include "parser.hpp"
#include "token.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip> // For std::setw, std::left, etc.
#include <chrono>  // For timing

// Function to enable ANSI escape codes on Windows (Assuming it's defined elsewhere)
#ifdef _WIN32
void enableVirtualTerminal()
{
    // Implementation to enable ANSI escape codes on Windows
    // This is a placeholder. Ensure you have the actual implementation.
}
#endif

// Enable ANSI escape codes on Windows
#ifdef _WIN32
enableVirtualTerminal();
#endif

// ANSI color codes
const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string CYAN = "\033[36m";
const std::string BOLD = "\033[1m";

// Function to simulate token list (Replace this with actual token input)
std::vector<Token> getTestTokens(int testCase)
{
    switch (testCase)
    {
    case 1: // Simple Read and Write
        return {
            Token(TokenType::READ, "read"),
            Token(TokenType::IDENTIFIER, "x"),
            Token(TokenType::SEMICOLON, ";"),
            Token(TokenType::WRITE, "write"),
            Token(TokenType::IDENTIFIER, "x"),
            Token(TokenType::END_OF_INPUT, "$")};
    case 2: // If Statement Without Else
        return {
            Token(TokenType::IF, "if"),
            Token(TokenType::IDENTIFIER, "x"),
            Token(TokenType::LT, "<"),
            Token(TokenType::NUMBER, "10"),
            Token(TokenType::THEN, "then"),
            Token(TokenType::WRITE, "write"),
            Token(TokenType::IDENTIFIER, "x"),
            Token(TokenType::END, "end"),
            Token(TokenType::END_OF_INPUT, "$")};
    case 3: // If Statement With Else
        return {
            Token(TokenType::IF, "if"),
            Token(TokenType::IDENTIFIER, "x"),
            Token(TokenType::LT, "<"),
            Token(TokenType::NUMBER, "10"),
            Token(TokenType::THEN, "then"),
            Token(TokenType::WRITE, "write"),
            Token(TokenType::IDENTIFIER, "x"),
            Token(TokenType::ELSE, "else"),
            Token(TokenType::WRITE, "write"),
            Token(TokenType::IDENTIFIER, "y"),
            Token(TokenType::END, "end"),
            Token(TokenType::END_OF_INPUT, "$")};
    case 4: // Repeat Loop
        return {
            Token(TokenType::REPEAT, "repeat"),
            Token(TokenType::READ, "read"),
            Token(TokenType::IDENTIFIER, "x"),
            Token(TokenType::SEMICOLON, ";"),
            Token(TokenType::WRITE, "write"),
            Token(TokenType::IDENTIFIER, "x"),
            Token(TokenType::UNTIL, "until"),
            Token(TokenType::IDENTIFIER, "x"),
            Token(TokenType::EQ, "="),
            Token(TokenType::NUMBER, "0"),
            Token(TokenType::END_OF_INPUT, "$")};
    case 5: // Missing 'end' in If Statement
        return {
            Token(TokenType::IF, "if"),
            Token(TokenType::IDENTIFIER, "x"),
            Token(TokenType::LT, "<"),
            Token(TokenType::NUMBER, "10"),
            Token(TokenType::THEN, "then"),
            Token(TokenType::WRITE, "write"),
            Token(TokenType::IDENTIFIER, "x"),
            Token(TokenType::END_OF_INPUT, "$") // Missing "end"
        };
    case 6: // Unexpected Token
        return {
            Token(TokenType::READ, "read"),
            Token(TokenType::IDENTIFIER, "x"),
            Token(TokenType::WRITE, "write"),
            Token(TokenType::SEMICOLON, ";"),
            Token(TokenType::IDENTIFIER, "y"),
            Token(TokenType::END_OF_INPUT, "$")};
    case 7: // Missing Semicolon
        return {
            Token(TokenType::READ, "read"),
            Token(TokenType::IDENTIFIER, "x"),
            // Missing SEMICOLON
            Token(TokenType::WRITE, "write"),
            Token(TokenType::IDENTIFIER, "x"),
            Token(TokenType::END_OF_INPUT, "$")};
    default: // Default Test Case
        return {
            Token(TokenType::READ, "read"),
            Token(TokenType::IDENTIFIER, "x"),
            Token(TokenType::SEMICOLON, ";"),
            Token(TokenType::IF, "if"),
            Token(TokenType::IDENTIFIER, "x"),
            Token(TokenType::LT, "<"),
            Token(TokenType::NUMBER, "10"),
            Token(TokenType::THEN, "then"),
            Token(TokenType::WRITE, "write"),
            Token(TokenType::IDENTIFIER, "x"),
            Token(TokenType::END, "end"),
            Token(TokenType::END_OF_INPUT, "$")};
    }
}

// Structure to hold test case information
struct TestCase
{
    int id;
    std::string description;
};

// Function to initialize all test cases with their descriptions
std::vector<TestCase> initializeTestCases()
{
    return {
        {1, "Simple Read and Write"},
        {2, "If Statement Without Else"},
        {3, "If Statement With Else"},
        {4, "Repeat Loop"},
        {5, "Missing 'end' in If Statement"},
        {6, "Unexpected Token"},
        {7, "Missing Semicolon"}};
}

// Helper function to print formatted test results
void printTestResult(int id, const std::string &description, bool success, double time_us, size_t maxDescLen)
{
    // Define column widths
    const int descriptionWidth = static_cast<int>(maxDescLen) + 2; // Adding padding

    std::cout << "Test Case " << id << ": ";

    // Description
    std::cout << std::left << std::setw(descriptionWidth) << description << " - ";

    // Parse Result with fixed width and coloring
    if (success)
    {
        std::cout << GREEN << "Parse Success" << RESET;
    }
    else
    {
        std::cout << RED << "Parse Failure" << RESET;
    }

    // Add padding spaces to ensure alignment (assuming "Parse Success" and "Parse Failure" are 13 chars)
    std::cout << "  "; // Two spaces

    // Time
    std::cout << "| Time: " << YELLOW << std::fixed << std::setprecision(3) << time_us << " µs" << RESET << std::endl;
}

int main()
{
    // Initialize all test cases
    std::vector<TestCase> testCases = initializeTestCases();

    // Counters for passed and failed tests
    int passedTests = 0;
    int failedTests = 0;

    std::cout << "Starting All Test Cases...\n"
              << std::endl;

    // Determine the maximum description length for alignment
    size_t maxDescriptionLength = 0;
    for (const auto &testCase : testCases)
    {
        if (testCase.description.length() > maxDescriptionLength)
            maxDescriptionLength = testCase.description.length();
    }

    // Iterate through each test case in order
    for (const auto &testCase : testCases)
    {
        // Get tokens for the current test case
        std::vector<Token> tokens = getTestTokens(testCase.id);

        // Initialize the parser with tokens
        Parser parser(tokens);

        // Start the timer before parsing
        auto start = std::chrono::high_resolution_clock::now();

        // Parse the tokens
        bool success = parser.parse();

        // End the timer after parsing
        auto end = std::chrono::high_resolution_clock::now();

        // Calculate the duration in microseconds
        std::chrono::duration<double, std::micro> duration = end - start;

        // Print the formatted test result
        printTestResult(testCase.id, testCase.description, success, duration.count(), maxDescriptionLength);

        // Update counters
        if (success)
            passedTests++;
        else
            failedTests++;
    }

    // Summary of test results
    std::cout << "\n"
              << BOLD << CYAN << "========================================" << RESET << std::endl;
    std::cout << BOLD << CYAN << "              TEST SUMMARY              " << RESET << std::endl;
    std::cout << BOLD << CYAN << "========================================" << RESET << std::endl;
    // Test results
    std::cout << BOLD << "Total Tests Run  : " << RESET << testCases.size() << std::endl;
    std::cout << BOLD << GREEN << "Passed           : " << passedTests << RESET << std::endl;
    std::cout << BOLD << RED << "Failed           : " << failedTests << RESET << std::endl;
    // Footer
    std::cout << BOLD << CYAN << "========================================" << RESET << std::endl;

    return 0;
}
