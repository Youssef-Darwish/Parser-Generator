//
// Created by Youssef on 20/04/18.
//
#include "first_follow_generator.h"
#include "symbol.h"
#include "production.h"
#include "parser_symbol.h"
#include "non_terminal.h"
#include "terminal.h"
#include "iostream"
#include "first_follow_wrapper.h"


first_follow_generator::first_follow_generator(vector<non_terminal *> non_ter) {

    non_terminals_received = non_ter;
    visited = (bool *) malloc(non_ter.size() * sizeof(bool));
    init();
}

void first_follow_generator::init() {
    for (auto f : non_terminals_received) {
        for (auto g : f->get_productions()) {
            for (auto h : g.get_symbol_list()) {
                if (is_terminal(h)) {
                    auto *term_token = new set<token>;
                    term_token->insert(h->get_name());
                    first_set_map[h] = term_token;
                }
            }
        }
    }
}

void first_follow_generator::start_first_calculations() {

    for (int i = 0; i < non_terminals_received.size(); i++) {

        if (first_set_map.count(non_terminals_received[i]) == 0) {
            get_first(non_terminals_received[i]);
        }
    }
    for (auto f : first_set_map) {
        std::cout << "Symbol :  " << f.first->get_name() << std::endl;
        for (auto g : *f.second) {
            std::cout << g.name << "  ";
        }
        std::cout << std::endl;
    }
    std::cout << "end of first set print " << std::endl << std::endl<< std::endl;
}


set<token> first_follow_generator::get_first(symbol *sym) {
    auto *current = dynamic_cast<non_terminal *>(sym);
    auto *first_set = new set<token>;
    for (int i = 0; i < current->get_productions().size(); i++) {
        // get first symbol in the production
        symbol *next = current->get_productions()[i].get_symbol(0);
        // symbol is terminal, just add it to first set
        if (is_terminal(next)) {
            auto *term_token = new set<token>;
            term_token->insert(next->get_name());
            first_set_map[next] = term_token;
            first_set->insert(token(next->get_name()));
            continue;
        }
            // symbol is non-terminal, find its first set

        else {

            set<token> temp = get_first((non_terminal *) next);
            // If no epsilon found in the next non-terminal, add all elements
            // of next non-terminal to current non-terminal
            if (temp.count(eps) == 0) {
                first_set->insert(temp.begin(), temp.end());
            }

                // If epsilon is found in non-terminal first set,add all terminals except epsilon
                // iterate through next non-terminals to add first sets
            else {
                // add all for now & remove epsilon later
                bool insert_epsilon = false;
                bool has_epsilon = true;
                first_set->insert(temp.begin(), temp.end());
                for (int j = 1; j < current->get_productions()[i].get_symbol_list_size()
                                && has_epsilon; j++) {

                    symbol *next_sym = current->get_productions()[i].get_symbol(j);
                    if (is_terminal(next_sym)) {
                        has_epsilon = next_sym->get_name() == "epsilon";  //TODO make it more clean
                        std::cout << "passed" << std::endl;
                        first_set->insert(next_sym->get_name());
                    } else {
                        set<token> inner = get_first((non_terminal *) next_sym);
                        first_set->insert(inner.begin(), inner.end());
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
    first_set_map[sym] = first_set;
    return *first_set;

}

void first_follow_generator::start_follow_calculations() {

    token start = token("$");
    auto *temp = new set<token>;
    temp->insert(start);
    add_in_follow(non_terminals_received[0], temp);

    for (int i = 0; i < non_terminals_received.size(); i++) {

        non_terminal *sym = non_terminals_received[i];
        int sz = sym->get_productions().size();
        for (int i = 0; i < sz; i++) {
            int size = sym->get_productions()[i].get_symbol_list_size();
            for (int j = size - 1; j > 0; j--) {
                symbol *current = sym->get_productions()[i].get_symbol(j - 1);
                // add first of j in follow of j-1 (symbol, first set)
                if (!is_terminal(current)) {
                    add_in_follow((non_terminal *) current,
                                  first_set_map[sym->get_productions()[i].get_symbol(j)]);
                }

            }
        }
    }

    for (auto f : follow_set_map){
        f.second->erase(eps);
    }

}

void first_follow_generator::add_in_follow(non_terminal *sym, set<token> *tok) {

    if (visited_symbols.count(sym) != 0)
        return;
    visited_symbols.insert(sym);

    if (!follow_set_map.count(sym)) {
        follow_set_map[sym] = new set<token>();
    }
    follow_set_map[sym]->insert(tok->begin(), tok->end());

    for (int i = 0; i < sym->get_productions().size(); i++) {
        int size = sym->get_productions()[i].get_symbol_list_size();
        bool cont;
        do {
            cont = false;
            symbol *curr = sym->get_productions()[i].get_symbol(size - 1);
            if (!is_terminal(curr)) {
                add_in_follow(dynamic_cast<non_terminal *>(curr), tok);
                if (first_set_map[curr]->count(eps)) {
                    cont = true;
                }
            }
            size--;
        } while (cont && size >= 0);
    }

    visited_symbols.erase(sym);
}

first_follow_wrapper *first_follow_generator::get_wrapper() {

    first_follow_wrapper *wrapper = new first_follow_wrapper(first_set_map, follow_set_map);
    return wrapper;

}

void first_follow_generator::print() {
    for (auto f : follow_set_map) {
        std::cout << "non-terminal :  " << f.first->get_name() << std::endl;
        f.second->erase(eps);
        for (auto g : *f.second) {
            std::cout << g.name << "  ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

}

bool first_follow_generator::is_terminal(symbol *sym) {
    for (int i = 0; i < non_terminals_received.size(); i++) {
        if (non_terminals_received[i] == sym) {
            return false;
        }
    }
    return true;
}