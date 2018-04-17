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
using std::set;
class symbol;
class token;
class parser_symbol :symbol {
private:
    set <token> first,follow;
    symbol * symb;
protected:

public:
    parser_symbol(symbol*,set<token> first,set<token> follow);
    set<token> get_first_set();
    set<token> get_follow_set();

};

#endif //PARSER_GENERATOR_PARSER_SYMBOL_H
