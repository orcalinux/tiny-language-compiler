#include <gtest/gtest.h>
#include "token.hpp"

namespace TINY
{
    namespace SCANNER
    {

        // Test token creation
        TEST(TokenTest, TokenCreation)
        {
            Token token(TokenType::IF, "if", 1, 1);

            EXPECT_EQ(token.getType(), TokenType::IF);
            EXPECT_EQ(token.getValue(), "if");
            EXPECT_EQ(token.getLine(), 1);
            EXPECT_EQ(token.getColumn(), 1);
        }

        // Test token string representation
        TEST(TokenTest, TokenToString)
        {
            Token token(TokenType::IF, "if", 1, 1);

            EXPECT_EQ(token.toString(false), "if, IF");
            EXPECT_EQ(token.toString(true), "if, IF [Line: 1, Column: 1]");
        }

    } // namespace SCANNER
} // namespace TINY
