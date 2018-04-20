//
// Created by youssef on 17/04/18.
//

#ifndef PARSER_GENERATOR_NON_TERMINAL_H
#define PARSER_GENERATOR_NON_TERMINAL_H

#include "vector"
#include "string"
#include "symbol.h"
using std::vector;
using std::string;

class production;



class non_terminal : public symbol {

public:
    non_terminal(string);
    void add_production(production);
    vector<production> get_productions();
#ifdef debug_mode

#endif

private:
#ifndef debug_mode

    vector<production> production_list;
#endif
};

#endif //PARSER_GENERATOR_NON_TERMINAL_H
