#ifndef NODE_H
#define NODE_H

#include <QString>
#include <QList>
#include <QStringView>
#include <QLatin1StringView>
#include <QDebug>

#include <array>


namespace Tiny::Data {
class Node {

public:
    enum class NodeType {
        Program,
        Statement,
        IfStatement,
        RepeatStatement,
        AssignStatement,
        ReadStatement,
        WriteStatement,
        Expression,
        Comparison,
        Addition,
        Multiplication,
        Factor,
        Identifier,
        Number
    }; // enum class NodeType


    explicit Node(NodeType type, QString value, Node *parent = nullptr);
    ~Node();

    // getters
    QString getValue() const;
    NodeType getType() const;
    QStringView getNodeTypeString() const;
    Node *getParent() const;
    QList<Node *> getSiblings() const;
    QList<Node *> getChildren() const;

    // setters
    void setValue(QString value);
    void setType(NodeType type);
    void setParent(Node *parent);

    // add children
    void addChild(Node *child);

    // add siblings
    void addSibling(Node *sibling);

    // print tree
    void printTree(int depth = 0) const;

private:
    QString value;
    NodeType type;
    Node *parent;
    QList<Node *> siblings;
    QList<Node *> children;




    static constexpr std::array<QLatin1StringView, 14> nodeTypeStrings = {
        QLatin1StringView("Program"),
        QLatin1StringView("Statement"),
        QLatin1StringView("IfStatement"),
        QLatin1StringView("RepeatStatement"),
        QLatin1StringView("AssignStatement"),
        QLatin1StringView("ReadStatement"),
        QLatin1StringView("WriteStatement"),
        QLatin1StringView("Expression"),
        QLatin1StringView("Comparison"),
        QLatin1StringView("Addition"),
        QLatin1StringView("Multiplication"),
        QLatin1StringView("Factor"),
        QLatin1StringView("Identifier"),
        QLatin1StringView("Number")
    }; // nodeTypeStrings Lookup Table

}; // class Node

} // namespace Tiny::Data

#endif // NODE_H
