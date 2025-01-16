#include "parser.hpp"
#include "token.hpp"
#include <iostream>
#include <vector>
#include <string>

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

int main()
{
    // Initialize all test cases
    std::vector<TestCase> testCases = initializeTestCases();

    // Counters for passed and failed tests
    int passedTests = 0;
    int failedTests = 0;

    std::cout << "Starting All Test Cases...\n"
              << std::endl;

    // Iterate through each test case in order
    for (const auto &testCase : testCases)
    {
        // Get tokens for the current test case
        std::vector<Token> tokens = getTestTokens(testCase.id);

        // Initialize the parser with tokens
        Parser parser(tokens);

        // Parse the tokens
        bool success = parser.parse();

        // Display the result
        std::cout << "Test Case " << testCase.id << ": " << testCase.description << " - ";
        if (success)
        {
            std::cout << "Parse Success" << std::endl;
            passedTests++;
        }
        else
        {
            std::cout << "Parse Failure" << std::endl;
            failedTests++;
        }
    }

    // Summary of test results
    std::cout << "\n"
              << BOLD << CYAN << "========================================" << RESET << std::endl;
    std::cout << BOLD << CYAN << "              TEST SUMMARY              " << RESET << std::endl;
    std::cout << BOLD << CYAN << "========================================" << RESET << std::endl;
    // Test results
    std::cout << BOLD << "Total Tests Run  : " << RESET << testCases.size() << std::endl;
    std::cout << BOLD << GREEN << "Passed           : " << RESET << passedTests << std::endl;
    std::cout << BOLD << RED << "Failed           : " << RESET << failedTests << std::endl;
    // Footer
    std::cout << BOLD << CYAN << "========================================" << RESET << std::endl;

    return 0;
}
