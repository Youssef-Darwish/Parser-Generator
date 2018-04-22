//
// Created by youssef on 17/04/18.
//

#ifndef PARSER_GENERATOR_FILE_PARSER_H
#define PARSER_GENERATOR_FILE_PARSER_H

#include <istream>
#include "terminal.h"
#include <set>
using  std::set;
using std::istream;
class file_parser{
    const terminal terminal::epsilon = terminal(token::eps);
public:
    file_parser(istream &c);
    file_parser(istream &c,const set<token> &token_set);

};

class grammar_validator {

};
#endif //PARSER_GENERATOR_FILE_PARSER_H
