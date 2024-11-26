#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>
#include <QAction>
#include <QIcon>
#include <QDebug>
#include <QObject>
#include <QVector>

#include <functional>

namespace Tiny::Widgets {

class ToolBar : public QToolBar
{
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

    explicit ToolBar(QWidget *parent = nullptr);
    ~ToolBar();


    QAction* getAction(const QString& name);
    void setActionEnabled(const QString& name, bool enabled);
    void setActionVisible(const QString& name, bool visible);

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
    void addToolbarAction(Action* action, bool onOffAction = false, bool onByDefault = false);

    void initStyle();

    // lookup table for action enum to string
    static const QMap<ActionName, QString> actionNameToString;



public slots:

signals:



}; // class ToolBar
} // namespace Tiny::Widgets
#endif // TOOLBAR_H
