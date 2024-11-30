#include "ToolBar.h"

namespace Tiny::Widgets {

ToolBar::ToolBar(QWidget* parent) {
    // toolbar configrations
    setMovable(false);
    setFloatable(false);
    setAllowedAreas(Qt::TopToolBarArea);
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    setIconSize(QSize(25, 25));
    setOrientation(Qt::Horizontal);

    // toolbar style
    initStyle();

    // initialize the actions and separators between them
    initFileActions();
    addSeparator();
    initViewActions();
    addSeparator();
    initHelpActions();
}

ToolBar::~ToolBar() {
    foreach (auto action, this->actions) {
        delete action;
    }
}

void ToolBar::initFileActions() {
    // new text file action
    Action* newFileTextAction = new Action();
    newFileTextAction->name = ActionName::NewTextFile;
    newFileTextAction->statusTip = "Create a new text file";
    newFileTextAction->shortcut = QKeySequence::New;
    newFileTextAction->slot = [this]() {
        qDebug() << "New text file";
        emit newTextTab();
    };
    addToolbarAction(newFileTextAction);

    // new tokens file action
    Action* newTokensFileAction = new Action();
    newTokensFileAction->name = ActionName::NewTokensFile;
    newTokensFileAction->statusTip = "Create a new tokens file";
    newTokensFileAction->shortcut = QKeySequence("Ctrl+Shift+N");
    newTokensFileAction->slot = [this]() {
        qDebug() << "New tokens file";
        emit newTokensTab();
    };
    addToolbarAction(newTokensFileAction);

    // open file action
    Action* openFileAction = new Action();
    openFileAction->name = ActionName::OpenFile;
    openFileAction->statusTip = "Open a file";
    openFileAction->shortcut = QKeySequence::Open;
    openFileAction->slot = []() {
        qDebug() << "Open file";
    };
    addToolbarAction(openFileAction);

    // save file action
    Action* saveFileAction = new Action();
    saveFileAction->name = ActionName::SaveFile;
    saveFileAction->statusTip = "Save the file";
    saveFileAction->shortcut = QKeySequence::Save;
    saveFileAction->slot = []() {
        qDebug() << "Save file";
    };
    addToolbarAction(saveFileAction);

    // save as file action
    Action* saveAsFileAction = new Action();
    saveAsFileAction->name = ActionName::SaveAsFile;
    saveAsFileAction->statusTip = "Save the file as";
    saveAsFileAction->shortcut = QKeySequence::SaveAs;
    saveAsFileAction->slot = []() {
        qDebug() << "Save as file";
    };
    addToolbarAction(saveAsFileAction);
}

void ToolBar::initViewActions() {
    // view text
    Action* viewTextAction = new Action();
    viewTextAction->name = ActionName::ViewTextFile;
    viewTextAction->statusTip = "View the text file";
    viewTextAction->shortcut = QKeySequence("Ctrl+Shift+T");
    viewTextAction->slot = []() {
        qDebug() << "View text";
    };
    addToolbarAction(viewTextAction, true, true);

    // view tokens
    Action* viewTokensAction = new Action();
    viewTokensAction->name = ActionName::ViewTokens;
    viewTokensAction->statusTip = "View the tokens file";
    viewTokensAction->shortcut = QKeySequence("Ctrl+Shift+K");
    viewTokensAction->slot = []() {
        qDebug() << "View tokens";
    };
    addToolbarAction(viewTokensAction, true, false);

    addSeparator();

    // view parse tree
    Action* viewParseTreeAction = new Action();
    viewParseTreeAction->name = ActionName::ViewParseTree;
    viewParseTreeAction->statusTip = "View the parse tree";
    viewParseTreeAction->shortcut = QKeySequence("Ctrl+Shift+P");
    viewParseTreeAction->slot = []() {
        qDebug() << "View parse tree";
    };
    addToolbarAction(viewParseTreeAction, true, false);

    // view syntax tree
    Action* viewSyntaxTreeAction = new Action();
    viewSyntaxTreeAction->name = ActionName::ViewSyntaxTree;
    viewSyntaxTreeAction->statusTip = "View the syntax tree";
    viewSyntaxTreeAction->shortcut = QKeySequence("Ctrl+Shift+O");
    viewSyntaxTreeAction->slot = []() {
        qDebug() << "View syntax tree";
    };
    addToolbarAction(viewSyntaxTreeAction, true, true);
}

void ToolBar::initHelpActions() {
    // help action
    Action* helpAction = new Action();
    helpAction->name = ActionName::Help;
    helpAction->statusTip = "Get help";
    helpAction->shortcut = QKeySequence::HelpContents;
    helpAction->slot = []() {
        qDebug() << "Help";
    };
    addToolbarAction(helpAction);

    // about action
    Action* aboutAction = new Action();
    aboutAction->name = ActionName::About;
    aboutAction->statusTip = "About the application";
    aboutAction->shortcut = QKeySequence::WhatsThis;
    aboutAction->slot = []() {
        qDebug() << "About";
    };
    addToolbarAction(aboutAction);
}

void ToolBar::addToolbarAction(Action* action, bool onOffAction, bool onByDefault) {
    QString actionName = actionNameToString[action->name];
    // load icon, it has the same name as the action
    QIcon icon(QString(":/resources/%1.png").arg(actionName));
    // check if the icon is valid
    if (icon.isNull()) {
        qCritical() << "Icon is null";
    }

    // create the action
    QAction* newAction = new QAction(icon, actionName, this);
    // set the shortcut if it is not empty
    if (!action->shortcut.isEmpty()) {
        newAction->setShortcut(action->shortcut);

        // change the tooltip to include the shortcut
        QString tooltip = actionName;
        tooltip.append(" (");
        tooltip.append(action->shortcut.toString());
        tooltip.append(")");
        newAction->setToolTip(tooltip);
    }

    // set the status tip if it is not empty
    if (!action->statusTip.isEmpty()) {
        newAction->setStatusTip(action->statusTip);
    }

    if (onOffAction) {
        newAction->setCheckable(true);
        newAction->setChecked(onByDefault);
    }

    // connect the action to the slot
    connect(newAction, &QAction::triggered, this, action->slot);

    // add the action to the toolbar
    this->addAction(newAction);

    // add the action to the actions map
    this->actions.append(newAction);
}

void ToolBar::initStyle() {
    // set the style of the toolbar
    QString style =
        "QToolBar {"
        "background-color: #1e1e1e;"
        "border: 1px solid #c0c0c0;"
        "padding: 5px;"
        "}"
        "QToolBar::separator {"
        "width: 1px;"
        "height: 25px;"
        "background-color: #c0c0c0;"
        "margin: 0 5px;"
        "}"
        "QToolButton {"
        "color: #c0c0c0;"
        "}"
        "QToolButton:hover {"
        "background-color: #2e2e2e;"
        "}"
        "QToolButton:checked {"
        "background-color: #3e3e3e;"
        "}";

    this->setStyleSheet(style);
}

const QMap<ToolBar::ActionName, QString> ToolBar::actionNameToString = {
    {ToolBar::ActionName::NewTextFile, "New Text File"},
    {ToolBar::ActionName::NewTokensFile, "New Tokens File"},
    {ToolBar::ActionName::OpenFile, "Open File"},
    {ToolBar::ActionName::SaveFile, "Save File"},
    {ToolBar::ActionName::SaveAsFile, "Save As File"},
    {ToolBar::ActionName::ViewTextFile, "View Text"},
    {ToolBar::ActionName::ViewTokens, "View Tokens"},
    {ToolBar::ActionName::ViewParseTree, "View Parse Tree"},
    {ToolBar::ActionName::ViewSyntaxTree, "View Syntax Tree"},
    {ToolBar::ActionName::Help, "Help"},
    {ToolBar::ActionName::About, "About"}};

}  // namespace Tiny::Widgets
