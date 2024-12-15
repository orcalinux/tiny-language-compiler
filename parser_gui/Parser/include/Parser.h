#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QList>
#include <stdexcept>
#include <QListIterator>

#include "Token.h"
#include "Node.h"

namespace Tiny {
namespace Parser {

/**
 * @class Parser
 * @brief A parser for the TINY language that constructs a syntax tree from a list of tokens.
 *
 * The Parser class takes a list of tokens (produced by the scanner) and attempts to construct a
 * syntax tree according to the TINY language grammar rules. It emits errors or throws exceptions
 * if unexpected tokens or end-of-file conditions occur.
 *
 * Usage:
 * 1. Create a Parser object.
 * 2. Call setTokens() with the token list.
 * 3. Call parse() to parse the entire token list and produce a syntax tree root Node.
 * 4. If parsing is successful, you get a syntax tree. If errors occur, handle them as needed.
 */
class Parser : public QObject {
    Q_OBJECT
public:
    explicit Parser(QObject *parent = nullptr);
    ~Parser() override;

    /**
     * @brief Set the token list to be parsed.
     * @param tokens The list of tokens produced by the scanner.
     */
    void setTokens(QList<Tiny::Data::Token> tokens);

    /**
     * @brief Parse the entire set of tokens and build a syntax tree.
     * @return A pointer to the root Node of the syntax tree if successful, or nullptr if empty.
     * @throws std::out_of_range if unexpected end of file (no more tokens) is encountered improperly.
     * @throws std::invalid_argument if a token does not match the expected type.
     */
    Tiny::Data::Node* parse();

signals:
    /**
     * @brief Emitted when a parsing error occurs (e.g., unexpected token or EOF).
     * @param message A descriptive error message.
     */
    void error(QString message);

private:
    QList<Tiny::Data::Token> tokens;  ///< The list of tokens to parse.
    QListIterator<Tiny::Data::Token> tokenIterator;  ///< Iterator for the token list.
    int currentLevel;                 ///< Current nesting level for the syntax tree.
    bool hasError;                    ///< Flag indicating if an error occurred during parsing.

    /**
     * @brief Peek at the current token without consuming it.
     * @return The current token.
     * @throws std::out_of_range if no more tokens.
     */
    Tiny::Data::Token peek();

    void match(Tiny::Data::Token::TokenType expectedType);

    void assignLevels(Tiny::Data::Node* node, int baseLevel);

    // Grammar rules:
    Tiny::Data::Node* parseStmtSequence();
    Tiny::Data::Node* parseStatement();
    Tiny::Data::Node* parseIfStatement();
    Tiny::Data::Node* parseRepeatStatement();
    Tiny::Data::Node* parseAssignStatement();
    Tiny::Data::Node* parseReadStatement();
    Tiny::Data::Node* parseWriteStatement();
    Tiny::Data::Node* parseExp();
    Tiny::Data::Node* parseSimpleExp();
    Tiny::Data::Node* parseComparisonOp();
    Tiny::Data::Node* parseAddop();
    Tiny::Data::Node* parseTerm();
    Tiny::Data::Node* parseMulop();
    Tiny::Data::Node* parseFactor();
};

} // namespace Parser
} // namespace Tiny

#endif // PARSER_H
