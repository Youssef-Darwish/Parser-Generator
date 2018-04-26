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
    friend class file_parser;
    friend  class CFG_TO_LL1;
public:

    /**
     * class equating symbols
     * @return true iff the 2 symbols have the same name
     */
    virtual bool operator==(const symbol &);       // to compare symbols
    string get_name(); //
         // check it

#ifdef debug_mode
     symbol(string);
    string symbol_name;
#endif
    string get_name() const ;

    /* pure virtual function to serve the parser visitor class */
    virtual void accept( parser *) const= 0;


protected :
#ifndef debug_mode
    string symbol_name;
    symbol(string);       // check it

#endif
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

const static  token end_token(string("$"));

#endif //PARSER_GENERATOR_SYMBOL_H
