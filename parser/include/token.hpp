#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType
{
    IF,
    THEN,
    ELSE,
    END,
    REPEAT,
    UNTIL,
    READ,
    WRITE,
    IDENTIFIER,
    NUMBER,
    ASSIGN,    // :=
    SEMICOLON, // ;
    PLUS,      // +
    MINUS,     // -
    TIMES,     // *
    DIVIDE,    // /
    LT,        // <
    EQ,        // =
    LPAREN,    // (
    RPAREN,    // )
    END_OF_INPUT,
    INVALID
};

struct Token
{
    TokenType type;
    std::string value; // For IDENTIFIER and NUMBER types

    Token(TokenType t = TokenType::INVALID, const std::string &val = "")
        : type(t), value(val) {}
};

#endif // TOKEN_H
