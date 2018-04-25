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
class first_follow_wrapper;
class token;

class production;

class parser_symbol;

class non_terminal;

class first_follow_generator {

public:
#ifdef debug_mode
    map<symbol *, set<token> *> first_set_map;
    map<symbol *, set<token> *> follow_set_map;

#endif

    first_follow_generator(vector<non_terminal *>);

    first_follow_wrapper * get_wrapper();
    void start_first_calculations();

    void start_follow_calculations();

    void print();



private:

#ifndef debug_mode
    map<symbol *, set<token> *> first_set_map;
    map<symbol *, set<token> *> follow_set_map;
#endif

    set<token> get_first(symbol *);
    void init();
    bool *visited;
    void  add_in_follow(non_terminal *, set<token > *);
    int function_calls=0;
    vector<non_terminal *> non_terminals_received;
    vector<parser_symbol> parser_syms;
    set<non_terminal *> visited_symbols;
    bool is_terminal(symbol *);
};

#endif //PARSER_GENERATOR_FIRST_FOLLOW_GENERATOR_H
