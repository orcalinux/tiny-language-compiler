// include/Stack.hpp
#ifndef STACK_HPP
#define STACK_HPP

#include <stack>
#include <string>

class Stack
{
public:
    void pushSymbol(const std::string &symbol);
    void popSymbol();
    std::string topSymbol() const;
    bool isEmpty() const;

private:
    std::stack<std::string> stack;
};

#endif // STACK_HPP
