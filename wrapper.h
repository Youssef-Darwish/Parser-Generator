//
// Created by Lenovo on 4/25/2018.
//

#ifndef PARSER_GENERATOR_WRAPPER_H
#define PARSER_GENERATOR_WRAPPER_H
//
// Created by youssef on 25/04/18.
//


#ifndef PARSER_GENERATOR_FIRST_FOLLOW_WRAPPER_H
#define PARSER_GENERATOR_FIRST_FOLLOW_WRAPPER_H

#include "non_terminal.h"
#include "set"
#include "symbol.h"
#include "map"

using std::set;
using std::vector;
using std::map;


class first_follow_wrapper {

public:

    set<token> *get_first(const symbol *);

    set<token> *get_follow(const symbol *);

    first_follow_wrapper(map<symbol *, set<token> *>,
                         map<symbol *, set<token> *> follow_set_map);

private:

    map<symbol *, set<token> *> first_set_map;
    map<symbol *, set<token> *> follow_set_map;

};

#endif //PARSER_GENERATOR_FIRST_FOLLOW_WRAPPER_H
#endif //PARSER_GENERATOR_WRAPPER_H
