#ifndef TABCONTENT_H
#define TABCONTENT_H

#include <QWidget>
#include <QObject>
#include <QHBoxLayout>
#include <QFrame>
#include <QSplitter>
#include <QDebug>
#include <QVector>
#include <QTimer>


#include "TextEditor.h"
#include "TreeVisualiser.h"
#include "Scanner.h"
#include "Parser.h"
#include "TokenStreamBuilder.h"
#include "Node.h"
#include "Token.h"

namespace Tiny::Widgets {

using Tiny::Scanner::Scanner;
using Tiny::Scanner::TokenStreamBuilder;
using Tiny::Parser::Parser;
using Tiny::Data::Token;
using Tiny::Data::Node;

class TabContent : public QWidget{
    Q_OBJECT

public:
    explicit TabContent(bool tokenTextOnly = false, bool newFile = true, QWidget* parent = nullptr);
    ~TabContent();



    bool getIsTokenOnly() const;
    bool getIsTokenShowed() const;

public slots:
    void showTokens();
    void showText();

    void saveFile();
    void saveAsFile();

    void textChanged();

private:
    bool isTokenOnly;
    bool isNewFile;
    bool isSaved;
    bool isTokenShowed;

    bool skipNextTextChange;

    QString filePath;

    QString tokenText;
    QString text;

    QVector<Token> tokensList;

    TextEditor* textEditor;
    TreeVisualiser* treeVisualiser;

    Scanner* scanner;
    Parser* parser;
    TokenStreamBuilder* tokenStreamBuilder;

    void initStyle();
    void initConfig();

    bool processUnknownTokens();
    void processReservedTokens();
};

} // namespace Tiny::Widgets

#endif // TABCONTENT_H
