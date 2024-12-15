#include "TabContent.h"

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

    // if not a new file, load the file
    if (!newFile) {
        // load the file
        // TODO
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

    // get the tokens
    tokenStreamBuilder->build();
    tokensList = tokenStreamBuilder->getTokens();

    // init the parser
    parser = new Parser(this);
    parser->setTokens(tokensList);
    parser->parse();

    connect(parser, &Parser::error, this, [this](QString message) {
        // show the error
        // TODO
        //qDebug() << message;
    });
}

TabContent::~TabContent()
{
    // before delete check if the file is saved
    if (!isSaved) {
        // ask the user to save the file
        // TODO
    }
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

void TabContent::saveFile()
{

}

void TabContent::saveAsFile()
{

}

void TabContent::textChanged()
{
    // skip the next text change
    if (skipNextTextChange) {
        skipNextTextChange = false;
        return;
    }

    // token only mode
    if (isTokenOnly) {
        // get the new tokens
        tokenText = textEditor->toPlainText();
        qDebug() << "Tokens: " << tokenText;

        // parse and update the tree visualiser
        // TODO
    }


    // text mode
    else {
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

        if(!hasUnknown){
            static int counter;
            // parse
            this->parser->setTokens(tokensList);
            Node* root = nullptr;
            try {
                qDebug() << "Parsing..." + QString::number(counter++);
                root = this->parser->parse();
            } catch (const std::exception& e) {
                // qDebug() << e.what();
            } catch (...) {
                qDebug() << "An unknown exception occurred";
            }

            // update the tree visualiser
            if (root != nullptr) {
                this->treeVisualiser->setRoot(root);
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
    static QTimer* timer = nullptr; // Static timer to debounce calls
    static QVector<Tiny::Data::Token> unknownTokens; // Store unknown tokens

    // Reset the state
    bool hasUnknown = false;
    unknownTokens.clear();

    // Collect all unknown tokens
    for (const auto& token : tokensList) {
        if (token.getType() == Tiny::Data::Token::TokenType::UNKNOWN) {
            hasUnknown = true;
            unknownTokens.append(token);
        }
    }

    if (!timer) {
        timer = new QTimer(this);
        timer->setSingleShot(true); // Ensure one-shot execution

        connect(timer, &QTimer::timeout, this, [this]() {
            // Process unknown tokens after the timer fires
            for (const auto& token : unknownTokens) {
                textEditor->markUnknowTokens(token.getLine(), token.getColumn(), token.getValue().length());
            }
        });
    }

    if (hasUnknown) {
        timer->start(10); // Start or restart the timer with a 10ms delay
    }

    return hasUnknown;

}

void TabContent::processReservedTokens()
{
    // static QTimer* timer = nullptr; // Static timer to debounce calls
    // static QVector<Tiny::Data::Token> reservedTokens; // Store reserved tokens

    // // mark any reserved tokens (not id or number or unknown)
    // for (const auto& token : tokensList) {
    //     if (token.getType() != Tiny::Data::Token::TokenType::IDENTIFIER &&
    //         token.getType() != Tiny::Data::Token::TokenType::NUMBER &&
    //         token.getType() != Tiny::Data::Token::TokenType::UNKNOWN) {
    //         reservedTokens.append(token);
    //     }
    // }

    // if (!timer) {
    //     timer = new QTimer(this);
    //     timer->setSingleShot(true); // Ensure one-shot execution

    //     connect(timer, &QTimer::timeout, this, [this]() {
    //         // Process reserved tokens after the timer fires
    //         for (const auto& token : reservedTokens) {
    //             textEditor->markReservedToken(token.getLine(), token.getColumn(), token.getValue().length());
    //         }
    //     });
    // }

    // if (!reservedTokens.isEmpty()) {
    //     timer->start(10); // Start or restart the timer with a 10ms delay
    // }

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

