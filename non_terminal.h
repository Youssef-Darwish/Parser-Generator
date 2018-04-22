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

#ifdef debug_mode

    non_terminal(string);

#endif

    void add_production(production);

    vector<production> get_productions();

private:


#ifndef debug_mode

    non_terminal(string);
#endif


    vector<production> production_list;
};

#endif //PARSER_GENERATOR_NON_TERMINAL_H
