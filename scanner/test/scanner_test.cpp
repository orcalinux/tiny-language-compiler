#include <gtest/gtest.h>
#include "scanner.hpp"
#include "token.hpp"

namespace TINY
{
    namespace SCANNER
    {

        // Test valid tokens
        TEST(ScannerTest, ValidTokens)
        {
            std::string input = "if then end repeat until read write := < = + - * / ( ) ;";
            Scanner scanner(input);

            EXPECT_TRUE(scanner.hasMoreTokens());
            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::IF);
            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::THEN);
            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::END);
            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::REPEAT);
            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::UNTIL);
            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::READ);
            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::WRITE);
            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::ASSIGN);
            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::LESSTHAN);
            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::EQUAL);
            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::PLUS);
            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::MINUS);
            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::MULT);
            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::DIV);
            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::OPENBRACKET);
            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::CLOSEDBRACKET);
            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::SEMICOLON);
            EXPECT_FALSE(scanner.hasMoreTokens());
        }

        // Test identifiers
        TEST(ScannerTest, Identifiers)
        {
            std::string input = "varName another_var lastVar";
            Scanner scanner(input);

            // First identifier: "varName"
            Token token1 = scanner.getNextToken(); // Store the token
            EXPECT_EQ(token1.getType(), TokenType::IDENTIFIER);
            EXPECT_EQ(token1.getValue(), "varName");

            // Identifier: "another"
            Token token2 = scanner.getNextToken(); // Store the next token
            EXPECT_EQ(token2.getType(), TokenType::IDENTIFIER);
            EXPECT_EQ(token2.getValue(), "another");

            // Underscore as UNKNOWN token
            Token token3 = scanner.getNextToken(); // Store the next token
            EXPECT_EQ(token3.getType(), TokenType::UNKNOWN);
            EXPECT_EQ(token3.getValue(), "_");

            // Identifier: "var"
            Token token4 = scanner.getNextToken(); // Store the next token
            EXPECT_EQ(token4.getType(), TokenType::IDENTIFIER);
            EXPECT_EQ(token4.getValue(), "var");

            // Final identifier: "lastVar"
            Token token5 = scanner.getNextToken(); // Store the next token
            EXPECT_EQ(token5.getType(), TokenType::IDENTIFIER);
            EXPECT_EQ(token5.getValue(), "lastVar");
        }

        // Test numeric literals
        TEST(ScannerTest, NumericLiterals)
        {
            std::string input = "123 45678 999";
            Scanner scanner(input);

            // First number: "123"
            Token token1 = scanner.getNextToken(); // Store the token
            EXPECT_EQ(token1.getType(), TokenType::NUMBER);
            EXPECT_EQ(token1.getValue(), "123");

            // Second number: "45678"
            Token token2 = scanner.getNextToken(); // Store the next token
            EXPECT_EQ(token2.getType(), TokenType::NUMBER);
            EXPECT_EQ(token2.getValue(), "45678");

            // Third number: "999"
            Token token3 = scanner.getNextToken(); // Store the next token
            EXPECT_EQ(token3.getType(), TokenType::NUMBER);
            EXPECT_EQ(token3.getValue(), "999");
        }

        // Test mixed tokens
        TEST(ScannerTest, MixedTokens)
        {
            std::string input = "if x := 42 + y;";
            Scanner scanner(input);

            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::IF);
            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::IDENTIFIER);
            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::ASSIGN);
            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::NUMBER);
            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::PLUS);
            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::IDENTIFIER);
            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::SEMICOLON);
        }

        // Test unknown tokens
        TEST(ScannerTest, UnknownTokens)
        {
            std::string input = "@_ $ #";
            Scanner scanner(input);

            // First unknown token: "@"
            Token token1 = scanner.getNextToken(); // Store the token
            EXPECT_EQ(token1.getType(), TokenType::UNKNOWN);
            EXPECT_EQ(token1.getValue(), "@");

            // Second unknown token: "_"
            Token token2 = scanner.getNextToken(); // Store the next token
            EXPECT_EQ(token2.getType(), TokenType::UNKNOWN);
            EXPECT_EQ(token2.getValue(), "_");

            // Second unknown token: "$"
            Token token3 = scanner.getNextToken(); // Store the next token
            EXPECT_EQ(token3.getType(), TokenType::UNKNOWN);
            EXPECT_EQ(token3.getValue(), "$");

            // Third unknown token: "#"
            Token token4 = scanner.getNextToken(); // Store the next token
            EXPECT_EQ(token4.getType(), TokenType::UNKNOWN);
            EXPECT_EQ(token4.getValue(), "#");
        }

    } // namespace SCANNER
} // namespace TINY
