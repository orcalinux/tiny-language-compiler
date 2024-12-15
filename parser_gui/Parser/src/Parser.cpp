#include "Parser.h"

using namespace Tiny::Parser;
using namespace Tiny::Data;

Parser::Parser(QObject *parent) : QObject(parent), tokenIterator(QList<Token>())
{
    this->tokens = QList<Token>();
    this->tokenIterator = QListIterator<Token>(tokens);
}

Parser::~Parser()
{}

void Parser::setTokens(QList<Data::Token> tokens)
{
    this->tokens = tokens;
    this->tokenIterator = QListIterator<Data::Token>(tokens);
    this->currentLevel = 0;
}

Node *Parser::parse()
{
    if(tokens.isEmpty())
    {
        return nullptr;
    }

    return parseStmtSequence();
}

void Parser::match(Data::Token::TokenType expectedType)
{
    if(!tokenIterator.hasNext())
    {
        throw std::out_of_range("In match(): Unexpected end of file while expecting " + Token::getTokenTypeString(expectedType).toString().toStdString());
    }

    Data::Token currentToken = tokenIterator.next();
    if(currentToken.getType() != expectedType)
    {
        throw std::invalid_argument("In match(): Expected " +
                                    Token::getTokenTypeString(expectedType).toString().toStdString() +
                                    " but got " +
                                    Token::getTokenTypeString(currentToken.getType()).toString().toStdString() +
                                    " (value: " + currentToken.getValue().toStdString() + ")");
    }
}

void Parser::assignLevels(Node *node, int baseLevel)
{
    // Assign levels from top to bottom
    std::function<void(Node*,int)> recurse = [&](Node* n, int level) {
        n->setLevel(level);
        for (auto child : n->getChildren()) {
            recurse(child, level + 1);
        }
    };
    recurse(node, baseLevel + 1);
}

Node *Parser::parseStmtSequence()
{
    // parseStmtSequence rule
    if(!tokenIterator.hasNext())
    {
        throw std::out_of_range("In parseStmtSequence(): Unexpected end of file");
    }

    Node* stmt = parseStatement();
    stmt->setLevel(currentLevel);

    Node* root = stmt;

    while(tokenIterator.hasNext() && tokenIterator.peekNext().getType() == Token::TokenType::SEMICOLON)
    {
        match(Token::TokenType::SEMICOLON);
        Node* nextStmt = parseStatement();
        nextStmt->setLevel(currentLevel);
        stmt->addChild(nextStmt);

        stmt = nextStmt;
    }

    return root;
}

Node *Parser::parseStatement()
{
    // parseStatement rule
    if(!tokenIterator.hasNext())
    {
        throw std::out_of_range("In parseStatement(): Unexpected end of file");
    }

    switch(tokenIterator.peekNext().getType())
    {
    case Token::TokenType::IF:
        return parseIfStatement();
    case Token::TokenType::REPEAT:
        return parseRepeatStatement();
    case Token::TokenType::IDENTIFIER:
        return parseAssignStatement();
    case Token::TokenType::READ:
        return parseReadStatement();
    case Token::TokenType::WRITE:
        return parseWriteStatement();
    default:
        throw std::invalid_argument("In parseStatement(): Unexpected token: " +
                                    tokenIterator.peekNext().getValue().toStdString() +
                                    " of type " +
                                    Token::getTokenTypeString(tokenIterator.peekNext().getType()).toString().toStdString());
    }
}

Node *Parser::parseIfStatement()
{
    // parseIfStatement rule
    if(!tokenIterator.hasNext())
    {
        throw std::out_of_range("In parseIfStatement(): Unexpected end of file");
    }

    match(Token::TokenType::IF);
    Node* ifNode = new Node(Node::NodeType::If);
    ifNode->setLevel(currentLevel);

    currentLevel++;

    Node* expNode = parseExp();
    expNode->setLevel(currentLevel);
    ifNode->addChild(expNode);

    match(Token::TokenType::THEN);

    Node* stmtSeqNode = parseStmtSequence();
    stmtSeqNode->setLevel(currentLevel);
    ifNode->addChild(stmtSeqNode);

    if(tokenIterator.hasNext() && tokenIterator.peekNext().getType() == Token::TokenType::ELSE)
    {
        match(Token::TokenType::ELSE);

        Node* elseStmtSeqNode = parseStmtSequence();
        elseStmtSeqNode->setLevel(currentLevel);
        ifNode->addChild(elseStmtSeqNode);
    }

    match(Token::TokenType::END);

    currentLevel--;

    return ifNode;
}

Node *Parser::parseRepeatStatement()
{
    // parseRepeatStatement rule
    match(Token::TokenType::REPEAT);
    Node* repeatNode = new Node(Node::NodeType::Repeat);
    repeatNode->setLevel(currentLevel);

    currentLevel++;

    Node* stmtSeqNode = parseStmtSequence();
    stmtSeqNode->setLevel(currentLevel);
    repeatNode->addChild(stmtSeqNode);

    match(Token::TokenType::UNTIL);

    Node* expNode = parseExp();
    expNode->setLevel(currentLevel);
    repeatNode->addChild(expNode);

    currentLevel--;

    return repeatNode;
}

Node *Parser::parseAssignStatement()
{
    // parseAssignStatement rule
    if(!tokenIterator.hasNext())
    {
        throw std::out_of_range("In parseAssignStatement(): Unexpected end of file");
    }

    QString idValue = tokenIterator.peekNext().getValue();
    match(Token::TokenType::IDENTIFIER);

    match(Token::TokenType::ASSIGN);

    Node* assignNode = new Node(Node::NodeType::Assign);
    assignNode->setLevel(currentLevel);
    assignNode->setValue(idValue);

    Node* expNode = parseExp();
    expNode->setLevel(currentLevel + 1);
    assignNode->addChild(expNode);

    return assignNode;
}

Node *Parser::parseReadStatement()
{
    // parseReadStatement rule
    match(Token::TokenType::READ);
    Node* readNode = new Node(Node::NodeType::Read);
    readNode->setLevel(currentLevel);

    if(!tokenIterator.hasNext())
    {
        throw std::out_of_range("In parseReadStatement(): Unexpected end of file expecting IDENTIFIER");
    }

    QString idValue = tokenIterator.peekNext().getValue();
    match(Token::TokenType::IDENTIFIER);

    readNode->setValue(idValue);

    return readNode;
}


Node *Parser::parseWriteStatement()
{
    // parseWriteStatement rule
    match(Token::TokenType::WRITE);
    Node* writeNode = new Node(Node::NodeType::Write);
    writeNode->setLevel(currentLevel);

    Node* expNode = parseExp();
    expNode->setLevel(currentLevel + 1);
    writeNode->addChild(expNode);

    return writeNode;
}

Node *Parser::parseExp()
{
    // parseExp rule
    Node* simpleExpNode = parseSimpleExp();

    if(tokenIterator.hasNext() &&
        (tokenIterator.peekNext().getType() == Token::TokenType::LESSTHAN ||
         tokenIterator.peekNext().getType() == Token::TokenType::EQUAL))
    {
        Node* opNode = parseComparisonOp();
        opNode->setLevel(currentLevel);

        simpleExpNode->setLevel(currentLevel + 1);
        opNode->addChild(simpleExpNode);

        Node* nextSimpleExpNode = parseSimpleExp();
        nextSimpleExpNode->setLevel(currentLevel + 1);
        opNode->addChild(nextSimpleExpNode);

        return opNode;
    }

    return simpleExpNode;
}

Node *Parser::parseSimpleExp()
{
    // parseSimpleExp rule
    Node* firstTerm = parseTerm();

    std::vector<Node*> terms;
    std::vector<Node*> ops;

    terms.push_back(firstTerm);

    while (tokenIterator.hasNext() &&
           (tokenIterator.peekNext().getType() == Token::TokenType::PLUS ||
            tokenIterator.peekNext().getType() == Token::TokenType::MINUS))
    {
        Node* opNode = parseAddop();
        Node* nextTerm = parseTerm();

        ops.push_back(opNode);
        terms.push_back(nextTerm);
    }

    // Left-associative build:
    Node* root = terms[0];
    for (int i = 0; i < (int)ops.size(); i++) {
        Node* op = ops[i];
        Node* rightTerm = terms[i + 1];

        op->addChild(root);
        op->addChild(rightTerm);
        root = op;
    }

    assignLevels(root, currentLevel);
    return root;
}


Node *Parser::parseComparisonOp()
{
    // parseComparisonOp rule
    if(!tokenIterator.hasNext())
    {
        throw std::out_of_range("In parseComparisonOp(): Unexpected end of file");
    }

    Token::TokenType t = tokenIterator.peekNext().getType();
    if(t != Token::TokenType::LESSTHAN && t != Token::TokenType::EQUAL)
    {
        throw std::invalid_argument("In parseComparisonOp(): Unexpected token: " +
                                    tokenIterator.peekNext().getValue().toStdString() +
                                    " of type " +
                                    Token::getTokenTypeString(t).toString().toStdString());
    }

    Node* opNode = new Node(Node::NodeType::Op);
    opNode->setLevel(currentLevel);
    opNode->setValue(tokenIterator.peekNext().getValue());

    if(t == Token::TokenType::LESSTHAN)
    {
        match(Token::TokenType::LESSTHAN);
    }
    else
    {
        match(Token::TokenType::EQUAL);
    }

    return opNode;
}

Node *Parser::parseAddop()
{
    // parseAddop rule
    if(!tokenIterator.hasNext())
    {
        throw std::out_of_range("In parseAddop(): Unexpected end of file");
    }

    Token::TokenType t = tokenIterator.peekNext().getType();
    if(t != Token::TokenType::PLUS && t != Token::TokenType::MINUS)
    {
        throw std::invalid_argument("In parseAddop(): Unexpected token: " +
                                    tokenIterator.peekNext().getValue().toStdString() +
                                    " of type " +
                                    Token::getTokenTypeString(t).toString().toStdString());
    }

    Node* opNode = new Node(Node::NodeType::Op);
    opNode->setLevel(currentLevel);
    opNode->setValue(tokenIterator.peekNext().getValue());

    if(t == Token::TokenType::PLUS)
    {
        match(Token::TokenType::PLUS);
    }
    else
    {
        match(Token::TokenType::MINUS);
    }

    return opNode;
}

Node *Parser::parseTerm()
{
    // parseTerm rule
    Node* firstFactor = parseFactor();

    std::vector<Node*> factors;
    std::vector<Node*> ops;

    factors.push_back(firstFactor);

    while (tokenIterator.hasNext() &&
           (tokenIterator.peekNext().getType() == Token::TokenType::MULT ||
            tokenIterator.peekNext().getType() == Token::TokenType::DIV))
    {
        Node* opNode = parseMulop();
        Node* nextFactor = parseFactor();

        ops.push_back(opNode);
        factors.push_back(nextFactor);
    }

    // Left-associative build:
    Node* root = factors[0];
    for (int i = 0; i < (int)ops.size(); i++) {
        Node* op = ops[i];
        Node* rightFactor = factors[i + 1];

        op->addChild(root);
        op->addChild(rightFactor);
        root = op;
    }

    assignLevels(root, currentLevel);
    return root;
}

Node *Parser::parseMulop()
{
    // parseMulop rule
    if(!tokenIterator.hasNext())
    {
        throw std::out_of_range("In parseMulop(): Unexpected end of file");
    }

    Token::TokenType t = tokenIterator.peekNext().getType();
    if(t != Token::TokenType::MULT && t != Token::TokenType::DIV)
    {
        throw std::invalid_argument("In parseMulop(): Unexpected token: " +
                                    tokenIterator.peekNext().getValue().toStdString() +
                                    " of type " +
                                    Token::getTokenTypeString(t).toString().toStdString());
    }

    Node* opNode = new Node(Node::NodeType::Op);
    opNode->setLevel(currentLevel);
    opNode->setValue(tokenIterator.peekNext().getValue());

    if(t == Token::TokenType::MULT)
    {
        match(Token::TokenType::MULT);
    }
    else
    {
        match(Token::TokenType::DIV);
    }

    return opNode;
}

Node *Parser::parseFactor()
{
    // parseFactor rule
    if(!tokenIterator.hasNext())
    {
        throw std::out_of_range("In parseFactor(): Unexpected end of file");
    }

    Node* factorNode = nullptr;
    Token::TokenType t = tokenIterator.peekNext().getType();

    switch(t)
    {
    case Token::TokenType::OPENBRACKET:
        match(Token::TokenType::OPENBRACKET);
        factorNode = parseExp();
        factorNode->setLevel(currentLevel);
        if(!tokenIterator.hasNext())
        {
            throw std::out_of_range("In parseFactor(): Unexpected end of file, expecting CLOSEDBRACKET");
        }
        match(Token::TokenType::CLOSEDBRACKET);
        break;
    case Token::TokenType::NUMBER:
        factorNode = new Node(Node::NodeType::Const);
        factorNode->setLevel(currentLevel);
        factorNode->setValue(tokenIterator.peekNext().getValue());
        match(Token::TokenType::NUMBER);
        break;
    case Token::TokenType::IDENTIFIER:
        factorNode = new Node(Node::NodeType::Id);
        factorNode->setLevel(currentLevel);
        factorNode->setValue(tokenIterator.peekNext().getValue());
        match(Token::TokenType::IDENTIFIER);
        break;
    default:
        throw std::invalid_argument("In parseFactor(): Unexpected token: " +
                                    tokenIterator.peekNext().getValue().toStdString() +
                                    " of type " +
                                    Token::getTokenTypeString(t).toString().toStdString());
    }

    return factorNode;
}
