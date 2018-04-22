//
// Created by Youssef on 20/04/18.
//

#include "first_follow_generator.h"
#include "symbol.h"
#include "production.h"
#include "parser_symbol.h"
#include "non_terminal.h"
#include "terminal.h"

first_follow_generator::first_follow_generator(vector<non_terminal *> non_ter) {
    parser_syms.resize(non_ter.size());
    non_terminals_received = non_ter;
    visited = new bool[non_ter.size()];

}

void first_follow_generator::start_first_calculations() {

    for (int i = 0; i < non_terminals_received.size(); i++) {
        if (first_set_map.count(non_terminals_received[i]) == 0) {
            get_first(non_terminals_received[i]);
        }
    }
}

void first_follow_generator::start_follow_calculations() {

    for (int i = 0; i < non_terminals_received.size(); i++) {

    }
}

set<token> first_follow_generator::get_first(non_terminal *sym) {
    non_terminal *current = sym;
    set<token> first_set;
    // E --> ;T;   ??
    // use visited array / map and call it from an outer function

    for (int i = 0; i < current->get_productions().size(); i++) {
        // get first symbol in the production

        symbol *next = current->get_productions()[i].get_symbol(0);
        // symbol is terminal, just add it to first set

        if (dynamic_cast<terminal *>(next)) {
            first_set.insert(next->get_name());
            continue;
        }
            // symbol is non-terminal, find its first set

        else {
            set<token> temp = get_first((non_terminal *) next);
            // If no epsilon found in the next non-terminal, add all elements
            // of next non-terminal to current non-terminal

            if (temp.count(token("epsilon")) == 0) {
                first_set.insert(temp.begin(), temp.end());
            }

                // If epsilon is found in non-terminal first set,add all terminals except epsilon
                // iterate through next non-terminals to add first sets
            else {

                // add all for now & remove epsilon later
                bool insert_epsilon = false;
                bool has_epsilon = true;
                first_set.insert(temp.begin(), temp.end());
                for (int j = 1; i < current->get_productions()[i].get_symbol_list_size()
                                && has_epsilon; j++) {

                    symbol *next_sym = current->get_productions()[i].get_symbol(j);
                    if (dynamic_cast<terminal *>(next_sym)) {
                        has_epsilon = false;
                        first_set.insert(next_sym->get_name());
                    } else {
                        set<token> inner = get_first((non_terminal *) next_sym);
                        first_set.insert(inner.begin(), inner.end());
                        if (inner.count(token("epsilon")) == 0) {
                            has_epsilon = false;
                            if (j == current->get_productions()[i].get_symbol_list_size() - 1) {
                                insert_epsilon = true;
                            }
                        }

                    }
                }

            }

        }

    }

    first_set_map[sym] = &first_set;
    return first_set;

}


set<token> first_follow_generator::get_follow(non_terminal *sym) {

    if (follow_set_map.count(sym)) {
        return *follow_set_map[sym];
    }
    // make a function called: copy_set_except_epsilon xD

    // call bardo from outer function?
    non_terminal *current = sym;
    set<token> follow_set;

    for (int i = 0; i < current->get_productions().size(); i++) {
        symbol *next = current->get_productions()[i].get_symbol(0);
        if (dynamic_cast<terminal *>(next)) {
            continue;
        }

    }


}

vector<parser_symbol> first_follow_generator::get_parser_symbols() {
    return parser_syms;
}
