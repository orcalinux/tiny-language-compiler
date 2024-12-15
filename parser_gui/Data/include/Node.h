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
        Read,
        Write,
        If,
        Repeat,
        Assign,
        Op,
        Id,
        Const
    }; // enum class NodeType


    explicit Node(NodeType type);
    ~Node();

    // getters
    QString getValue() const;
    NodeType getType() const;
    QStringView getNodeTypeString() const;
    Node *getParent() const;
    QList<Node *> getChildren() const;
    int getLevel() const;

    // setters
    void setValue(QString value);
    void setType(NodeType type);
    void setParent(Node *parent);
    void setLevel(int level);

    // add children
    void addChild(Node *child);

    // print tree
    void printTree(int depth = 0) const;

private:
    QString value;
    NodeType type;
    Node *parent;
    QList<Node *> children;
    int level;



    static constexpr std::array<QLatin1StringView, 8> nodeTypeStrings = {
        QLatin1StringView("Read"),
        QLatin1StringView("Write"),
        QLatin1StringView("If"),
        QLatin1StringView("Repeat"),
        QLatin1StringView("Assign"),
        QLatin1StringView("Op"),
        QLatin1StringView("Id"),
        QLatin1StringView("Const")
    }; // nodeTypeStrings Lookup Table

}; // class Node

} // namespace Tiny::Data

#endif // NODE_H
