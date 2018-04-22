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

first_follow_generator::first_follow_generator(vector<non_terminal *> non_ter) {

    non_terminals_received = non_ter;
    visited = (bool *) malloc(non_ter.size() * sizeof(bool));
}

void first_follow_generator::start_first_calculations() {


    for (int i = 0; i < non_terminals_received.size(); i++) {

        if (first_set_map.count(non_terminals_received[i]) == 0) {

//            std::cout << "terminal not found: " << non_terminals_received[i]->get_name() << std::endl;

            get_first(non_terminals_received[i]);
        } else {
//            std::cout << "terminal: " << non_terminals_received[i]->get_name() << std::endl;
//            for (std::map<non_terminal *, std::set<token> *>::iterator it = first_set_map.begin();
//                 it != first_set_map.end(); ++it)
//                std::cout << it->first->get_name() << " => " << it->second->size() << '\n';

        }
    }
}

void first_follow_generator::start_follow_calculations() {

    for (int i = 0; i < non_terminals_received.size(); i++) {

    }
}

set<token> first_follow_generator::get_first(non_terminal *sym) {
    non_terminal *current = sym;
    set<token> *first_set = new set<token>;
    function_calls++;
    std::cout<<function_calls<<std::endl;
    for (int i = 0; i < current->get_productions().size(); i++) {
        // get first symbol in the production
//        std::cout << " size : " << current->get_productions().size() << std::endl;
        symbol *next = current->get_productions()[i].get_symbol(0);
//        std::cout<<"name  " <<next->get_name() <<std::endl;
        // symbol is terminal, just add it to first set
//
//        terminal * test = dynamic_cast<terminal*>(next);
//        non_terminal * test2 = dynamic_cast<non_terminal*>(next);
//        std::cout<<"casting"<<(test == NULL) <<" "<<(test2 == NULL)<<std::endl;

        if (dynamic_cast<non_terminal *>(next)==NULL) {
            first_set->insert(next->get_name());
            continue;
        }
            // symbol is non-terminal, find its first set

        else {

            set<token> temp = get_first((non_terminal *) next);
            // If no epsilon found in the next non-terminal, add all elements
            // of next non-terminal to current non-terminal
//            std::cout<<"arrived after rec" <<std::endl;
            if (temp.count(token("epsilon")) == 0) {
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
                    if (dynamic_cast<terminal *>(next_sym)) {
                        has_epsilon = next_sym->get_name()=="epsilon";  //TODO make it more clean
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
    std::cout <<"name of symbol  " <<sym->get_name()<<std::endl;
    for(auto f : *first_set) {
        std::cout << f.name << " ";
    }
    std::cout<<std::endl;
    return *first_set;

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
