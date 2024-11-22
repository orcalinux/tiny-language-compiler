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

            // Third unknown token: "$"
            Token token3 = scanner.getNextToken(); // Store the next token
            EXPECT_EQ(token3.getType(), TokenType::UNKNOWN);
            EXPECT_EQ(token3.getValue(), "$");

            // Fourth unknown token: "#"
            Token token4 = scanner.getNextToken(); // Store the next token
            EXPECT_EQ(token4.getType(), TokenType::UNKNOWN);
            EXPECT_EQ(token4.getValue(), "#");
        }

        // New test case: Comments
        TEST(ScannerTest, Comments)
        {
            // Input with comments
            std::string input = "read x; { This is a comment } write y;";

            Scanner scanner(input);

            // Token: read
            Token token1 = scanner.getNextToken();
            EXPECT_EQ(token1.getType(), TokenType::READ);
            EXPECT_EQ(token1.getValue(), "read");

            // Token: x
            Token token2 = scanner.getNextToken();
            EXPECT_EQ(token2.getType(), TokenType::IDENTIFIER);
            EXPECT_EQ(token2.getValue(), "x");

            // Token: ;
            Token token3 = scanner.getNextToken();
            EXPECT_EQ(token3.getType(), TokenType::SEMICOLON);
            EXPECT_EQ(token3.getValue(), ";");

            // Comment is skipped, no token generated for it

            // Token: write
            Token token4 = scanner.getNextToken();
            EXPECT_EQ(token4.getType(), TokenType::WRITE);
            EXPECT_EQ(token4.getValue(), "write");

            // Token: y
            Token token5 = scanner.getNextToken();
            EXPECT_EQ(token5.getType(), TokenType::IDENTIFIER);
            EXPECT_EQ(token5.getValue(), "y");

            // Token: ;
            Token token6 = scanner.getNextToken();
            EXPECT_EQ(token6.getType(), TokenType::SEMICOLON);
            EXPECT_EQ(token6.getValue(), ";");

            EXPECT_FALSE(scanner.hasMoreTokens());
        }

        // New test case: Comments with newlines
        TEST(ScannerTest, CommentsWithNewlines)
        {
            // Input with comments containing newlines
            std::string input = "read x; { This is a \n multi-line \n comment } \n write y;";

            Scanner scanner(input);

            // Token: read
            Token token1 = scanner.getNextToken();
            EXPECT_EQ(token1.getType(), TokenType::READ);
            EXPECT_EQ(token1.getValue(), "read");
            EXPECT_EQ(token1.getLine(), 1);

            // Token: x
            Token token2 = scanner.getNextToken();
            EXPECT_EQ(token2.getType(), TokenType::IDENTIFIER);
            EXPECT_EQ(token2.getValue(), "x");
            EXPECT_EQ(token2.getLine(), 1);

            // Token: ;
            Token token3 = scanner.getNextToken();
            EXPECT_EQ(token3.getType(), TokenType::SEMICOLON);
            EXPECT_EQ(token3.getValue(), ";");
            EXPECT_EQ(token3.getLine(), 1);

            // Comment is skipped, including newlines

            // Token: write
            Token token4 = scanner.getNextToken();
            EXPECT_EQ(token4.getType(), TokenType::WRITE);
            EXPECT_EQ(token4.getValue(), "write");
            EXPECT_EQ(token4.getLine(), 4); // Lines have advanced due to newlines in comment

            // Token: y
            Token token5 = scanner.getNextToken();
            EXPECT_EQ(token5.getType(), TokenType::IDENTIFIER);
            EXPECT_EQ(token5.getValue(), "y");
            EXPECT_EQ(token5.getLine(), 4);

            // Token: ;
            Token token6 = scanner.getNextToken();
            EXPECT_EQ(token6.getType(), TokenType::SEMICOLON);
            EXPECT_EQ(token6.getValue(), ";");
            EXPECT_EQ(token6.getLine(), 4);

            EXPECT_FALSE(scanner.hasMoreTokens());
        }

        // New test case: Unclosed comment
        TEST(ScannerTest, UnclosedComment)
        {
            // Input with an unclosed comment
            std::string input = "read x; { This is an unclosed comment ";

            Scanner scanner(input);

            // Token: read
            Token token1 = scanner.getNextToken();
            EXPECT_EQ(token1.getType(), TokenType::READ);
            EXPECT_EQ(token1.getValue(), "read");

            // Token: x
            Token token2 = scanner.getNextToken();
            EXPECT_EQ(token2.getType(), TokenType::IDENTIFIER);
            EXPECT_EQ(token2.getValue(), "x");

            // Token: ;
            Token token3 = scanner.getNextToken();
            EXPECT_EQ(token3.getType(), TokenType::SEMICOLON);
            EXPECT_EQ(token3.getValue(), ";");

            // Attempt to get next token, should return UNKNOWN due to unclosed comment
            Token token4 = scanner.getNextToken();
            EXPECT_EQ(token4.getType(), TokenType::UNKNOWN);
            EXPECT_EQ(token4.getValue(), "Unclosed comment");

            EXPECT_FALSE(scanner.hasMoreTokens());
        }

        // New test case: Multiple comments
        TEST(ScannerTest, MultipleComments)
        {
            // Input with multiple comments
            std::string input = "{First comment} read x; {Second comment} write y; {Third comment}";

            Scanner scanner(input);

            // Token: read
            Token token1 = scanner.getNextToken();
            EXPECT_EQ(token1.getType(), TokenType::READ);
            EXPECT_EQ(token1.getValue(), "read");

            // Token: x
            Token token2 = scanner.getNextToken();
            EXPECT_EQ(token2.getType(), TokenType::IDENTIFIER);
            EXPECT_EQ(token2.getValue(), "x");

            // Token: ;
            Token token3 = scanner.getNextToken();
            EXPECT_EQ(token3.getType(), TokenType::SEMICOLON);
            EXPECT_EQ(token3.getValue(), ";");

            // Token: write
            Token token4 = scanner.getNextToken();
            EXPECT_EQ(token4.getType(), TokenType::WRITE);
            EXPECT_EQ(token4.getValue(), "write");

            // Token: y
            Token token5 = scanner.getNextToken();
            EXPECT_EQ(token5.getType(), TokenType::IDENTIFIER);
            EXPECT_EQ(token5.getValue(), "y");

            // Token: ;
            Token token6 = scanner.getNextToken();
            EXPECT_EQ(token6.getType(), TokenType::SEMICOLON);
            EXPECT_EQ(token6.getValue(), ";");

            EXPECT_FALSE(scanner.hasMoreTokens());
        }

        // New test case: Nested comments
        TEST(ScannerTest, NestedComments)
        {
            // Input with nested comments
            std::string input = "read x; { This is a { nested { comment } } } write y;";

            Scanner scanner(input);

            // Token: read
            Token token1 = scanner.getNextToken();
            EXPECT_EQ(token1.getType(), TokenType::READ);
            EXPECT_EQ(token1.getValue(), "read");

            // Token: x
            Token token2 = scanner.getNextToken();
            EXPECT_EQ(token2.getType(), TokenType::IDENTIFIER);
            EXPECT_EQ(token2.getValue(), "x");

            // Token: ;
            Token token3 = scanner.getNextToken();
            EXPECT_EQ(token3.getType(), TokenType::SEMICOLON);
            EXPECT_EQ(token3.getValue(), ";");

            // Nested comments are skipped, no tokens generated for them

            // Token: write
            Token token4 = scanner.getNextToken();
            EXPECT_EQ(token4.getType(), TokenType::WRITE);
            EXPECT_EQ(token4.getValue(), "write");

            // Token: y
            Token token5 = scanner.getNextToken();
            EXPECT_EQ(token5.getType(), TokenType::IDENTIFIER);
            EXPECT_EQ(token5.getValue(), "y");

            // Token: ;
            Token token6 = scanner.getNextToken();
            EXPECT_EQ(token6.getType(), TokenType::SEMICOLON);
            EXPECT_EQ(token6.getValue(), ";");

            EXPECT_FALSE(scanner.hasMoreTokens());
        }

        // New test case: Unclosed nested comment
        TEST(ScannerTest, UnclosedNestedComment)
        {
            // Input with an unclosed nested comment
            std::string input = "read x; { Outer comment { Inner comment } write y;";

            Scanner scanner(input);

            // Token: read
            Token token1 = scanner.getNextToken();
            EXPECT_EQ(token1.getType(), TokenType::READ);
            EXPECT_EQ(token1.getValue(), "read");

            // Token: x
            Token token2 = scanner.getNextToken();
            EXPECT_EQ(token2.getType(), TokenType::IDENTIFIER);
            EXPECT_EQ(token2.getValue(), "x");

            // Token: ;
            Token token3 = scanner.getNextToken();
            EXPECT_EQ(token3.getType(), TokenType::SEMICOLON);
            EXPECT_EQ(token3.getValue(), ";");

            // Attempt to get next token, should return UNKNOWN due to unclosed comment
            Token token4 = scanner.getNextToken();
            EXPECT_EQ(token4.getType(), TokenType::UNKNOWN);
            EXPECT_EQ(token4.getValue(), "Unclosed comment");

            EXPECT_FALSE(scanner.hasMoreTokens());
        }
    } // namespace SCANNER
} // namespace TINY
