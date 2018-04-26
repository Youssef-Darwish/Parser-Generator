#ifndef PARSER_GENERATOR_PARSER_H
#define PARSER_GENERATOR_PARSER_H

#include <stack>
#include <string>
#include <iostream>
using std::stack;
using std::cout;
using  std::string;
class terminal;
class non_terminal;
class predictive_table;
class token;
class symbol;
class parser {
public:
    parser(predictive_table *table/*, Analyzer *lexical_analyzer*/);

    void parse();

    void process(const terminal *top);

    void process(const non_terminal *top);

private:
    token *cur_token ;// cur_token must be initialized
    stack<const symbol *> parser_stack;
    predictive_table *table;
    // Analyzer *lexical_analyzer;
};


#endif
