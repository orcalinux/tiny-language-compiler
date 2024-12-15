// Parser.h
#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QList>

#include "Token.h"
#include "Node.h"

using namespace Tiny::Data;

namespace Tiny::Parser {
    class Parser : public QObject {
        Q_OBJECT
       public:
        explicit Parser(QObject *parent = nullptr);
        ~Parser() override;

        void setTokens(QList<Token> tokens);
        Node* parse();
        signals:
            void error(QString message);
        private:
            QList<Token> tokens;
            int currentTokenIndex;
            int currentLevel;

            void advance();

            void expectAndSkip(Token::TokenType type);
            Node* consume(Token::TokenType tokenType, Tiny::Data::Node::NodeType nodeType);

            // rules
            Node* parseStmtSequence();
            Node* parseStatement();
            Node* parseIfStatement();
            Node* parseRepeatStatement();
            Node* parseAssignStatement();
            Node* parseReadStatement();
            Node* parseWriteStatement();
            Node* parseExp();
            Node* parseSimpleExp();
            Node* parseComparisonOp();
            Node* parseAddop();
            Node* parseTerm();
            Node* parseMulop();
            Node* parseFactor();
    };


}  // namespace Tiny::Parser

#endif  // PARSER_H
