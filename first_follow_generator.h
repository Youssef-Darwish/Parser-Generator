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

class non_terminal;

typedef  const non_terminal parser_symbol;
class first_follow_generator {

public:
#ifdef debug_mode
    map<const symbol *, set<token> *> first_set_map;
    map<const symbol *, set<token> *> follow_set_map;

#endif

    first_follow_generator(vector<const non_terminal *>);

    first_follow_wrapper * get_wrapper();
    void start_first_calculations();

    void start_follow_calculations();

    void print();



private:

#ifndef debug_mode
    map<const symbol *, set<token> *> first_set_map;
    map<const symbol *, set<token> *> follow_set_map;
#endif

   void get_first(const non_terminal *);
    void init();
    bool *visited;
    void  add_in_follow(const non_terminal *, set<token > *);
    int function_calls=0;
    vector<const non_terminal *> non_terminals_received;
    set<const non_terminal *> visited_symbols;
    bool is_terminal(const symbol *);
};

#endif //PARSER_GENERATOR_FIRST_FOLLOW_GENERATOR_H
