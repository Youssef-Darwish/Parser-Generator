//
// Created by youssef on 17/04/18.
//

#ifndef PARSER_GENERATOR_NON_TERMINAL_H
#define PARSER_GENERATOR_NON_TERMINAL_H

#include <vector>
#include <string>
#include "symbol.h"
#include <iostream>

using std::vector;
using std::string;
using std::ostream;

class production;


class non_terminal : public symbol {

public:
    void add_production(production);

    vector<production> get_productions() const ;

    friend ostream &operator<<(ostream &os, non_terminal &p);

    void accept( parser *) const override;

protected:
    friend class file_parser;

    friend class grammar_validator;

    non_terminal(string);

    vector<production> production_list;
};

#endif //PARSER_GENERATOR_NON_TERMINAL_H
