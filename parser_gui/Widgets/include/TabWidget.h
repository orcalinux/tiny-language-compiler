#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTabWidget>
#include <QVBoxLayout>

namespace Tiny::Widgets {

class TabWidget : public QTabWidget {
    Q_OBJECT
   public:
    explicit TabWidget(QWidget* parent = nullptr);

   signals:

   public slots:
    void addTabRequest(bool tokenOnly = false);

    void newTextTab();
    void newTokensTab();

    void openTextTab();
    void openTokensTab();

   private:
    QWidget* defaultTab;
    size_t counter = 0;

    void initStyle();
    void initConfig();

    void putDefaultTab();

    void defaultTabLayout();
    void createDefaultTab();

   private slots:
    void closeTab(int index);
};  // class TabWidget

}  // namespace Tiny::Widgets

#endif  // TABWIDGET_H
