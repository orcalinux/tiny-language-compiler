#include "parser.hpp"
#include "token.hpp"
#include <iostream>
#include <vector>
#include <string>

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

int main()
{
    int testCase = 2; // Change this value to run different test cases
    std::vector<Token> tokens = getTestTokens(testCase);

    Parser parser(tokens);
    bool success = parser.parse();

    if (success)
    {
        std::cout << "Parse Success" << std::endl;
    }
    else
    {
        std::cout << "Parse Failure" << std::endl;
    }

    return 0;
}
