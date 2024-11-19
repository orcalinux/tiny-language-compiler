// Token class implementation
#include "token.hpp"

Token::Token(TokenType type, std::string_view value, int line, int column)
    : type(type),
      value(value),
      line(line),
      column(column) {}

TokenType Token::getType() const {
    return this->type;
}

std::string Token::getValue() const {
    return this->value;
}

int Token::getLine() const {
    return this->line;
}

int Token::getColumn() const {
    return this->column;
}

std::string Token::toString(bool includePosition) const {
    std::string result = this->getValue() + ", " + this->getTokenTypeString().data();
    if (includePosition) {
        result += " (Line: " + std::to_string(this->line) + ", Column: " + std::to_string(this->column) + ")";
    }
    return result;
}

std::string_view Token::getTokenTypeString() const {
    size_t index = static_cast<size_t>(this->type);

    if (index >= tokenTypeStrings.size()) {
        throw std::out_of_range("Invalid token type");
    }

    return tokenTypeStrings[index];
}
