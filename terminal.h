//
// Created by Lenovo on 4/19/2018.
//

#ifndef PARSER_GENERATOR_TERMINAL_H
#define PARSER_GENERATOR_TERMINAL_H
#include "symbol.h"

class terminal : symbol {
public:
#ifdef debug_mode

    terminal(token t);

#endif

    const static terminal epsilon; /// TODO define it in file parser;
private:

#ifndef debug_mode

    terminal(token t);

#endif

    token terminal_name = token::eps;

};

#endif //PARSER_GENERATOR_TERMINAL_H
