// Token class definition
#ifndef TOKEN_HPP
#define TOKEN_HPP

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
    ASSIGN,
    LESSTHAN,
    EQUAL,
    PLUS,
    MINUS,
    MULT,
    DIV,
    OPENBRACKET,
    CLOSEDBRACKET,
    SEMICOLON,
    IDENTIFIER,
    NUMBER,
    UNKNOWN
};

class Token
{
public:
    Token(TokenType type, const std::string &value)
        : type(type), value(value) {}

    TokenType getType() const { return type; }
    std::string getValue() const { return value; }
    std::string toString() const;

private:
    TokenType type;
    std::string value;
};

#endif // TOKEN_HPP
