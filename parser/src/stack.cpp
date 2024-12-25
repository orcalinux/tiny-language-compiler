#include "stack.hpp"

void Stack::pushSymbol(const std::string &symbol)
{
    stack.push(symbol);
}

void Stack::popSymbol()
{
    if (!stack.empty())
    {
        stack.pop();
    }
}

std::string Stack::topSymbol() const
{
    if (!stack.empty())
    {
        return stack.top();
    }
    return "";
}

bool Stack::isEmpty() const
{
    return stack.empty();
}
