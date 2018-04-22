//
// Created by youssef on 20/04/18.
//

#ifndef PARSER_GENERATOR_FIRST_FOLLOW_GENERATOR_H
#define PARSER_GENERATOR_FIRST_FOLLOW_GENERATOR_H

#include "set"
#include "vector"
#include "map"

using std::set;
using std::vector;
using std::map;

class symbol;

class token;

class production;

class parser_symbol;

class non_terminal;

class first_follow_generator {

public:
#ifdef debug_mode
    map<non_terminal *, set<token> *> first_set_map;
    map<non_terminal *, set<token> *> follow_set_map;

#endif

    first_follow_generator(vector<non_terminal *>);

    vector<parser_symbol> get_parser_symbols();

    void start_first_calculations();

    void start_follow_calculations();


private:

#ifndef debug_mode
    map<non_terminal *, set<token> *> first_set_map;
    map<non_terminal *, set<token> *> follow_set_map;
#endif

    set<token> get_first(non_terminal *);
    void init();
    bool *visited;
    set<token> get_follow(non_terminal *);
    int function_calls=0;
    vector<non_terminal *> non_terminals_received;
    vector<parser_symbol> parser_syms;
};

#endif //PARSER_GENERATOR_FIRST_FOLLOW_GENERATOR_H
