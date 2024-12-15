#ifndef TREEVISUALISER_H
#define TREEVISUALISER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>

#include "Node.h"

namespace Tiny::Widgets {
    using namespace Tiny::Data;
    class TreeVisualiser : public QWidget {
        Q_OBJECT

    protected:
        void paintEvent(QPaintEvent *event) override;
       public:
        TreeVisualiser(QWidget *parent = nullptr);
           void drawTree(QPainter *painter, Node *node, int x, int y, int availableWidth, int currentLevel);

        int calculateTreeWidth(Node* node) {
            if (!node || node->getChildren().empty()) return 50;

            int totalWidth = 0;
            for (Node* child : node->getChildren()) {
                totalWidth += calculateTreeWidth(child);
            }
            return std::max(totalWidth, 50);
        }

        void setRoot(Node *root) {
            this->root = root;
        }

        void wheelEvent(QWheelEvent* event) override;

        bool isOval(Node::NodeType type) {
            if ((type == Node::NodeType::Identifier) ||
                (type == Node::NodeType::Number) ||
                (type == Node::NodeType::Comparison)) {
                return true;
            } else {
                return false;
            }
        }

        bool hasValue(Node::NodeType type) {
            if ((type == Node::NodeType::Identifier) ||
                (type == Node::NodeType::Number) ||
                (type == Node::NodeType::ReadStatement) ||
                (type == Node::NodeType::AssignStatement) ||
                (type == Node::NodeType::Comparison)) {
                return true;
            } else {
                return false;
            }
        }
    private:
        Node *root = nullptr;
        qreal zoomFactor = 1.0;
    }; // class TreeVisualiser
}  // namespace Tiny::Widgets

#endif  // TREEVISUALISER_H
