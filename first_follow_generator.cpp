//
// Created by youssef on 20/04/18.
//

#include "first_follow_generator.h"
#include "symbol.h"
#include "production.h"
#include "parser_symbol.h"
#include "non_terminal.h"

first_follow_generator::first_follow_generator(vector<symbol *> symbols) {
    parser_syms.resize(symbols.size());
    visited = new bool[symbols.size()];

}

set<token> first_follow_generator::get_first(non_terminal * sym) {

    non_terminal * current = sym;
    set<token> first_set;
    for (int i =0;i<current->get_productions().size();i++){
        symbol * next = current->get_productions()[i].get_symbol[0];

    }

}


set<token> first_follow_generator::get_follow(non_terminal * sym) {

}

vector<parser_symbol> first_follow_generator::get_parser_symbols() {
    return parser_syms;
}
