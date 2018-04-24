//
// Created by youssef on 17/04/18.
//

#include "non_terminal.h"
#include "production.h"
#include "symbol.h"
#include "terminal.h"

terminal::terminal(token t) :symbol(t.name) {
    terminal_name = t;
    this->symbol_name = t.name;
}


bool production::operator ==( const production &b) { // move to production.cpp
    return  this->symbol_list == b.symbol_list;
}