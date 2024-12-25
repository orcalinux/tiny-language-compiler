#include "TabContent.h"
#include <QFileDialog>
#include <QMessageBox>

using Tiny::Widgets::TabContent;
using Tiny::Widgets::TextEditor;
using Tiny::Widgets::TreeVisualiser;
using Tiny::Scanner::Scanner;
using Tiny::Parser::Parser;
using Tiny::Scanner::TokenStreamBuilder;


TabContent::TabContent(bool tokenTextOnly, bool newFile, QWidget *parent) :
    QWidget(parent),
    isTokenOnly(tokenTextOnly),
    isNewFile(newFile),
    isSaved(newFile ? false : true),
    isTokenShowed(false),
    filePath(""),
    text(""),
    tokenText(""),
    skipNextTextChange(false)
{
    initStyle();
    initConfig();

    this->parseErrors = QVector<QPair<Tiny::Data::Token, QString>>();

    // if not a new file, load the file
    if (!newFile) {
        // open the file
        filePath = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath(), "All Files (*);;Tiny files (*.txt)");
        // read the file
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            if(filePath == ""){
                QMessageBox::critical(this, "Error", "No file selected");
                throw std::runtime_error ("No file selected");
            }

            if (file.error() == QFile::OpenError) {
                // show an error message
                QMessageBox::critical(this, "Error", "Could not open the file");
                throw std::runtime_error ("Could not open the file");
            }
        }

        // read the file
        QTextStream in(&file);
        text = in.readAll();
        file.close();

        // opan a dialog to choose the mode of the opened file, token only or with text code
        QMessageBox msgBox;
        msgBox.setText("Choose the mode of the file");
        // give a peek of the file content, the first 3 lines
        QStringList lines = text.split("\n");
        QString peek = "";
        int linesCount = lines.size();
        if (linesCount > 3) {
            linesCount = 3;
        }
        for (int i = 0; i < linesCount; i++) {
            peek += lines[i] + "\n";
        }

        // set the text of the message box
        msgBox.setDetailedText(peek);

        msgBox.setInformativeText("Do you want to open the file in token-only mode?\n yes: for token list files\n no: for text code files");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();

        // set the token only mode
        if (ret == QMessageBox::Yes) {
            isTokenOnly = true;
            tokenTextOnly = true;
            this->tokenText = text;
            this->textEditor->setText(tokenText);
        } else {
            isTokenOnly = false;
            tokenTextOnly = false;
            this->text = text;
            this->textEditor->setText(text);
        }
    }

    // if tokenTextOnly is true, show the tokens
    if (tokenTextOnly) {
        // show the tokens
        // TODO
        this->isTokenShowed = true;
    }

    // connect the text changed signal
    connect(textEditor, &TextEditor::textChanged, this, &TabContent::textChanged);

    // init the scanner
    scanner = new Scanner(text, this);
    tokenStreamBuilder = new TokenStreamBuilder(*scanner, this);


    // init the parser
    parser = new Parser(this);
    parser->setTokens(tokensList);


    connect(parser, &Parser::error, this, [this](Tiny::Data::Token token, QString message) {
        // show the error
        // TODO
        qDebug() << message;
        // append the error
        this->parseErrors.append({token, message});

    });

    this->textChanged();
}

TabContent::~TabContent()
{
}

void TabContent::showTokens()
{
    // check if the tokens are already showed
    if (isTokenShowed) {
        return;
    }

    // show the tokens

    // set text editor to read only
    textEditor->setReadOnly(true);

    // skip the next text change
    skipNextTextChange = true;

    // set the text
    textEditor->setText(tokenText);

    // set the token showed to true
    isTokenShowed = true;
}

void TabContent::showText()
{
    // chack if it accepts token only
    if (isTokenOnly){
        return;
    }

    // check if the text is already showed
    if (!isTokenShowed) {
        return;
    }

    // skip the next text change
    skipNextTextChange = true;

    // unset the text editor read only
    textEditor->setReadOnly(false);

    // reset the format
    textEditor->resetFormat();

    // set the text
    textEditor->setText(text);

    this->textChanged();

    // set the token showed to false
    isTokenShowed = false;
}

bool TabContent::saveFile()
{
    // if it is a new file, ask for the file path
    if (isNewFile) {
        filePath = QFileDialog::getSaveFileName(this, "Save file", QDir::homePath(), "Tiny files (*.txt)");
    }

    // save the file
    QFile file(filePath);
    if(filePath == ""){
        QMessageBox::critical(this, "Error", "No file selected");
        return false;
    }
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // show an error message
        QMessageBox::critical(this, "Error", "Could not save the file");
        return false;
    }

    // write the text to the file
    QTextStream out(&file);
    out << textEditor->toPlainText();
    file.close();

    isNewFile = false;

    // set the file as saved
    isSaved = true;

    return true;
}

void TabContent::textChanged()
{
    //hide the error
    treeVisualiser->hideError();

    // set file as not saved
    isSaved = false;

    // Token-only mode
    if (isTokenOnly) {
        if(skipNextTextChange){
            skipNextTextChange = false;
            return;
        }

        bool hasUnknown = false;

        // Get the new tokens from the text editor
        QString tokenText = textEditor->toPlainText();

        // reset the format
        textEditor->resetFormat();

        // Tokens are expected in the format: type, value
        QStringList lines = tokenText.split("\n", Qt::SkipEmptyParts); // Skip empty lines
        tokensList.clear(); // Clear the existing tokens list

        // Loop over each line and process tokens
        int lineCounter = 1;
        for (const QString& line : lines) {
            QStringList tokenParts = line.split(",", Qt::SkipEmptyParts);
            if (tokenParts.size() != 2) {
                qDebug() << "Invalid token format: " << line;
                this->treeVisualiser->setRoot(nullptr); // Clear the tree if no tokens
                this->treeVisualiser->displayError(Tiny::Data::Token(Tiny::Data::Token::TokenType::ASSIGN, QString(), 0 ,0) , "Invalid token format", true);
                return;
            }

            QString value = tokenParts[0].trimmed();
            QString type = tokenParts[1].trimmed();

            Tiny::Data::Token token(Tiny::Data::Token::TokenType::UNKNOWN, value, lineCounter, 0); // Line and column default to 0
            token.setType(type);
            if(token.getType() == Tiny::Data::Token::TokenType::UNKNOWN){
                hasUnknown = true;
            }
            tokensList.append(token);
            lineCounter++;
        }

        hasUnknown = processUnknownTokens();

        // Parse the tokens
        if (tokensList.isEmpty() || hasUnknown) {
            qDebug() << "No tokens or unknown tokens";
            this->treeVisualiser->setRoot(nullptr); // Clear the tree if no tokens
            this->treeVisualiser->displayError(Tiny::Data::Token(Tiny::Data::Token::TokenType::ASSIGN, QString(), 0 ,0) , "No tokens or unknown tokens", true);
            return;
        }

        this->parser->setTokens(tokensList);
        Node* root = nullptr;

        try {
            qDebug() << "Parsing...";
            this->parseErrors.clear(); // Clear any previous parse errors
            root = this->parser->parse();
        } catch (const std::exception& e) {
            qDebug() << "Parser exception: " << e.what();
            this->treeVisualiser->setRoot(nullptr); // Clear the tree if no tokens
        } catch (...) {
            qDebug() << "An unknown exception occurred during parsing.";
            this->treeVisualiser->setRoot(nullptr); // Clear the tree if no tokens
        }

        // Update the tree visualizer        
        if (root != nullptr) {
            qDebug() << "Done parsing with no errors";
            qDebug() << "Drawing tree...";
            this->treeVisualiser->setRoot(root);
            qDebug() << "Done drawing tree";
        } else {
            qDebug() << "Done parsing with errors";
            this->treeVisualiser->setRoot(nullptr);
            // mark the errors
            for (const auto& error : this->parseErrors) {
                textEditor->markParseError(error.first.getLine(), error.first.getColumn(), error.first.getValue().length(), error.second, true);
                this->treeVisualiser->displayError(error.first, error.second, false);
            }
        }
    }
    // text mode
    else {
        if (skipNextTextChange) {
            skipNextTextChange = false;
            return;
        }
        // get the new text
        text = textEditor->toPlainText();
        // reset the format
        textEditor->resetFormat();


        // tokenise the text
        scanner->setInput(text);
        tokenStreamBuilder->build();
        tokensList = tokenStreamBuilder->getTokens();

        // clear the token text
        tokenText = "";

        // Convert tokensList to HTML strings and separate them with line breaks
        for (const auto& token : tokensList) {
            tokenText += token.toHTMLString(true) + "<br>";
        }

        // mark the unknown tokens
        bool hasUnknown = processUnknownTokens();
        processReservedTokens();

        if (hasUnknown) {
            // print that there are unknown tokens
            qDebug() << "Unknown tokens found";
            this->treeVisualiser->setRoot(nullptr);
            this->treeVisualiser->displayError(Tiny::Data::Token(Tiny::Data::Token::TokenType::ASSIGN, QString(), 0 ,0) , "No tokens or unknown tokens", true);
        }

        if(!hasUnknown){
            // parse
            this->parser->setTokens(tokensList);
            Node* root = nullptr;
            try {
                // reset errors list
                this->parseErrors.clear();
                // print that the parser is parsing
                qDebug() << "Parsing...";
                root = this->parser->parse();
            } catch (const std::exception& e) {
                qDebug() << e.what();
                this->treeVisualiser->setRoot(nullptr);
            } catch (...) {
                qDebug() << "An unknown exception occurred";
                this->treeVisualiser->setRoot(nullptr);
            }


            // update the tree visualiser
            if (root != nullptr) {
                // print that the parser is done parsing
                qDebug() << "Done parsing with no errors";
                // print draw tree
                qDebug() << "Drawing tree...";
                this->treeVisualiser->setRoot(root);
                // print done drawing tree
                qDebug() << "Done drawing tree";
            } else {
                // print that the parser is done parsing
                qDebug() << "Done parsing with errors";
                this->treeVisualiser->setRoot(nullptr);
                // mark the errors
                for (const auto& error : this->parseErrors) {
                    textEditor->markParseError(error.first.getLine(), error.first.getColumn(), error.first.getValue().length(), error.second);
                    this->treeVisualiser->displayError(error.first, error.second, false);
                }
            }
        }
    }
}

void TabContent::initStyle()
{
    // create a splitter
    QSplitter* splitter = new QSplitter(this);
    splitter->setOrientation(Qt::Horizontal);
    splitter->setStyleSheet("background-color: #2e2e2e;");
    splitter->setContentsMargins(0, 0, 0, 0);
    splitter->setChildrenCollapsible(true);

    // create the text editor
    textEditor = new TextEditor(this);

    // add the text editor to the splitter
    splitter->addWidget(textEditor);

    // create the tree visualiser
    treeVisualiser = new TreeVisualiser(this);

    // add the tree visualiser to the splitter
    splitter->addWidget(treeVisualiser);

    // add the splitter to the main layout
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(splitter);
    setLayout(layout);

    // set initial sizes for the splitter
    splitter->setSizes({400, 400});

}

void TabContent::initConfig()
{

}

bool TabContent::processUnknownTokens()
{
    bool hasUnknown = false;
    int counter = 1;
    for (const auto& token : tokensList) {
        if (token.getType() == Tiny::Data::Token::TokenType::UNKNOWN) {
            hasUnknown = true;
            if (isTokenOnly) {
                textEditor->markUnknowTokens(counter);
            }
            else{
                textEditor->markUnknowTokens(token.getLine(), token.getColumn(), token.getValue().length());
            }
        }
        counter++;
    }

    return hasUnknown;

}

void TabContent::processReservedTokens()
{
    for (const auto& token : tokensList) {
        if (token.getType() != Tiny::Data::Token::TokenType::IDENTIFIER &&
            token.getType() != Tiny::Data::Token::TokenType::NUMBER &&
            token.getType() != Tiny::Data::Token::TokenType::UNKNOWN) {
            this->textEditor->markReservedToken(token.getLine(), token.getColumn(), token.getValue().length());
        }
    }
}



bool TabContent::getIsTokenOnly() const
{
    return isTokenOnly;
}

bool TabContent::getIsTokenShowed() const
{
    return isTokenShowed;
}

