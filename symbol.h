//
// Created by youssef on 17/04/18.
//

#ifndef PARSER_GENERATOR_SYMBOL_H
#define PARSER_GENERATOR_SYMBOL_H

#include "string"

using std::string;

class file_parser;
class grammar_validator;

class symbol {
    friend file_parser;
    friend   grammar_validator;
public:
    virtual bool operator==(const symbol &);       // to compare symbols

protected :
    virtual symbol(string) = 0;       // check it
    string symbol_name;
};


#endif //PARSER_GENERATOR_SYMBOL_H
