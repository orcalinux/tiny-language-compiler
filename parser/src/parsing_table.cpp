#include "parsing_table.hpp"
#include <utility>

// Initialize the parsing table in the constructor
ParsingTable::ParsingTable()
{
    // program → stmt-sequence
    table[{"program", TokenType::IF}] = {"stmt-sequence"};
    table[{"program", TokenType::REPEAT}] = {"stmt-sequence"};
    table[{"program", TokenType::READ}] = {"stmt-sequence"};
    table[{"program", TokenType::WRITE}] = {"stmt-sequence"};
    table[{"program", TokenType::IDENTIFIER}] = {"stmt-sequence"};

    // stmt-sequence  statement stmt-sequence'
    table[{"stmt-sequence", TokenType::IF}] = {"statement", "stmt-sequence'"};
    table[{"stmt-sequence", TokenType::REPEAT}] = {"statement", "stmt-sequence'"};
    table[{"stmt-sequence", TokenType::READ}] = {"statement", "stmt-sequence'"};
    table[{"stmt-sequence", TokenType::WRITE}] = {"statement", "stmt-sequence'"};
    table[{"stmt-sequence", TokenType::IDENTIFIER}] = {"statement", "stmt-sequence'"};

    // stmt-sequence' → ; statement stmt-sequence' | ε
    table[{"stmt-sequence'", TokenType::SEMICOLON}] = {";", "statement", "stmt-sequence'"};
    // FOLLOW(stmt-sequence') includes END, ELSE, UNTIL, RPAREN, END_OF_INPUT
    table[{"stmt-sequence'", TokenType::END}] = {};          // ε
    table[{"stmt-sequence'", TokenType::ELSE}] = {};         // ε
    table[{"stmt-sequence'", TokenType::UNTIL}] = {};        // ε
    table[{"stmt-sequence'", TokenType::RPAREN}] = {};       // ε
    table[{"stmt-sequence'", TokenType::END_OF_INPUT}] = {}; // ε

    // statement → if-stmt | repeat-stmt | assign-stmt | read-stmt | write-stmt
    table[{"statement", TokenType::IF}] = {"if-stmt"};
    table[{"statement", TokenType::REPEAT}] = {"repeat-stmt"};
    table[{"statement", TokenType::READ}] = {"read-stmt"};
    table[{"statement", TokenType::WRITE}] = {"write-stmt"};
    table[{"statement", TokenType::IDENTIFIER}] = {"assign-stmt"};

    // if-stmt → if exp then stmt-sequence end | if exp then stmt-sequence else stmt-sequence end
    // Handled uniformly
    table[{"if-stmt", TokenType::IF}] = {"if", "exp", "then", "stmt-sequence", "end"};

    // repeat-stmt → repeat stmt-sequence until exp
    table[{"repeat-stmt", TokenType::REPEAT}] = {"repeat", "stmt-sequence", "until", "exp"};

    // assign-stmt → identifier := exp
    table[{"assign-stmt", TokenType::IDENTIFIER}] = {"identifier", ":=", "exp"};

    // read-stmt → read identifier
    table[{"read-stmt", TokenType::READ}] = {"read", "identifier"};

    // write-stmt → write exp
    table[{"write-stmt", TokenType::WRITE}] = {"write", "exp"};

    // exp → simple-exp exp'
    table[{"exp", TokenType::IF}] = {"simple-exp", "exp'"};
    table[{"exp", TokenType::REPEAT}] = {"simple-exp", "exp'"};
    table[{"exp", TokenType::READ}] = {"simple-exp", "exp'"};
    table[{"exp", TokenType::WRITE}] = {"simple-exp", "exp'"};
    table[{"exp", TokenType::IDENTIFIER}] = {"simple-exp", "exp'"};
    table[{"exp", TokenType::NUMBER}] = {"simple-exp", "exp'"};
    table[{"exp", TokenType::LPAREN}] = {"simple-exp", "exp'"};

    // exp' → comparison-op simple-exp | ε
    table[{"exp'", TokenType::LT}] = {"comparison-op", "simple-exp"};
    table[{"exp'", TokenType::EQ}] = {"comparison-op", "simple-exp"};
    // FOLLOW(exp') includes THEN, SEMICOLON, ELSE, UNTIL, RPAREN, END_OF_INPUT
    table[{"exp'", TokenType::THEN}] = {};         // ε
    table[{"exp'", TokenType::SEMICOLON}] = {};    // ε
    table[{"exp'", TokenType::ELSE}] = {};         // ε
    table[{"exp'", TokenType::UNTIL}] = {};        // ε
    table[{"exp'", TokenType::RPAREN}] = {};       // ε
    table[{"exp'", TokenType::END_OF_INPUT}] = {}; // ε

    // comparison-op → < | =
    table[{"comparison-op", TokenType::LT}] = {"<"};
    table[{"comparison-op", TokenType::EQ}] = {"="};

    // simple-exp → term simple-exp'
    table[{"simple-exp", TokenType::IDENTIFIER}] = {"term", "simple-exp'"};
    table[{"simple-exp", TokenType::NUMBER}] = {"term", "simple-exp'"};
    table[{"simple-exp", TokenType::LPAREN}] = {"term", "simple-exp'"};

    // simple-exp' → addop term simple-exp' | ε
    table[{"simple-exp'", TokenType::PLUS}] = {"+", "term", "simple-exp'"};
    table[{"simple-exp'", TokenType::MINUS}] = {"-", "term", "simple-exp'"};
    // ε production
    table[{"simple-exp'", TokenType::SEMICOLON}] = {};    // ε
    table[{"simple-exp'", TokenType::END}] = {};          // ε
    table[{"simple-exp'", TokenType::ELSE}] = {};         // ε
    table[{"simple-exp'", TokenType::UNTIL}] = {};        // ε
    table[{"simple-exp'", TokenType::RPAREN}] = {};       // ε
    table[{"simple-exp'", TokenType::END_OF_INPUT}] = {}; // ε

    // addop → + | -
    table[{"addop", TokenType::PLUS}] = {"+"};
    table[{"addop", TokenType::MINUS}] = {"-"};

    // term → factor term'
    table[{"term", TokenType::IDENTIFIER}] = {"factor", "term'"};
    table[{"term", TokenType::NUMBER}] = {"factor", "term'"};
    table[{"term", TokenType::LPAREN}] = {"factor", "term'"};

    // term' → mulop factor term' | ε
    table[{"term'", TokenType::TIMES}] = {"*", "factor", "term'"};
    table[{"term'", TokenType::DIVIDE}] = {"/", "factor", "term'"};
    // ε production
    table[{"term'", TokenType::PLUS}] = {};         // ε
    table[{"term'", TokenType::MINUS}] = {};        // ε
    table[{"term'", TokenType::SEMICOLON}] = {};    // ε
    table[{"term'", TokenType::END}] = {};          // ε
    table[{"term'", TokenType::ELSE}] = {};         // ε
    table[{"term'", TokenType::UNTIL}] = {};        // ε
    table[{"term'", TokenType::RPAREN}] = {};       // ε
    table[{"term'", TokenType::END_OF_INPUT}] = {}; // ε
    // No need to add 'LT' and 'EQ' here as 'exp'' handles comparison operators

    // mulop → * | /
    table[{"mulop", TokenType::TIMES}] = {"*"};
    table[{"mulop", TokenType::DIVIDE}] = {"/"};

    // factor → ( exp ) | number | identifier
    table[{"factor", TokenType::LPAREN}] = {"(", "exp", ")"};
    table[{"factor", TokenType::NUMBER}] = {"number"};
    table[{"factor", TokenType::IDENTIFIER}] = {"identifier"};

    // Handle ε productions for non-terminals with ε
    // Note: ε productions are already handled by providing empty productions above
}

Production ParsingTable::getProduction(const std::string &nonTerminal, const TokenType &terminal) const
{
    auto it = table.find({nonTerminal, terminal});
    if (it != table.end())
    {
        return it->second;
    }
    // Handle ε productions or errors
    return {}; // Empty vector indicates ε or error
}
