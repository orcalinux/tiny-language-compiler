#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    // set the window title
    setWindowTitle("Tiny Parser");

    // set the window size
    resize(800, 600);

    // initialize the toolbar
    initToolbar();

    // initialize the status bar
    initStatusBar();

    // initialize the tab widget
    initTabWidget();
}

MainWindow::~MainWindow() {}

void MainWindow::initToolbar() {
    // Create a new toolba
    Tiny::Widgets::ToolBar *toolbar = new Tiny::Widgets::ToolBar(this);
    this->addToolBar(toolbar);
}

void MainWindow::initStatusBar() {
    // Create a new status bar
    QStatusBar *statusBar = new QStatusBar(this);
    this->setStatusBar(statusBar);
}

void MainWindow::initTabWidget() {
    // Create a new tab widget
    tabWidget = new Tiny::Widgets::TabWidget(this);
    this->setCentralWidget(tabWidget);

    // get the toolbar
    Tiny::Widgets::ToolBar *toolbar = this->findChild<Tiny::Widgets::ToolBar *>();

    // connect tolbar buttons to tab widget slots
    connect(toolbar, &Tiny::Widgets::ToolBar::newTextTab, tabWidget, &Tiny::Widgets::TabWidget::newTextTab);
    connect(toolbar, &Tiny::Widgets::ToolBar::newTokensTab, tabWidget, &Tiny::Widgets::TabWidget::newTokensTab);

    connect(toolbar, &Tiny::Widgets::ToolBar::openFile, tabWidget, &Tiny::Widgets::TabWidget::openTextTab);
    connect(toolbar, &Tiny::Widgets::ToolBar::saveFile, tabWidget, &Tiny::Widgets::TabWidget::saveCurrentTab);

    // set the toolbar in the tab widget
    tabWidget->setToolBar(toolbar);
}
