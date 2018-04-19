//
// Created by youssef on 17/04/18.
//
#include "non_terminal.h"
#include "parser_symbol.h"
#include "symbol.h"

parser_symbol::parser_symbol(symbol *sym, set<token> first,
                             set<token> follow) : symbol(sym->get_name()) {
    this->first = first;
    this->follow = follow;
    this->symb = sym;

}


set<token> parser_symbol::get_first_set() {

    return first;
}

set<token> parser_symbol::get_follow_set() {
    return follow;
}