//
// Created by youssef on 20/04/18.
//

#ifndef PARSER_GENERATOR_FIRST_FOLLOW_GENERATOR_H
#define PARSER_GENERATOR_FIRST_FOLLOW_GENERATOR_H

#include "set"
#include "vector"

using std::set;
using std::vector;

class symbol;

class token;

class production;

class parser_symbol;

class non_terminal;

class first_follow_generator {

public:

    first_follow_generator(vector<symbol *>);

    vector<parser_symbol> get_parser_symbols();

private:
    set<token> get_first(non_terminal *);

    void init();

    bool visited[];

    set<token> get_follow(non_terminal *);

    vector<parser_symbol> parser_syms;
};

#endif //PARSER_GENERATOR_FIRST_FOLLOW_GENERATOR_H
