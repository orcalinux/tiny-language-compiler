// src/Parser.cpp
#include "parser.hpp"
#include <iostream>
#include <unordered_map>

// Helper function to convert TokenType to string
std::string Parser::tokenTypeToString(TokenType type) const
{
    switch (type)
    {
    case TokenType::IF:
        return "if";
    case TokenType::THEN:
        return "then";
    case TokenType::ELSE:
        return "else";
    case TokenType::END:
        return "end";
    case TokenType::REPEAT:
        return "repeat";
    case TokenType::UNTIL:
        return "until";
    case TokenType::READ:
        return "read";
    case TokenType::WRITE:
        return "write";
    case TokenType::IDENTIFIER:
        return "identifier";
    case TokenType::NUMBER:
        return "number";
    case TokenType::ASSIGN:
        return ":=";
    case TokenType::SEMICOLON:
        return ";";
    case TokenType::PLUS:
        return "+";
    case TokenType::MINUS:
        return "-";
    case TokenType::TIMES:
        return "*";
    case TokenType::DIVIDE:
        return "/";
    case TokenType::LT:
        return "<";
    case TokenType::EQ:
        return "=";
    case TokenType::LPAREN:
        return "(";
    case TokenType::RPAREN:
        return ")";
    case TokenType::END_OF_INPUT:
        return "$";
    default:
        return "invalid";
    }
}

Parser::Parser(const std::vector<Token> &tokensList)
    : tokens(tokensList), currentTokenIndex(0), parsingTable(), stack()
{
    if (!tokens.empty())
    {
        currentToken = tokens[currentTokenIndex];
    }
}

void Parser::advance()
{
    if (currentTokenIndex < tokens.size() - 1)
    {
        currentTokenIndex++;
        currentToken = tokens[currentTokenIndex];
    }
}

TokenType Parser::getTokenType(const Token &token) const
{
    return token.type;
}

bool Parser::parse()
{
    // Initialize the stack with the start symbol and end marker
    stack.pushSymbol("$");       // End marker
    stack.pushSymbol("program"); // Start symbol

    while (!stack.isEmpty())
    {
        std::string top = stack.topSymbol();
        stack.popSymbol();

        // Debug: Print current top and current token
        // Uncomment the next line for debugging
        // std::cout << "Top of Stack: " << top << ", Current Token: " << tokenTypeToString(currentToken.type) << std::endl;

        if (top == "$")
        {
            if (currentToken.type == TokenType::END_OF_INPUT)
            {
                return true; // Successful parsing
            }
            else
            {
                std::cerr << "Parse Error: Unexpected tokens after end of input." << std::endl;
                return false;
            }
        }

        // Check if 'top' is a terminal
        // Define a map of terminals for quick lookup
        static const std::unordered_map<std::string, TokenType> terminals = {
            {"if", TokenType::IF},
            {"then", TokenType::THEN},
            {"else", TokenType::ELSE},
            {"end", TokenType::END},
            {"repeat", TokenType::REPEAT},
            {"until", TokenType::UNTIL},
            {"read", TokenType::READ},
            {"write", TokenType::WRITE},
            {";", TokenType::SEMICOLON},
            {":=", TokenType::ASSIGN},
            {"+", TokenType::PLUS},
            {"-", TokenType::MINUS},
            {"*", TokenType::TIMES},
            {"/", TokenType::DIVIDE},
            {"<", TokenType::LT},
            {"=", TokenType::EQ},
            {"(", TokenType::LPAREN},
            {")", TokenType::RPAREN},
            {"identifier", TokenType::IDENTIFIER},
            {"number", TokenType::NUMBER},
            {"$", TokenType::END_OF_INPUT}};

        // Check if 'top' is a terminal
        auto terminalIt = terminals.find(top);
        if (terminalIt != terminals.end())
        {
            TokenType expectedType = terminalIt->second;
            if (expectedType == currentToken.type)
            {
                advance(); // Match successful, consume token
            }
            else
            {
                std::cerr << "Parse Error: Expected '" << tokenTypeToString(expectedType)
                          << "' but found '" << tokenTypeToString(currentToken.type) << "'" << std::endl;
                return false;
            }
        }
        else
        {
            // 'top' is a non-terminal, consult the parsing table
            Production production = parsingTable.getProduction(top, currentToken.type);
            if (production.empty())
            {
                // ε-production or error
                // If 'top' can derive ε, continue
                // Else, it's an error
                // Here, assume empty production is ε
                continue;
            }

            // Push the production's right-hand side symbols onto the stack in reverse order
            for (auto it = production.rbegin(); it != production.rend(); ++it)
            {
                if (*it != "ε")
                { // Skip ε
                    stack.pushSymbol(*it);
                }
            }
        }
    }

    // After processing, check if input tokens are exhausted
    if (currentToken.type == TokenType::END_OF_INPUT)
    {
        return true;
    }

    std::cerr << "Parse Error: Input not fully consumed." << std::endl;
    return false;
}
