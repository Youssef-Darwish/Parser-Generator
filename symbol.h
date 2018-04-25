//
// Created by youssef on 17/04/18.
//

#ifndef PARSER_GENERATOR_SYMBOL_H
#define PARSER_GENERATOR_SYMBOL_H

#include <string>
#include "parser.h"

using std::string;

/**
 * class representing general symbol (terminals and non terminals)
 */
class symbol {
private:

public:
    /**
     * class equating symbols
     * @return true iff the 2 symbols have the same name
     */
    virtual bool operator==(const symbol &);       // to compare symbols
    string get_name() const ; //
     friend class file_parser;
    friend  class grammar_validator;

    /* pure virtual function to serve the parser visitor class */
    virtual void accept( parser *) const= 0;


protected :

    symbol(string);       // check it
    string symbol_name;
};


/**
 * class represents token
 */
class token {
public:
    bool operator < (const token &) const;
    bool operator ==(const token &) const ;
    /**
     * constructor taking token name
     * @param s token name (ex: "id","num",")")
     */
    token(string s) {
        name = s;
    }
    string name;
};

const static  token eps(string("epsilon"));


#endif //PARSER_GENERATOR_SYMBOL_H
