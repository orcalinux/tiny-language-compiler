// TextEditor.cpp

#include "TextEditor.h"

using namespace Tiny::Widgets;
TextEditor::TextEditor(QWidget *parent) :
    QTextEdit(parent)
{
    initStyle();
    initConfig();
}

void TextEditor::markUnknowTokens(int line, int column, int charCount)
{
    this->blockSignals(true);

    // Create a QTextCursor to navigate the document
    QTextCursor cursor = this->textCursor();

    // Get the block (line) based on the 1-based line number
    QTextBlock block = this->document()->findBlockByLineNumber(line - 1);
    if (!block.isValid()) {
        qWarning() << "Invalid line number:" << line;
        return;
    }

    // Calculate the position in the block (column is 1-based)
    int position = block.position() + (column - 2);

    // Set the cursor to the starting position
    cursor.setPosition(position);

    // Select the characters to mark by moving the cursor to the end of the selection range (left)
    cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, charCount);

    // Create the format for marking
    QTextCharFormat format;
    format.setForeground(Qt::red); // Text color: Red
    format.setUnderlineStyle(QTextCharFormat::SpellCheckUnderline); // Zigzag underline
    format.setToolTip("Unknown token type");

    // Apply the format to the selected text only
    cursor.setCharFormat(format);

    // Clear the selection to avoid further changes
    cursor.clearSelection();

    this->blockSignals(false); // Re-enable signals after formatting
}

void TextEditor::markReservedToken(int line, int column, int charCount)
{
    this->blockSignals(true);

    // Create a QTextCursor to navigate the document
    QTextCursor cursor = this->textCursor();

    // Get the block (line) based on the 1-based line number
    QTextBlock block = this->document()->findBlockByLineNumber(line - 1);
    if (!block.isValid()) {
        qWarning() << "Invalid line number:" << line;
        return;
    }

    // Calculate the position in the block (column is 1-based)
    int position = block.position() + (column - 1);

    // Set the cursor to the starting position
    cursor.setPosition(position);

    // Select the characters to mark by moving the cursor to the end of the selection range (left)
    cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, charCount);

    // Create the format for marking
    QTextCharFormat format;
    format.setForeground(Qt::green); // Text color: Green

    // Apply the format to the selected text only
    cursor.setCharFormat(format);

    // Clear the selection to avoid further changes
    cursor.clearSelection();

    this->blockSignals(false); // Re-enable signals after formatting
}

void TextEditor::resetFormat()
{
    // block signals to avoid infinite loop
    this->blockSignals(true);

    // reset the format to the default
    QTextCursor cursor = this->textCursor();
    cursor.select(QTextCursor::Document);
    // set the default format
    cursor.setCharFormat(QTextCharFormat());


    cursor.clearSelection();

    // unblock signals
    this->blockSignals(false);
}

void TextEditor::markParseError(int line, int column, int charCount, QString message)
{
    this->blockSignals(true);

    // Create a QTextCursor to navigate the document
    QTextCursor cursor = this->textCursor();

    // Get the block (line) based on the 1-based line number
    QTextBlock block = this->document()->findBlockByLineNumber(line - 1);
    if (!block.isValid()) {
        qWarning() << "Invalid line number:" << line;
        return;
    }

    // Calculate the position in the block (column is 1-based)
    int position = block.position() + (column - 1);

    // Set the cursor to the starting position
    cursor.setPosition(position);

    // Select the characters to mark by moving the cursor to the end of the selection range (left)
    cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, charCount);

    // Create the format for marking
    QTextCharFormat format;
    format.setForeground(QColor("orange") ); // Text color: orange
    format.setUnderlineStyle(QTextCharFormat::SpellCheckUnderline); // Zigzag underline
    format.setToolTip(message);

    // Apply the format to the selected text only
    cursor.setCharFormat(format);

    // Clear the selection to avoid further changes
    cursor.clearSelection();

    this->blockSignals(false); // Re-enable signals after formatting
}

void TextEditor::initStyle()
{
    // set the style
    setStyleSheet("background-color: #2e2e2e; color: #c0c0c0; border: 1px solid #2a2a2a;");
}

void TextEditor::initConfig()
{

}
