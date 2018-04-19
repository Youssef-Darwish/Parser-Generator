//
// Created by Chalixar on 17/04/18.
//
/**
 * class represents predictive table entry
 * the entry consists of a symbol and its follow and first sets
 */

#ifndef PARSER_GENERATOR_PARSER_SYMBOL_H
#define PARSER_GENERATOR_PARSER_SYMBOL_H

#include "set"
#include "symbol.h"
using std::set;
class token;
/**
 * class representing symbol with first and follow set
 */
class parser_symbol :symbol {
private:
    set <token> first,follow;
    symbol * symb;
protected:

public:
    /**
     * constructor creating the symbol with first and follow sets
     * @param first set<token> representing first set
     * @param follow  set<token> representing follow set
     */
    parser_symbol(symbol*,set<token> first,set<token> follow);
    set<token> get_first_set();
    set<token> get_follow_set();

};

#endif //PARSER_GENERATOR_PARSER_SYMBOL_H
