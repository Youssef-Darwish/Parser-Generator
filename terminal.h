//
// Created by Lenovo on 4/19/2018.
//

#ifndef PARSER_GENERATOR_TERMINAL_H
#define PARSER_GENERATOR_TERMINAL_H
#include "symbol.h"

class terminal : symbol {
public:
    const static terminal epsilon; /// TODO define it in file parser;
private:

    token terminal_name = token::eps;

    terminal(token t);
};

#endif //PARSER_GENERATOR_TERMINAL_H
