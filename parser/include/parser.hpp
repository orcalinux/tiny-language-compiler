#ifndef PARSER_HPP
#define PARSER_HPP

#include "token.hpp"
#include "parsing_table.hpp"
#include "stack.hpp"
#include <vector>
#include <string>

class Parser
{
public:
    Parser(const std::vector<Token> &tokens);
    bool parse(); // Returns true if parsing is successful

private:
    std::vector<Token> tokens;
    size_t currentTokenIndex;
    Token currentToken;
    ParsingTable parsingTable;
    Stack stack;

    void advance();
    TokenType getTokenType(const Token &token) const;
    std::string tokenTypeToString(TokenType type) const;
};

#endif // PARSER_HPP
