#include "ToolBar.h"

#include <QMessageBox>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QDialog>

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

void ToolBar::setActionChecked(ActionName name, bool checked)
{
    for (auto action : actions) {
        if (actionNameToString[name] == action->text()) {
            action->setChecked(checked);
            return;
        }
    }
}

void ToolBar::setActionEnabled(ActionName name, bool enabled)
{
    for (auto action : actions) {
        if (actionNameToString[name] == action->text()) {
            action->setEnabled(enabled);
            return;
        }
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
    openFileAction->slot = [this]() {
        qDebug() << "Open file";
        emit openFile();
    };
    addToolbarAction(openFileAction);

    // save file action
    Action* saveFileAction = new Action();
    saveFileAction->name = ActionName::SaveFile;
    saveFileAction->statusTip = "Save the file";
    saveFileAction->shortcut = QKeySequence::Save;
    saveFileAction->slot = [this]() {
        qDebug() << "Save file";
        emit saveFile();
    };
    addToolbarAction(saveFileAction);
}

void ToolBar::initViewActions() {
    QActionGroup* viewGroup = new QActionGroup(this);
    viewGroup->setExclusive(true);

    // view text
    Action* viewTextAction = new Action();
    viewTextAction->name = ActionName::ViewTextFile;
    viewTextAction->statusTip = "View the text file";
    viewTextAction->shortcut = QKeySequence("Ctrl+Shift+T");
    viewTextAction->slot = [this]() {
        qDebug() << "View text";
        emit showText();
    };
    QAction* textAction = addToolbarAction(viewTextAction, true, true);
    viewGroup->addAction(textAction);

    // view tokens
    Action* viewTokensAction = new Action();
    viewTokensAction->name = ActionName::ViewTokens;
    viewTokensAction->statusTip = "View the tokens file";
    viewTokensAction->shortcut = QKeySequence("Ctrl+Shift+K");
    viewTokensAction->slot = [this]() {
        qDebug() << "View tokens";
        emit showTokens();
    };
    QAction* tokensAction =  addToolbarAction(viewTokensAction, true, false);
    viewGroup->addAction(tokensAction);

    addSeparator();
}

void ToolBar::initHelpActions() {
    // about action
    Action* aboutAction = new Action();
    aboutAction->name = ActionName::About;
    aboutAction->statusTip = "About the application";
    aboutAction->shortcut = QKeySequence::WhatsThis;
    aboutAction->slot = [this]() {
        // Create a dialog
        QDialog *dialog = new QDialog(this);
        dialog->setWindowTitle("Team Info");
        dialog->resize(500, 300); // Adjust size as needed

        // Create a table widget
        QTableWidget *table = new QTableWidget(dialog);
        table->setColumnCount(2);
        table->setRowCount(6); // Number of team members
        table->setHorizontalHeaderLabels(QStringList() << "Team Member" << "ID");
        table->horizontalHeader()->setStretchLastSection(true);
        table->setEditTriggers(QAbstractItemView::NoEditTriggers); // Make table read-only
        table->setSelectionBehavior(QAbstractItemView::SelectRows);
        table->setSelectionMode(QAbstractItemView::SingleSelection);

        // Populate the table with team data
        struct TeamMember {
            QString name;
            QString id;
        };

        QVector<TeamMember> members = {
            {"Adham Khaled Abdelmaqsoud", "2000066"},
            {"Ahmed Khaled Abdelmaksod Ebrahim", "2000218"},
            {"Ahmed Mohammed Bakr Ahmed", "2000037"},
            {"Eslam Mohamed Marzouk", "2000252"},
            {"Karim Ibrahim Saad Abd-Elrazek", "2001118"},
            {"Mahmoud Abdelraouf Mahmoud", "2001436"}
        };

        for(int row = 0; row < members.size(); ++row) {
            QTableWidgetItem *nameItem = new QTableWidgetItem(members[row].name);
            QTableWidgetItem *idItem = new QTableWidgetItem(members[row].id);
            table->setItem(row, 0, nameItem);
            table->setItem(row, 1, idItem);
        }

        // Adjust column widths
        table->resizeColumnsToContents();
        table->horizontalHeader()->setStretchLastSection(true);

        // Layout setup
        QVBoxLayout *layout = new QVBoxLayout(dialog);
        layout->addWidget(table);
        dialog->setLayout(layout);

        // Show the dialog modally
        dialog->exec();

        // Clean up
        delete dialog;

    };
    addToolbarAction(aboutAction);
}

QAction* ToolBar::addToolbarAction(Action* action, bool onOffAction, bool onByDefault) {
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

    return newAction;
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
