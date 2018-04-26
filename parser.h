#ifndef PARSER_GENERATOR_PARSER_H
#define PARSER_GENERATOR_PARSER_H

#include <stack>
#include <iostream>
#include "predictive_table.h"

using std::stack;
using std::cout;
class terminal;
class non_terminal;
class parser {
public:
    parser(predictive_table *table/*, Analyzer *lexical_analyzer*/);

    void parse();

    void process(const terminal *top);

    void process(const non_terminal *top);

private:
    token cur_token = token(0); // cur_token must be initialized
    stack<const symbol *> parser_stack;
    predictive_table *table;
    // Analyzer *lexical_analyzer;
};


#endif
