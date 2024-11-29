/**
 * @file syntax_tree.hpp
 * @brief Defines the classes for syntax tree nodes used by the TINY language parser.
 *
 * The syntax tree represents the hierarchical structure of the parsed program.
 */

#ifndef SYNTAX_TREE_HPP
#define SYNTAX_TREE_HPP

#include <memory>
#include <vector>
#include <string>

namespace TINY::PARSER
{

    /**
     * @class SyntaxTreeNode
     * @brief Base class for all syntax tree nodes.
     */
    class SyntaxTreeNode
    {
    public:
        virtual ~SyntaxTreeNode() = default;

        /**
         * @brief Converts the syntax tree node to a string representation.
         * @param indentation The indentation level for pretty-printing.
         * @return A string representing the node.
         */
        virtual std::string toString(int indentation = 0) const = 0;
    };

    /**
     * @class StatementSequenceNode
     * @brief Represents a sequence of statements.
     */
    class StatementSequenceNode : public SyntaxTreeNode
    {
    public:
        void addStatement(std::unique_ptr<SyntaxTreeNode> statement);
        std::string toString(int indentation = 0) const override;

    private:
        std::vector<std::unique_ptr<SyntaxTreeNode>> statements;
    };

    /**
     * @class IfStatementNode
     * @brief Represents an if-then-else statement.
     */
    class IfStatementNode : public SyntaxTreeNode
    {
    public:
        IfStatementNode(std::unique_ptr<SyntaxTreeNode> condition,
                        std::unique_ptr<SyntaxTreeNode> thenPart,
                        std::unique_ptr<SyntaxTreeNode> elsePart);

        std::string toString(int indentation = 0) const override;

    private:
        std::unique_ptr<SyntaxTreeNode> condition;
        std::unique_ptr<SyntaxTreeNode> thenPart;
        std::unique_ptr<SyntaxTreeNode> elsePart;
    };

    /**
     * @class RepeatStatementNode
     * @brief Represents a repeat-until loop.
     */
    class RepeatStatementNode : public SyntaxTreeNode
    {
    public:
        RepeatStatementNode(std::unique_ptr<SyntaxTreeNode> body,
                            std::unique_ptr<SyntaxTreeNode> condition);

        std::string toString(int indentation = 0) const override;

    private:
        std::unique_ptr<SyntaxTreeNode> body;
        std::unique_ptr<SyntaxTreeNode> condition;
    };

    /**
     * @class AssignStatementNode
     * @brief Represents an assignment statement.
     */
    class AssignStatementNode : public SyntaxTreeNode
    {
    public:
        AssignStatementNode(const std::string &variableName,
                            std::unique_ptr<SyntaxTreeNode> expression);

        std::string toString(int indentation = 0) const override;

    private:
        std::string variableName;
        std::unique_ptr<SyntaxTreeNode> expression;
    };

    /**
     * @class ReadStatementNode
     * @brief Represents a read statement.
     */
    class ReadStatementNode : public SyntaxTreeNode
    {
    public:
        explicit ReadStatementNode(const std::string &variableName);

        std::string toString(int indentation = 0) const override;

    private:
        std::string variableName;
    };

    /**
     * @class WriteStatementNode
     * @brief Represents a write statement.
     */
    class WriteStatementNode : public SyntaxTreeNode
    {
    public:
        explicit WriteStatementNode(std::unique_ptr<SyntaxTreeNode> expression);

        std::string toString(int indentation = 0) const override;

    private:
        std::unique_ptr<SyntaxTreeNode> expression;
    };

    /**
     * @class OpExpressionNode
     * @brief Represents an expression with an operator.
     */
    class OpExpressionNode : public SyntaxTreeNode
    {
    public:
        OpExpressionNode(const std::string &op,
                         std::unique_ptr<SyntaxTreeNode> left,
                         std::unique_ptr<SyntaxTreeNode> right);

        std::string toString(int indentation = 0) const override;

    private:
        std::string op;
        std::unique_ptr<SyntaxTreeNode> left;
        std::unique_ptr<SyntaxTreeNode> right;
    };

    /**
     * @class ConstExpressionNode
     * @brief Represents a constant (number) in an expression.
     */
    class ConstExpressionNode : public SyntaxTreeNode
    {
    public:
        explicit ConstExpressionNode(const std::string &value);

        std::string toString(int indentation = 0) const override;

    private:
        std::string value;
    };

    /**
     * @class VariableExpressionNode
     * @brief Represents a variable in an expression.
     */
    class VariableExpressionNode : public SyntaxTreeNode
    {
    public:
        explicit VariableExpressionNode(const std::string &name);

        std::string toString(int indentation = 0) const override;

    private:
        std::string name;
    };

} // namespace TINY::PARSER

#endif // SYNTAX_TREE_HPP
