// Parser.cpp
#include "Parser.h"

using namespace Tiny::Parser;
using namespace Tiny::Data;

Parser::Parser(QObject *parent) : QObject(parent)
{

}

Parser::~Parser()
{}

void Parser::setTokens(QList<Token> tokens)
{
    this->tokens = tokens;
    currentTokenIndex = 0;
    currentLevel = 0;
}

Node *Parser::parse()
{
    return parseStmtSequence();
}

void Parser::advance()
{
    currentTokenIndex++;
}

void Parser::expectAndSkip(Token::TokenType type)
{
    if(tokens[currentTokenIndex].getType() != type)
    {
        emit error("Expected " + Token::getTokenTypeString(type).toString() + " but got " +
                   Token::getTokenTypeString(tokens[currentTokenIndex].getType()).toString() +
                   ". At line: " + QString::number(tokens[currentTokenIndex].getLine()) +
                   " column: " + QString::number(tokens[currentTokenIndex].getColumn()));
    }
    advance();
}

Node *Parser::consume(Token::TokenType tokenType, Node::NodeType nodeType)
{
    Token currentToken = tokens[currentTokenIndex];
    if(currentToken.getType() != tokenType){
        emit error("Expected " + Token::getTokenTypeString(tokenType).toString() + " but got " +
                   Token::getTokenTypeString(currentToken.getType()).toString() +
                   ". At line: " + QString::number(currentToken.getLine()) +
                   " column: " + QString::number(currentToken.getColumn()));
        return nullptr;
    }

    Node* node = new Node(nodeType, currentToken.getValue());
    advance();
    return node;
}

Node *Parser::parseStmtSequence()
{
    Node* firstStmt = parseStatement();
    Node* currentStmt = firstStmt;
    // set level
    currentStmt->setLevel(currentLevel);

    while(tokens[currentTokenIndex].getType() == Token::TokenType::SEMICOLON)
    {
        advance(); // consume the semicolon
        Node* nextStmt = parseStatement();
        if(nextStmt != nullptr)
        {
            currentStmt->addChild(nextStmt);
            nextStmt->setLevel(currentLevel);
            currentStmt = nextStmt;
        }
    }

    return firstStmt;
}

Node *Parser::parseStatement()
{

}

Node *Parser::parseIfStatement()
{

}

Node *Parser::parseRepeatStatement()
{

}

Node *Parser::parseAssignStatement()
{

}

Node *Parser::parseReadStatement()
{

}

Node *Parser::parseWriteStatement()
{

}

Node *Parser::parseExp()
{

}

Node *Parser::parseSimpleExp()
{

}

Node *Parser::parseComparisonOp()
{

}

Node *Parser::parseAddop()
{

}

Node *Parser::parseTerm()
{

}

Node *Parser::parseMulop()
{

}

Node *Parser::parseFactor()
{

}

