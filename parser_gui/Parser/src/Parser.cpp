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
        throw std::out_of_range("Unexpected end of file");
    }

    Data::Token currentToken = tokenIterator.next();
    if(currentToken.getType() != expectedType)
    {
        throw std::invalid_argument("Unexpected token: " + currentToken.getValue().toStdString());
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
    Node* stmt = nullptr;
    if(!tokenIterator.hasNext())
    {
        throw std::out_of_range("Unexpected end of file");
    }

    switch(tokenIterator.peekNext().getType())
    {
        case Token::TokenType::IF:
            stmt = parseIfStatement();
            break;
        case Token::TokenType::REPEAT:
            stmt = parseRepeatStatement();
            break;
        case Token::TokenType::IDENTIFIER:
            stmt = parseAssignStatement();
            break;
        case Token::TokenType::READ:
            stmt = parseReadStatement();
            break;
        case Token::TokenType::WRITE:
            stmt = parseWriteStatement();
            break;
        default:
            throw std::invalid_argument("Unexpected token: " + tokenIterator.peekNext().getValue().toStdString());
    }

    return stmt;
}

Node *Parser::parseIfStatement()
{
    if(!tokenIterator.hasNext())
    {
        throw std::out_of_range("Unexpected end of file");
    }

    match(Token::TokenType::IF);
    Node* ifNode = new Node(Node::NodeType::If);
    ifNode->setLevel(currentLevel);

    currentLevel++;

    // Parse the expression
    Node* expNode = parseExp();
    expNode->setLevel(currentLevel);
    ifNode->addChild(expNode);

    match(Token::TokenType::THEN);

    // Parse the statement sequence
    Node* stmtSeqNode = parseStmtSequence();
    stmtSeqNode->setLevel(currentLevel);
    ifNode->addChild(stmtSeqNode);

    // Check for an optional ELSE clause
    if(tokenIterator.hasNext() && tokenIterator.peekNext().getType() == Token::TokenType::ELSE)
    {
        match(Token::TokenType::ELSE);

        // Parse the else statement sequence
        Node* elseStmtSeqNode = parseStmtSequence();
        elseStmtSeqNode->setLevel(currentLevel);
        ifNode->addChild(elseStmtSeqNode);
    }

    // End the IF statement
    match(Token::TokenType::END);

    currentLevel--;

    return ifNode;
}

Node *Parser::parseRepeatStatement()
{
    // Parse the REPEAT statement
    match(Token::TokenType::REPEAT);
    Node* repeatNode = new Node(Node::NodeType::Repeat);
    repeatNode->setLevel(currentLevel);

    currentLevel++;

    // Parse the statement sequence
    Node* stmtSeqNode = parseStmtSequence();
    stmtSeqNode->setLevel(currentLevel);
    repeatNode->addChild(stmtSeqNode);

    match(Token::TokenType::UNTIL);

    // Parse the expression
    Node* expNode = parseExp();
    expNode->setLevel(currentLevel);
    repeatNode->addChild(expNode);

    currentLevel--;

    return repeatNode;
}

Node *Parser::parseAssignStatement()
{
    // get the id value
    if(!tokenIterator.hasNext())
    {
        throw std::out_of_range("Unexpected end of file");
    }

    QString idValue = tokenIterator.peekNext().getValue();
    // match the id
    match(Token::TokenType::IDENTIFIER);

    // parse the assignment operator
    match(Token::TokenType::ASSIGN);

    Node* assignNode = new Node(Node::NodeType::Assign);
    assignNode->setLevel(currentLevel);
    assignNode->setValue(idValue);

    // parse the expression
    Node* expNode = parseExp();
    expNode->setLevel(currentLevel + 1);
    assignNode->addChild(expNode);

    return assignNode;
}

Node *Parser::parseReadStatement()
{
    // parse the READ statement
    match(Token::TokenType::READ);
    Node* readNode = new Node(Node::NodeType::Read);
    readNode->setLevel(currentLevel);

    // get the id value
    if(!tokenIterator.hasNext())
    {
        throw std::out_of_range("Unexpected end of file");
    }

    QString idValue = tokenIterator.peekNext().getValue();
    // match the id
    match(Token::TokenType::IDENTIFIER);

    readNode->setValue(idValue);

    return readNode;
}


Node *Parser::parseWriteStatement()
{
    // parse the WRITE statement
    match(Token::TokenType::WRITE);
    Node* writeNode = new Node(Node::NodeType::Write);
    writeNode->setLevel(currentLevel);

    // parse the expression
    Node* expNode = parseExp();
    expNode->setLevel(currentLevel + 1);
    writeNode->addChild(expNode);

    return writeNode;
}

Node *Parser::parseExp()
{
    Node* simpleExpNode = parseSimpleExp();

    if(tokenIterator.hasNext() && (tokenIterator.peekNext().getType() == Token::TokenType::LESSTHAN || tokenIterator.peekNext().getType() == Token::TokenType::EQUAL))
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
    // Parse the first term
    Node* firstTerm = parseTerm();

    // Vectors to store terms and operators
    std::vector<Node*> terms;
    std::vector<Node*> ops;

    terms.push_back(firstTerm);

    // Collect all following operators and terms
    while (tokenIterator.hasNext() &&
           (tokenIterator.peekNext().getType() == Token::TokenType::PLUS ||
            tokenIterator.peekNext().getType() == Token::TokenType::MINUS))
    {
        Node* opNode = parseAddop();    // parse the operator
        Node* nextTerm = parseTerm();   // parse the next term

        ops.push_back(opNode);
        terms.push_back(nextTerm);
    }

    // Now we have all terms and operators.
    // Example: For "a + a + a + a":
    // terms = [a, a, a, a]
    // ops   = [+, +, +]

    // Decide how to build the tree. For example, if you want the last term deepest,
    // you might build the tree right-associatively:
    // a + a + a + a = a + (a + (a + a))

    // Start from the left
    Node* root = terms[0]; // The first term is the initial root
    for (int i = 0; i < (int)ops.size(); i++) {
        Node* op = ops[i];
        Node* rightTerm = terms[i + 1]; // The next term after the operator

        // For left-associativity: op(root, rightTerm)
        op->addChild(root);
        op->addChild(rightTerm);

        root = op; // Now op becomes the current root
    }

    // Now 'root' is left-associative
    assignLevels(root, currentLevel);
    return root;
}


Node *Parser::parseComparisonOp()
{
    if(!tokenIterator.hasNext())
    {
        throw std::out_of_range("Unexpected end of file");
    }

    if(tokenIterator.peekNext().getType() != Token::TokenType::LESSTHAN && tokenIterator.peekNext().getType() != Token::TokenType::EQUAL)
    {
        throw std::invalid_argument("Unexpected token: " + tokenIterator.peekNext().getValue().toStdString());
    }

    Node* opNode = new Node(Node::NodeType::Op);
    opNode->setLevel(currentLevel);
    opNode->setValue(tokenIterator.peekNext().getValue());

    if(tokenIterator.peekNext().getType() == Token::TokenType::LESSTHAN)
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
    if(!tokenIterator.hasNext())
    {
        throw std::out_of_range("Unexpected end of file");
    }

    if(tokenIterator.peekNext().getType() != Token::TokenType::PLUS && tokenIterator.peekNext().getType() != Token::TokenType::MINUS)
    {
        throw std::invalid_argument("Unexpected token: " + tokenIterator.peekNext().getValue().toStdString());
    }

    Node* opNode = new Node(Node::NodeType::Op);
    opNode->setLevel(currentLevel);
    opNode->setValue(tokenIterator.peekNext().getValue());

    if(tokenIterator.peekNext().getType() == Token::TokenType::PLUS)
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
    // Parse the first factor
    Node* firstFactor = parseFactor();

    // Temporary storage for factors and operators
    std::vector<Node*> factors;
    std::vector<Node*> ops;

    factors.push_back(firstFactor);

    // Collect all subsequent operators and factors
    while (tokenIterator.hasNext() &&
           (tokenIterator.peekNext().getType() == Token::TokenType::MULT ||
            tokenIterator.peekNext().getType() == Token::TokenType::DIV))
    {
        Node* opNode = parseMulop();
        Node* nextFactor = parseFactor();

        ops.push_back(opNode);
        factors.push_back(nextFactor);
    }

    // Now build the tree from these operators and factors.
    Node* root = factors[0]; // Start with the first factor
    for (int i = 0; i < (int)ops.size(); i++) {
        Node* op = ops[i];
        Node* rightFactor = factors[i + 1];

        // Left-associative: ( (firstFactor op secondFactor) op thirdFactor ) op fourthFactor
        op->addChild(root);
        op->addChild(rightFactor);

        root = op; // Update root
    }

    assignLevels(root, currentLevel);
    return root;
}

Node *Parser::parseMulop()
{
    if(!tokenIterator.hasNext())
    {
        throw std::out_of_range("Unexpected end of file");
    }

    if(tokenIterator.peekNext().getType() != Token::TokenType::MULT && tokenIterator.peekNext().getType() != Token::TokenType::DIV)
    {
        throw std::invalid_argument("Unexpected token: " + tokenIterator.peekNext().getValue().toStdString());
    }

    Node* opNode = new Node(Node::NodeType::Op);
    opNode->setLevel(currentLevel);
    opNode->setValue(tokenIterator.peekNext().getValue());

    if(tokenIterator.peekNext().getType() == Token::TokenType::MULT)
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
    if(!tokenIterator.hasNext())
    {
        throw std::out_of_range("Unexpected end of file");
    }

    Node* factorNode = nullptr;

    switch(tokenIterator.peekNext().getType())
    {
        case Token::TokenType::OPENBRACKET:
            match(Token::TokenType::OPENBRACKET);
            factorNode = parseExp();
            factorNode->setLevel(currentLevel);
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
            throw std::invalid_argument("Unexpected token: " + tokenIterator.peekNext().getValue().toStdString());
    }

    return factorNode;
}


