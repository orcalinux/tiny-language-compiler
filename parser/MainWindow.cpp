#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // set the window title
    setWindowTitle("Tiny Parser");

    // set the window size
    resize(800, 600);

    // initialize the toolbar
    initToolbar();

    // initialize the status bar
    initStatusBar();
}

MainWindow::~MainWindow() {}

void MainWindow::initToolbar()
{
    // Create a new toolba
    Tiny::Widgets::ToolBar *toolbar = new Tiny::Widgets::ToolBar(this);
    this->addToolBar(toolbar);
}

void MainWindow::initStatusBar()
{
    // Create a new status bar
    QStatusBar *statusBar = new QStatusBar(this);
    this->setStatusBar(statusBar);
}


