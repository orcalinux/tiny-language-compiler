// include/ParsingTable.hpp
#ifndef PARSINGTABLE_HPP
#define PARSINGTABLE_HPP

#include "token.hpp"
#include <map>
#include <vector>
#include <string>

// Define a type for productions: a vector of symbols (terminals and non-terminals as strings)
using Production = std::vector<std::string>;

// Parsing table: maps (Non-Terminal, Terminal) to Production
class ParsingTable
{
public:
    ParsingTable();
    Production getProduction(const std::string &nonTerminal, const TokenType &terminal) const;

private:
    std::map<std::pair<std::string, TokenType>, Production> table;
};

#endif // PARSINGTABLE_HPP
