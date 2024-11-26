#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ToolBar.h"

#include <QMainWindow>
#include <QGuiApplication>
#include <QStyle>
#include <QScreen>
#include <QDebug>
#include <QToolBar>
#include <QStatusBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    void initToolbar();
    void initStatusBar();
};
#endif // MAINWINDOW_H
