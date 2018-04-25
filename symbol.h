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
#ifdef debug_mode
    string symbol_name;
#endif

    /**
     * class equating symbols
     * @return true iff the 2 symbols have the same name
     */
    virtual bool operator==(const symbol &);       // to compare symbols
    string get_name();



protected :
#ifndef debug_mode
    string symbol_name;
#endif
    symbol(string);       // check it
};

/**
 * class represents token
 */
class token {
public:
    //const static token eps;// = token(string("epsilon"));

    /**
     * constructor taking token name
     * @param s token name (ex: "id","num",")")
     */
    token(string s) {
        name = s;
    }

    bool operator < (const token &) const;
    bool operator == (const token &) const;
    string name;
};


const static token eps("epsilon");

#endif //PARSER_GENERATOR_SYMBOL_H
