// TokenStreamBuilder.h

#ifndef TOKEN_STREAM_BUILDER_H
#define TOKEN_STREAM_BUILDER_H

#include <QObject>
#include <QVector>
#include <QString>

#include "Scanner.h"
#include "Token.h"

namespace Tiny::Scanner {

/**
 * @class TokenStreamBuilder
 * @brief Manages the scanning process for TINY language source code.
 *
 * The `TokenStreamBuilder` class orchestrates the tokenization process. It uses the `Scanner`
 * class to generate tokens and appends them to a vector of tokens for further processing.
 *
 * @example
 * Scanner scanner(inputCode);
 * TokenStreamBuilder builder(scanner);
 * builder.build();
 * for (const auto &token : builder.getTokens()) {
 *     qDebug() << token.lexeme;
 * }
 */
class TokenStreamBuilder : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructs a TokenStreamBuilder object with the given Scanner object.
     *
     * This constructor initializes the `TokenStreamBuilder` with a reference to a `Scanner` object,
     * which is used to generate tokens from the input source code.
     *
     * @param scanner The `Scanner` object to be used for tokenization.
     *
     * @note The `TokenStreamBuilder` does not take ownership of the `Scanner` object.
     *       The `Scanner` object must be properly initialized before constructing the `TokenStreamBuilder`.
     *
     * @see Scanner
     */
    TokenStreamBuilder(Scanner &scanner, QObject *parent = nullptr);

    /**
     * @brief Tokenizes the input source code and stores the tokens in a vector.
     *
     * This method processes the input source code using the `Scanner` object to generate tokens.
     * It appends the generated tokens to an internal vector for further use.
     */
    void build();

    /**
     * @brief Retrieves the vector of tokens generated from the input source code.
     *
     * This method provides access to the vector of tokens generated by the `Scanner`.
     *
     * @return A constant reference to the vector of tokens.
     */
    const QVector<Data::Token> &getTokens() const;

private:
    Scanner &scanner;            /**< The `Scanner` object used for tokenization. */
    QVector<Data::Token> tokens; /**< A vector storing the tokens generated from the input source code. */
};
}  // namespace Tiny::Scanner

#endif  // TOKEN_STREAM_BUILDER_H