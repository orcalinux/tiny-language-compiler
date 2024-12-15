#include "TreeVisualiser.h"
#include <QPainter>
#include <QWheelEvent>

using Tiny::Widgets::TreeVisualiser;

void TreeVisualiser::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    if (!root) return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(rect(), QColor(240, 240, 240));
    painter.scale(zoomFactor, zoomFactor);

    // Compute positions before drawing
    computePositions();

    // Draw the entire tree now
    drawTree(&painter, root);
}

TreeVisualiser::TreeVisualiser(QWidget *parent) : QWidget(parent) {

}

void TreeVisualiser::drawTree(QPainter *painter, Node *node)
{
    if (!node) return;

    QPoint pos = positions[node];

    // Draw this node
    painter->setPen(QPen(Qt::black, 2));
    painter->setBrush(QColor(70, 130, 180)); // Steel Blue

    if (isOval(node->getType())) {
        painter->drawEllipse(pos.x() - 20, pos.y() - 20, 40, 40);
    } else {
        painter->drawRect(pos.x() - 40, pos.y() - 20, 80, 40);
    }

    painter->setPen(Qt::white);
    QString nodeText;
    if (!hasValue(node->getType())) {
        nodeText = node->getNodeTypeString().toString() + "\n(" + node->getValue() + ")";
    } else {
        nodeText = node->getNodeTypeString().toString();
    }

    painter->drawText(QRect(pos.x() - 40, pos.y() - 20, 80, 40),
                      Qt::AlignCenter | Qt::TextWordWrap, nodeText);

    // Draw lines to children
    painter->setPen(QPen(Qt::black, 2));
    for (Node* child : node->getChildren()) {
        QPoint childPos = positions[child];
        painter->drawLine(pos.x(), pos.y() + 20, childPos.x(), childPos.y() - 20);
        drawTree(painter, child); // Recursively draw children
    }

}

void TreeVisualiser::drawTree(QPainter *painter, Node *node, int x, int y, int availableWidth, int level) {
    if (!node) return;

    QPoint pos = positions[node];

    // Draw this node
    painter->setPen(QPen(Qt::black, 2));
    painter->setBrush(QColor(70, 130, 180)); // Steel Blue

    if (isOval(node->getType())) {
        painter->drawEllipse(pos.x() - 20, pos.y() - 20, 40, 40);
    } else {
        painter->drawRect(pos.x() - 40, pos.y() - 20, 80, 40);
    }

    painter->setPen(Qt::white);
    QString nodeText;
    if (!hasValue(node->getType())) {
        nodeText = node->getNodeTypeString().toString() + "\n(" + node->getValue() + ")";
    } else {
        nodeText = node->getNodeTypeString().toString();
    }

    painter->drawText(QRect(pos.x() - 40, pos.y() - 20, 80, 40),
                      Qt::AlignCenter | Qt::TextWordWrap, nodeText);

    // Draw lines to children
    painter->setPen(QPen(Qt::black, 2));
    for (Node* child : node->getChildren()) {
        QPoint childPos = positions[child];
        painter->drawLine(pos.x(), pos.y() + 20, childPos.x(), childPos.y() - 20);
        drawTree(painter, child); // Recursively draw children
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

