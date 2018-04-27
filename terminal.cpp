//
// Created by youssef on 17/04/18.
//

#include "non_terminal.h"
#include "production.h"
#include "symbol.h"
#include "terminal.h"
#include "analyzer/parser.h"

terminal::terminal(token t) :symbol(t.name) {
    terminal_name = t;
    this->symbol_name = t.name;
}


token terminal::get_token() const {
    return terminal_name;
}

void terminal::accept( parser *parser) const {
    parser->process((this));
}

bool production::operator ==( const production &b) { // move to production.cpp
    return  this->symbol_list == b.symbol_list;
}
const  terminal terminal::epsilon  = terminal(eps);
const terminal terminal::end_terminal = terminal(token("$"));
