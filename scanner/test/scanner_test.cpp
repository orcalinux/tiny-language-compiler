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
            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::IDENTIFIER);
            EXPECT_EQ(scanner.getNextToken().getValue(), "varName");

            // Identifier: "another"
            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::IDENTIFIER);
            EXPECT_EQ(scanner.getNextToken().getValue(), "another");

            // Underscore as UNKNOWN token
            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::UNKNOWN);
            EXPECT_EQ(scanner.getNextToken().getValue(), "_");

            // Identifier: "var"
            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::IDENTIFIER);
            EXPECT_EQ(scanner.getNextToken().getValue(), "var");

            // Final identifier: "lastVar"
            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::IDENTIFIER);
            EXPECT_EQ(scanner.getNextToken().getValue(), "lastVar");
        }

        // Test numeric literals
        TEST(ScannerTest, NumericLiterals)
        {
            std::string input = "123 45678 999";
            Scanner scanner(input);

            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::NUMBER);
            EXPECT_EQ(scanner.getNextToken().getValue(), "123");

            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::NUMBER);
            EXPECT_EQ(scanner.getNextToken().getValue(), "45678");

            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::NUMBER);
            EXPECT_EQ(scanner.getNextToken().getValue(), "999");
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
            std::string input = "@ $ #";
            Scanner scanner(input);

            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::UNKNOWN);
            EXPECT_EQ(scanner.getNextToken().getValue(), "@");

            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::UNKNOWN);
            EXPECT_EQ(scanner.getNextToken().getValue(), "$");

            EXPECT_EQ(scanner.getNextToken().getType(), TokenType::UNKNOWN);
            EXPECT_EQ(scanner.getNextToken().getValue(), "#");
        }

    } // namespace SCANNER
} // namespace TINY
