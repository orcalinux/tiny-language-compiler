#include "TreeVisualiser.h"

using Tiny::Widgets::TreeVisualiser;

TreeVisualiser::TreeVisualiser(QWidget *parent) : QWidget(parent) {
    // set the layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    // set the style
    setStyleSheet("background-color: #2e2e2e ; color: #c0c0c0; border: 1px solid #2a2a2a;");

    // add the label
    QLabel* label = new QLabel("Tree Visualiser");
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("font-size: 20px; color: #c0c0c0;");

    // add the label to the layout
    layout->addWidget(label);
}

void TreeVisualiser::setRoot(Node *root)
{
    qDebug() << "Drawing tree";
    // print the tree
    root->printTree();
}
