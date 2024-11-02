// Token class implementation
#include "token.hpp"

std::string Token::toString() const
{
    switch (type)
    {
    case TokenType::IF:
        return "IF";
    case TokenType::THEN:
        return "THEN";
    case TokenType::ELSE:
        return "ELSE";
    case TokenType::END:
        return "END";
    case TokenType::REPEAT:
        return "REPEAT";
    case TokenType::UNTIL:
        return "UNTIL";
    case TokenType::READ:
        return "READ";
    case TokenType::WRITE:
        return "WRITE";
    case TokenType::ASSIGN:
        return "ASSIGN";
    case TokenType::LESSTHAN:
        return "LESSTHAN";
    case TokenType::EQUAL:
        return "EQUAL";
    case TokenType::PLUS:
        return "PLUS";
    case TokenType::MINUS:
        return "MINUS";
    case TokenType::MULT:
        return "MULT";
    case TokenType::DIV:
        return "DIV";
    case TokenType::OPENBRACKET:
        return "OPENBRACKET";
    case TokenType::CLOSEDBRACKET:
        return "CLOSEDBRACKET";
    case TokenType::SEMICOLON:
        return "SEMICOLON";
    case TokenType::IDENTIFIER:
        return "IDENTIFIER";
    case TokenType::NUMBER:
        return "NUMBER";
    default:
        return "UNKNOWN";
    }
}
