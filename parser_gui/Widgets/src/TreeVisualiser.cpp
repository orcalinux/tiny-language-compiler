#include "TreeVisualiser.h"
#include <QPainter>
#include <QWheelEvent>

using Tiny::Widgets::TreeVisualiser;

void TreeVisualiser::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    if (!root) return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Clear background
    painter.fillRect(rect(), QColor(240, 240, 240));
    painter.scale(zoomFactor, zoomFactor);

    // Calculate the total width needed for the tree
    int treeWidth = calculateTreeWidth(root);

    // Draw the entire tree
    drawTree(&painter, root, width() / 2, 50, treeWidth, root->getLevel());
}

TreeVisualiser::TreeVisualiser(QWidget *parent) : QWidget(parent) {
    Node *nroot = new Node(Node::NodeType::Expression, "+");
    nroot->setLevel(1);
    Node *child1 = new Node(Node::NodeType::Number, "3");
    child1->setLevel(2);
    Node *child2 = new Node(Node::NodeType::Number, "4");
    child2->setLevel(1);
    Node *child3 = new Node(Node::NodeType::Number, "5");
    child3->setLevel(3);

    Node *child4 = new Node(Node::NodeType::Number, "A7a");
    Node *child5 = new Node(Node::NodeType::Addition, "5555555");

    this->root = nroot;
    this->root->addChild(child1);
    this->root->addChild(child2);
    child2->addChild(child3);
    child2->addChild(child4);
    child1->addChild(child5);
}

void TreeVisualiser::drawTree(QPainter *painter, Node *node, int x, int y, int availableWidth, int level) {
    if (!node) return;

    // Draw the current node
    painter->setPen(QPen(Qt::black, 2));
    painter->setBrush(QColor(70, 130, 180)); // Steel Blue

    if (isOval(node->getType())) {
        painter->drawEllipse(x - 20, y - 20, 40, 40); // Node as an oval
    } else {
        painter->drawRect(x - 40, y - 20, 80, 40);    // Node as a rectangle
    }

    // Draw node value
    painter->setPen(Qt::white);
    QString nodeText;
    if (!hasValue(node->getType())) {
        nodeText = node->getNodeTypeString().toString() + "\n(" + node->getValue() + ")";
    } else {
        nodeText = node->getValue();
    }
    painter->drawText(QRect(x - 40, y - 20, 80, 40),
                      Qt::AlignCenter | Qt::TextWordWrap, nodeText);

    if (node->getChildren().empty()) return;

    // Calculate the total width and starting positions for children
    int childCount = node->getChildren().size();
    std::vector<int> childWidths;
    int totalChildWidth = 0;

    // Calculate width for each child's subtree
    for (Node* child : node->getChildren()) {
        int childWidth = calculateTreeWidth(child);
        childWidths.push_back(childWidth);
        totalChildWidth += childWidth;
    }

    // Vertical and horizontal spacing between nodes
    int verticalSpacing = 100;
    int horizontalSpacing = 100;

    // Starting X position for the first child node
    int startX = x - totalChildWidth / 2;

    // Draw children and their subtrees
    for (size_t i = 0; i < node->getChildren().size(); ++i) {
        Node* child = node->getChildren()[i];
        int childWidth = childWidths[i];

        // Calculate position for each child
        int childX = startX + childWidth / 2;
        int childY = (child->getLevel() == node->getLevel())? y : y + verticalSpacing;

        // Draw connection line to child node
        painter->setPen(QPen(Qt::black, 2));
        int yLineOffset = (child->getLevel() == node->getLevel())? 0 : 20;

        painter->drawLine(x, y + yLineOffset, childX, childY);

        // Recursively draw the child node
        drawTree(painter, child, childX, childY, childWidth, child->getLevel());

        // Update the starting position for the next child
        startX += childWidth + horizontalSpacing;
    }
}

void TreeVisualiser::wheelEvent(QWheelEvent *event)
{
    const qreal zoomStep = 0.1;   // Amount to zoom in/out
    const qreal minZoom = 0.5;   // Minimum zoom level
    const qreal maxZoom = 3.0;   // Maximum zoom level

    if (event->angleDelta().y() > 0) {
        // Zoom in
        zoomFactor = qMin(maxZoom, zoomFactor + zoomStep);
    } else {
        // Zoom out
        zoomFactor = qMax(minZoom, zoomFactor - zoomStep);
    }

    update(); // Redraw the widget
}

