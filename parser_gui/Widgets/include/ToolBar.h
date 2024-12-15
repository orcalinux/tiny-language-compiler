#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QAction>
#include <QDebug>
#include <QIcon>
#include <QObject>
#include <QToolBar>
#include <QVector>
#include <functional>
#include <QActionGroup>

namespace Tiny::Widgets {

class ToolBar : public QToolBar {
    Q_OBJECT
   public:
    enum class ActionName {
        NewTextFile,
        NewTokensFile,
        OpenFile,
        SaveFile,
        SaveAsFile,
        ViewTextFile,
        ViewTokens,
        ViewParseTree,
        ViewSyntaxTree,
        Help,
        About
    };

    explicit ToolBar(QWidget* parent = nullptr);
    ~ToolBar();

    QAction* getAction(ActionName name);
    void setActionChecked(ActionName name, bool checked);
    void setActionEnabled(ActionName name, bool enabled);

   private:
    QVector<QAction*> actions;

    void initFileActions();
    void initViewActions();
    void initHelpActions();

    struct Action {
        ActionName name;
        QString statusTip;
        QKeySequence shortcut;
        std::function<void()> slot;
    };
    QAction* addToolbarAction(Action* action, bool onOffAction = false, bool onByDefault = false);

    void initStyle();

    // lookup table for action enum to string
    static const QMap<ActionName, QString> actionNameToString;

   public slots:

   signals:
    void newTextTab();
    void newTokensTab();

    void showTokens();
    void showText();

};  // class ToolBar
}  // namespace Tiny::Widgets
#endif  // TOOLBAR_H
