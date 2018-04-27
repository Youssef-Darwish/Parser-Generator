//
// Created by Lenovo on 4/19/2018.
//

#include "non_terminal.h"
#include "production.h"
#include "iostream"
#include "symbol.h"
#include "terminal.h"
#include "analyzer/parser.h"

void non_terminal::add_production(production prod) {

    for (int i = 0; i < this->production_list.size(); i++) {
        if (production_list[i] == prod)
            return;
    }
    production_list.push_back(prod);
}

vector<production> non_terminal::get_productions() const {
    return production_list;
}

non_terminal::non_terminal(string name) : symbol(name) {
    this->symbol_name = name;
//    std::cout<<"bla";
}

void non_terminal::accept( parser *parser) const {
    parser->process((this));
}

ostream &operator<<(ostream &os, const non_terminal &p) {
    os << p.symbol_name <<"("<<p.production_list.size()<<")"<<"::=";
    for (int i = 0; i < p.production_list.size(); i++) {
        os << p.production_list[i] << "|";
    }
    os << "\n";
    return os;
}
