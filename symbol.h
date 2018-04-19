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
    string get_name(); //
protected :
    symbol(string);       // check it
    string symbol_name;
};


/**
 * class represents token
 */
class token {
public:
    const static token eps;// = token(string("epsilon"));

    /**
     * constructor taking token name
     * @param s token name (ex: "id","num",")")
     */
    token(string s) {
        name = s;
    }

    string name;
};



#endif //PARSER_GENERATOR_SYMBOL_H
