#include "Node.h"

using namespace Tiny::Data;

Node::Node(NodeType type, QString value, Node *parent)
: type(type), value(value), parent(parent)
{}

Node::~Node()
{
    for (auto child : children)
    {
        delete child;
    }
}

QString Node::getValue() const
{
    return value;
}

Node::NodeType Node::getType() const
{
    return type;
}

QStringView Node::getNodeTypeString() const
{
    size_t index = static_cast<size_t>(type);

    // Ensure the index is valid and within range
    if (index >= nodeTypeStrings.size())
    {
        throw std::out_of_range("Invalid NodeType index");
    }

    // Return the string representation of the node type
    return QStringView(nodeTypeStrings[index].toString());
}

Node *Node::getParent() const
{
    return parent;
}

QList<Node *> Node::getChildren() const
{
    return children;
}

int Node::getLevel() const
{
    return level;
}

void Node::setValue(QString value)
{
    this->value = value;
}

void Node::setType(NodeType type)
{
    this->type = type;
}

void Node::setParent(Node *parent)
{
    this->parent = parent;
    parent->addChild(this);
}

void Node::setLevel(int level)
{
    this->level = level;
}

void Node::addChild(Node *child)
{
    this->children.append(child);
    child->setParent(this);
}

void Node::printTree(int depth) const
{
    qDebug().noquote() << QString(depth * 2, ' ') << this->getNodeTypeString() << ": " << value;
    for (auto child : children)
    {
        child->printTree(depth + 1);
    }

}
