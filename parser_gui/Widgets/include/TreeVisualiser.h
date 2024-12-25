#ifndef TREEVISUALISER_H
#define TREEVISUALISER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QQueue>
#include <QMap>


#include "Node.h"
#include "Token.h"

namespace Tiny::Widgets {
    using namespace Tiny::Data;
    class TreeVisualiser : public QWidget {
        Q_OBJECT

    protected:
        void paintEvent(QPaintEvent *event) override;
        void resizeEvent(QResizeEvent *event) override {
            Q_UNUSED(event);
            errorLabel->setFixedSize(width(), height());
            errorLabel->setGeometry(0, 0, width(), height());
        }
       public:
        TreeVisualiser(QWidget *parent = nullptr);
           void drawTree(QPainter *painter, Node *root);
           void drawTree(QPainter *painter, Node *node, int x, int y, int availableWidth, int currentLevel);

        void displayError(Tiny::Data::Token token, const QString& errorMessage, bool isUnexpectedToken);
        void hideError() {
            errorLabel->setVisible(false);
        }

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

            if(root != nullptr){
                // hide the error label
                errorLabel->setVisible(false);
            }
            // update the widget
            update();
        }

        void wheelEvent(QWheelEvent* event) override;

        bool isOval(Node::NodeType type) {
            if ((type == Node::NodeType::Id) ||
                (type == Node::NodeType::Const) ||

                (type == Node::NodeType::Op)) {
                return true;
            } else {
                return false;
            }
        }

        bool hasValue(Node::NodeType type) {
            if ((type == Node::NodeType::If) ||
                    (type == Node::NodeType::Write) ||
                    (type == Node::NodeType::Repeat)
                )
                {
                return true;
            } else {
                return false;
            }
        }

        void computePositions() {
            positions.clear();
            if (!root) return;

            // BFS to gather nodes by level
            QQueue<Node*> queue;
            queue.enqueue(root);

            QMap<int, QList<Node*>> levelMap;
            int maxLevel = 0;

            while (!queue.isEmpty()) {
                Node* current = queue.dequeue();
                int lvl = current->getLevel();
                maxLevel = qMax(maxLevel, lvl);
                levelMap[lvl].append(current);

                for (Node* child : current->getChildren()) {
                    queue.enqueue(child);
                }
            }

            // Now assign positions level by level
            int W = width(); // widget width
            for (int lvl = 0; lvl <= maxLevel; lvl++) {
                QList<Node*>& nodesAtLevel = levelMap[lvl];
                int N = nodesAtLevel.size();
                if (N == 0) continue;

                int spacing = W / (N + 1);
                int yPos = 50 + lvl * 100; // each level 100px apart vertically
                for (int i = 0; i < N; i++) {
                    Node* n = nodesAtLevel[i];
                    int xPos = spacing * (i + 1);
                    positions[n] = QPoint(xPos, yPos);
                }
            }
        }
    private:
        Node *root = nullptr;
        qreal zoomFactor = 1.0;
        QMap<Node*, QPoint> positions;

        QLabel *errorLabel;

    }; // class TreeVisualiser
}  // namespace Tiny::Widgets

#endif  // TREEVISUALISER_H
