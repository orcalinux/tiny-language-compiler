#include "TabWidget.h"

namespace Tiny::Widgets {

TabWidget::TabWidget(QWidget* parent)
    : QTabWidget(parent), defaultTab(nullptr) {
    initStyle();
    initConfig();

    putDefaultTab();

    // set the tab tool tip
    setTabToolTip(0, "New Tab");
    // set the close and move actions
    setTabsClosable(true);
    setMovable(true);

    // connect the tab close signal
    connect(this, &TabWidget::tabCloseRequested, this, &TabWidget::closeTab);

    // connect the current changed signal with a lambda function
    connect(this, &TabWidget::currentChanged, [this](int index) {
        connectCurrentTabSignals();
    });
}

void TabWidget::setToolBar(ToolBar *toolbar)
{
    this->toolbar = toolbar;
    connectCurrentTabSignals();
}

void TabWidget::addTabRequest(bool tokenOnly) {
    // check that the tab is not the default tab
    // get the tab at the current index
    QWidget* currentTab = widget(0);
    if (currentTab == defaultTab) {
        removeTab(0);
        // set close and move actions
        setTabsClosable(true);
        setMovable(true);

        // show the tab bar
        tabBar()->show();
    }

    // create a new tab
    TabContent* newTab = new TabContent(tokenOnly, true, this);

    // add the new tab
    addTab(newTab, (tokenOnly ? "Tokens" : "Text") + QString::number(counter));

    // set the tab tool tip
    setTabToolTip(count() - 1, (tokenOnly ? "Tokens" : "Text") + QString::number(counter));

    counter++;

    connectCurrentTabSignals();

}

void TabWidget::newTextTab() {
    addTabRequest(false);
}

void TabWidget::newTokensTab() {
    addTabRequest(true);
}

void TabWidget::openTextTab() {
    addTabRequest(false);
}

void TabWidget::openTokensTab() {
    addTabRequest(true);
}

void TabWidget::initStyle() {
    // Set the tab widget style
    setStyleSheet(
        "QTabWidget::pane {"
        "    border: 1px solid #C2C7CB;"
        "    border-top-left-radius: 4px;"
        "    border-top-right-radius: 4px;"
        "    margin-top: -1px;"
        "}"
        "QTabWidget::tab-bar {"
        "    alignment: left;"
        "}"
        "QTabBar::tab {"
        "    background-color: #1e1e1e;"
        "    border: 1px solid #C4C4C3;"
        "    border-top-left-radius: 4px;"
        "    border-top-right-radius: 4px;"
        "    min-width: 8ex;"
        "    padding: 2px;"
        "}"
        "QTabBar::tab:selected {"
        "    background-color: #3e3e3e;"
        "    border-color: #9B9B9B;"
        "}"
        "QTabBar::tab:!selected {"
        "    background-color: #1e1e1e;"
        "    border: 1px solid #C4C4C3;"
        "    border-bottom-color: #C2C7CB;"
        "}"
        "QTabBar::tab:!selected:hover {"
        "    background-color: #1e1e1e;"
        "}"
        "QTabBar::tab:selected:hover {"
        "    background-color: #2e2e2e;"
        "}");
}

void TabWidget::initConfig() {
    setTabShape(QTabWidget::Rounded);
    setMovable(true);
    setTabsClosable(true);
    setTabBarAutoHide(false);
    setIconSize(QSize(15, 15));
}

void TabWidget::putDefaultTab() {
    if (count() == 0) {
        if (defaultTab == nullptr) {
            createDefaultTab();
        }

        addTab(defaultTab, "Welcome");
        // remove the close button
        setTabsClosable(false);
        // set the tab tool tip
        setTabToolTip(0, "Welcome");
        setMovable(false);

        // hide the tab bar
        tabBar()->hide();
    }
}

void Tiny::Widgets::TabWidget::defaultTabLayout() {
    QVBoxLayout* layout = new QVBoxLayout();
    defaultTab->setLayout(layout);

    layout->setAlignment(Qt::AlignTop);
    layout->setContentsMargins(15, 15, 15, 15);

    // add a label for the welcome message
    QLabel* welcomeLabel = new QLabel("Welcome to Tiny Editor");
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setStyleSheet("font-size: 30px; color: #c0c0c0;");
    layout->addWidget(welcomeLabel);

    layout->addSpacing(20);

    // add label for text options
    QLabel* textOptionsLabel = new QLabel("Text options");
    textOptionsLabel->setAlignment(Qt::AlignCenter);
    textOptionsLabel->setStyleSheet("font-size: 20px; color: #c0c0c0;");
    layout->addWidget(textOptionsLabel);

    // add 2 buttons in a horizontal layout
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* newTextButton = new QPushButton("New Text File");
    QPushButton* openTextButton = new QPushButton("Open Text File");

    // set the button style
    newTextButton->setStyleSheet("background-color: #2e2e2e; color: #c0c0c0;");
    openTextButton->setStyleSheet("background-color: #2e2e2e; color: #c0c0c0;");

    // buttons actions
    connect(newTextButton, &QPushButton::clicked, this, &TabWidget::newTextTab);
    connect(openTextButton, &QPushButton::clicked, this, &TabWidget::openTextTab);

    // add the buttons to the layout
    buttonLayout->addWidget(newTextButton);
    buttonLayout->addWidget(openTextButton);

    // add the layout to the main layout
    layout->addLayout(buttonLayout);
    layout->addSpacing(20);

    // add label for tokens options
    QLabel* tokensOptionsLabel = new QLabel("Tokens options");
    tokensOptionsLabel->setAlignment(Qt::AlignCenter);
    tokensOptionsLabel->setStyleSheet("font-size: 20px; color: #c0c0c0;");
    layout->addWidget(tokensOptionsLabel);

    // add 2 buttons in a horizontal layout
    QHBoxLayout* tokensButtonLayout = new QHBoxLayout();
    QPushButton* newTokensButton = new QPushButton("New Tokens File");
    QPushButton* openTokensButton = new QPushButton("Open Tokens File");

    // set the button style
    newTokensButton->setStyleSheet("background-color: #2e2e2e; color: #c0c0c0;");
    openTokensButton->setStyleSheet("background-color: #2e2e2e; color: #c0c0c0;");

    // buttons actions
    connect(newTokensButton, &QPushButton::clicked, this, &TabWidget::newTokensTab);
    connect(openTokensButton, &QPushButton::clicked, this, &TabWidget::openTokensTab);

    // add the buttons to the layout
    tokensButtonLayout->addWidget(newTokensButton);
    tokensButtonLayout->addWidget(openTokensButton);

    // add the layout to the main layout
    layout->addLayout(tokensButtonLayout);
    layout->addSpacing(20);
}

void TabWidget::createDefaultTab() {
    defaultTab = new QWidget(this);
    defaultTabLayout();
}

void TabWidget::connectCurrentTabSignals()
{
    // if default tab, return
    QWidget* currentTab = currentWidget();
    if (currentTab == defaultTab) {
        // disconnect the showText and showTokens signals
        disconnect(this->toolbar, &ToolBar::showText, nullptr, nullptr);
        disconnect(this->toolbar, &ToolBar::showTokens, nullptr, nullptr);

        // unchecked the view text and view tokens actions
        this->toolbar->setActionChecked(ToolBar::ActionName::ViewTextFile, false);
        this->toolbar->setActionChecked(ToolBar::ActionName::ViewTokens, false);

        // disable the view text and view tokens actions
        this->toolbar->setActionEnabled(ToolBar::ActionName::ViewTextFile, false);
        this->toolbar->setActionEnabled(ToolBar::ActionName::ViewTokens, false);
        return;
    }

    // enable the view text and view tokens actions
    this->toolbar->setActionEnabled(ToolBar::ActionName::ViewTextFile, true);
    this->toolbar->setActionEnabled(ToolBar::ActionName::ViewTokens, true);

    if (currentTab == nullptr) {
        return;
    }

    // disconnect the showText and showTokens signals
    disconnect(this->toolbar, &ToolBar::showText, nullptr, nullptr);
    disconnect(this->toolbar, &ToolBar::showTokens, nullptr, nullptr);

    // cast the current tab to TabContent
    TabContent* currentContentTab = qobject_cast<TabContent*>(currentTab);

    if (currentContentTab == nullptr) {
        return;
    }

    // connect the showText and showTokens signals to the current tab
    connect(this->toolbar, &ToolBar::showText, currentContentTab, &TabContent::showText);
    connect(this->toolbar, &ToolBar::showTokens, currentContentTab, &TabContent::showTokens);

    // if the current conten tab accept only tokens, hide the showText action
    if(currentContentTab->getIsTokenOnly()){
        this->toolbar->setActionEnabled(ToolBar::ActionName::ViewTextFile, false);
        if (currentContentTab->getIsTokenShowed()){
            this->toolbar->setActionChecked(ToolBar::ActionName::ViewTextFile, false);
            this->toolbar->setActionChecked(ToolBar::ActionName::ViewTokens, true);
        }
    } else {
        this->toolbar->setActionEnabled(ToolBar::ActionName::ViewTextFile, true);
        if (currentContentTab->getIsTokenShowed()){
            this->toolbar->setActionChecked(ToolBar::ActionName::ViewTextFile, false);
            this->toolbar->setActionChecked(ToolBar::ActionName::ViewTokens, true);
        } else {
            this->toolbar->setActionChecked(ToolBar::ActionName::ViewTextFile, true);
            this->toolbar->setActionChecked(ToolBar::ActionName::ViewTokens, false);
        }
    }
}

void TabWidget::closeTab(int index) {
    removeTab(index);
    if (count() == 0) {
        putDefaultTab();
    }
}

}  // namespace Tiny::Widgets
