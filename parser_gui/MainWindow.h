#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QGuiApplication>
#include <QMainWindow>
#include <QScreen>
#include <QStatusBar>
#include <QStyle>
#include <QToolBar>

#include "TabWidget.h"
#include "ToolBar.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   private:
    Tiny::Widgets::TabWidget *tabWidget;

    void initToolbar();
    void initStatusBar();
    void initTabWidget();
};
#endif  // MAINWINDOW_H
