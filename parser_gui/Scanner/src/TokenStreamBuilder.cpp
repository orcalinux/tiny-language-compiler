#include <TokenStreamBuilder.h>

namespace Tiny::Scanner {

TokenStreamBuilder::TokenStreamBuilder(Scanner &scanner, QObject *parent)
    : scanner(scanner), QObject(parent) {}

void TokenStreamBuilder::build()
{
    tokens.clear(); // Clear any existing tokens in the vector
    while (scanner.hasMoreTokens())
    {
        tokens.push_back(scanner.getNextToken()); // Append the next token to the vector
    }
}

const QVector<Data::Token> &TokenStreamBuilder::getTokens() const
{
    return tokens; // Provide read-only access to the tokens
}

}  // namespace Tiny::Scanner
