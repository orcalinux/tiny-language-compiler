#include "TreeVisualiser.h"
#include <QPainter>
#include <QWheelEvent>

using Tiny::Widgets::TreeVisualiser;
using Tiny::Data::Node;

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
    // init the error label
    errorLabel = new QLabel(this);
    errorLabel->setAlignment(Qt::AlignCenter);
    errorLabel->setWordWrap(true);
    errorLabel->setVisible(false); // Hidden by default

    // Set font properties for better visibility
    QFont font = errorLabel->font();
    font.setPointSize(14);
    font.setBold(true);
    errorLabel->setFont(font);

    // Set bright text color
    errorLabel->setStyleSheet("QLabel { color : red; background-color: transparent; }");

    // Adjust label size and position
    errorLabel->setFixedSize(width(), height());
    errorLabel->setGeometry(0, 0, width(), height());

}

void TreeVisualiser::drawTree(QPainter* painter, Node *node)
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
        if (child->getLevel() == node->getLevel()) {
            painter->drawLine(pos.x() + 40, pos.y(), childPos.x(), childPos.y());
            painter->setBrush(QColor(255, 0, 0)); // Red
            painter->drawEllipse(pos.x() + 40 - 3, pos.y()- 3, 6, 6);
            painter->drawEllipse(childPos.x() - 45, childPos.y()-3, 6, 6);
        } else {
            painter->drawLine(pos.x(), pos.y() + 20, childPos.x(), childPos.y() - 20);
            painter->setBrush(QColor(255, 0, 0)); // Red
            painter->drawEllipse(pos.x()-3, pos.y() + 20-3, 6, 6);
            painter->drawEllipse(childPos.x()-3, childPos.y()- 20-3, 6, 6);
        }
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
        painter->setBrush(QColor(255, 0, 0)); // Red
        painter->drawEllipse(pos.x()-3, pos.y() + 20-3, 6, 6);
        painter->drawEllipse(childPos.x()-3, childPos.y()- 20-3, 6, 6);
        drawTree(painter, child); // Recursively draw children
    }
}

void TreeVisualiser::displayError(Token token, const QString &errorMessage, bool isUnexpectedToken)
{
    // Construct the full error message
    QString fullMessage;
    if (isUnexpectedToken) {
        fullMessage = QString("Scanner Error: Unexpected Tokens marked in red");
    } else {
        // get the token position, value and type
        fullMessage = QString("Parser Error: Unexpected token %1 at line %2, column %3")
                .arg(token.getValue())
                .arg(token.getLine())
                .arg(token.getColumn());
        // append the error message
        fullMessage.append("\n");
        fullMessage.append(errorMessage);
    }

    // Set the message to the label
    errorLabel->setText(fullMessage);
    errorLabel->setStyleSheet("QLabel { color : yellow; background-color: rgba(0, 0, 0, 150); }");
    errorLabel->setVisible(true);

    // update the widget
    update();
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

