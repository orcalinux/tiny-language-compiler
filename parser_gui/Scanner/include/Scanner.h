/**
 * @file Scanner.h
 * @brief Defines the Scanner class for tokenizing TINY language source code.
 *
 * The Scanner is responsible for reading the source code, identifying tokens,
 * and handling special cases such as invalid characters.
 */

#ifndef SCANNER_H
#define SCANNER_H

#include <QObject>
#include <QString>
#include <QStack>
#include <QChar>

#include <stdexcept>

#include "Token.h"

namespace Tiny::Scanner {

/**
 * @class Scanner
 * @brief Performs lexical analysis on TINY language source code.
 *
 * The `Scanner` processes input source code to produce a sequence of tokens.
 * It identifies keywords, operators, delimiters, and literals, and it reports
 * invalid characters as necessary.
 */
class Scanner : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructs a `Scanner` object with the given input string.
     *
     * This constructor initializes the `Scanner` with the source code that
     * needs to be tokenized.
     *
     * @param input The source code to be tokenized.
     */
    Scanner(const QString &input, QObject *parent = nullptr);

    /**
     * @brief Extracts the next token from the input source code.
     *
     * This method processes the source code and returns the next token
     * identified by the `Scanner`.
     *
     * @return The next token.
     */
    Tiny::Data::Token getNextToken();

    /**
     * @brief Checks if there are more tokens to be extracted.
     *
     * This method determines if the end of the source code has been reached.
     *
     * @return True if there are more tokens, false otherwise.
     */
    bool hasMoreTokens();

private:
    QString input;     /**< The source code to be tokenized. */
    size_t pos = 0;    /**< Current position in the input string. */
    int line = 1;      /**< Current line number in the source code. */
    int column = 1;    /**< Current column number in the source code. */

    /**
     * @brief Peeks at the next character in the input without advancing the position.
     *
     * This method allows inspecting the next character in the source code
     * without consuming it.
     *
     * @return The next character in the input, or '\0' if end of input.
     */
    QChar peek() const;

    /**
     * @brief Gets the next character in the input and advances the position.
     *
     * This method reads the next character from the source code and moves
     * the cursor forward.
     *
     * @return The next character in the input, or '\0' if end of input.
     */
    QChar get();

    /**
     * @brief Skips over whitespace characters in the input.
     *
     * This method advances the cursor past any whitespace characters
     * encountered in the source code.
     */
    void skipWhitespace();

    /**
     * @brief Skips over nested comments in the input source code.
     *
     * This method checks if the current position is at the start of a comment (indicated by a '{' character).
     * If it is, the method skips over all characters until it finds the corresponding closing '}'.
     * It correctly handles **nested comments** by keeping track of the nesting levels.
     * For each opening '{', it increases the nesting level, and for each closing '}', it decreases the nesting level.
     * The comment is considered closed when the nesting level returns to zero.
     * After successfully skipping a comment, it also skips any whitespace characters that follow the comment.
     * If the end of the input is reached before all comments are closed (i.e., nesting level does not return to zero),
     * the method returns `true` to indicate that an unclosed comment was detected.
     *
     * @return True if an unclosed comment was detected, false otherwise.
     */
    bool skipComments();

    /**
     * @brief Skips over whitespace and comments in the input.
     *
     * This method continuously skips whitespace and comments until it reaches
     * a character that is neither whitespace nor part of a comment.
     * If an unclosed comment is detected (i.e., the end of input is reached before a closing '}' is found),
     * the method returns `true` to indicate the error.
     *
     * @return True if an unclosed comment was detected, false otherwise.
     */
    bool skipWhitespaceAndComments();

};

}  // namespace Tiny::Scanner

#endif  // SCANNER_H
