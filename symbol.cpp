//
// Created by youssef on 17/04/18.
//

#include "symbol.h"

bool symbol::operator==(const symbol & sym) {
        return this->symbol_name == sym.symbol_name;
}
symbol::symbol(string name) {
        this->symbol_name = name;
}
string symbol::get_name() const {
    return symbol_name;
}

//const token token::eps = token(string("epsilon"));
bool token::operator < (const token &t) const {
    return this->name < t.name;
}
bool token::operator ==(const token &t) const  {
    return  this->name == t.name;
}