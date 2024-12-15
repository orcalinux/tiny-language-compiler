#ifndef TREEVISUALISER_H
#define TREEVISUALISER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

#include "Node.h"

namespace Tiny::Widgets {
    class TreeVisualiser : public QWidget {
        Q_OBJECT
       public:
        TreeVisualiser(QWidget *parent = nullptr);
        void drawTree(Node* root);

    }; // class TreeVisualiser
}  // namespace Tiny::Widgets

#endif  // TREEVISUALISER_H
