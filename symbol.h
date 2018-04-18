//
// Created by youssef on 17/04/18.
//

#ifndef PARSER_GENERATOR_SYMBOL_H
#define PARSER_GENERATOR_SYMBOL_H

#include "string"

using std::string;

/**
 * class representing general symbol (terminals and non terminals)
 */
class symbol {
    friend class file_parser;
    friend  class grammar_validator;
public:
    /**
     * class equating symbols
     * @return true iff the 2 symbols have the same name
     */
    virtual bool operator==(const symbol &);       // to compare symbols

protected :
    virtual explicit symbol(string) = 0;       // check it
    string symbol_name;
};


#endif //PARSER_GENERATOR_SYMBOL_H
