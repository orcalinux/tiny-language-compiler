/**
 * @file parser.hpp
 * @brief Declares the Parser class for parsing TINY language tokens into a syntax tree.
 *
 * The Parser reads a sequence of tokens and constructs an Abstract Syntax Tree (AST)
 * according to the grammar rules of the TINY language.
 */

#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>
#include <memory>

#include "token.hpp"
#include "syntax_tree.hpp"

namespace TINY::PARSER
{

    /**
     * @class Parser
     * @brief Parses tokens into a syntax tree based on TINY language grammar.
     *
     * The Parser implements recursive descent parsing methods for each grammar rule.
     */
    class Parser
    {
    public:
        /**
         * @brief Constructs a Parser with a given list of tokens.
         * @param tokens The list of tokens to parse.
         */
        Parser(const std::vector<SCANNER::Token> &tokens);

        /**
         * @brief Parses the tokens and returns the root of the syntax tree.
         * @return A unique pointer to the root SyntaxTreeNode.
         */
        std::unique_ptr<SyntaxTreeNode> parse();

    private:
        const std::vector<SCANNER::Token> &tokens; /**< The list of tokens to parse. */
        size_t currentTokenIndex;                  /**< Index of the current token being processed. */

        // Parsing methods for grammar rules
        std::unique_ptr<SyntaxTreeNode> parseProgram();
        std::unique_ptr<SyntaxTreeNode> parseStatementSequence();
        std::unique_ptr<SyntaxTreeNode> parseStatement();
        std::unique_ptr<SyntaxTreeNode> parseIfStatement();
        std::unique_ptr<SyntaxTreeNode> parseRepeatStatement();
        std::unique_ptr<SyntaxTreeNode> parseAssignStatement();
        std::unique_ptr<SyntaxTreeNode> parseReadStatement();
        std::unique_ptr<SyntaxTreeNode> parseWriteStatement();
        std::unique_ptr<SyntaxTreeNode> parseExpression();
        std::unique_ptr<SyntaxTreeNode> parseSimpleExpression();
        std::unique_ptr<SyntaxTreeNode> parseTerm();
        std::unique_ptr<SyntaxTreeNode> parseFactor();

        // Utility methods
        const SCANNER::Token &peekToken() const;
        const SCANNER::Token &getToken();
        bool matchToken(SCANNER::TokenType type);
        void expectToken(SCANNER::TokenType type);

        // Error handling
        void error(const std::string &message);
    };

} // namespace TINY::PARSER

#endif // PARSER_HPP
