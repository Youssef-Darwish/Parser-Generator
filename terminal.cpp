//
// Created by youssef on 17/04/18.
//

#include "non_terminal.h"
#include "production.h"
terminal::terminal(token t) :symbol(t.name) {
    terminal_name = t;
}
non_terminal::non_terminal(string name):symbol(name) {
    this->symbol_name = name;
}


bool operator ==(const production&a, const production &b) { // move to production.cpp
    return  a.symbol_list == b.symbol_list;
}
void non_terminal:: add_production(production prod){

    for (int i=0;i<this->production_list.size();i++){
        if (production_list[i]==prod)
            return ;
    }
   production_list.push_back(prod);
}

vector <production> non_terminal::get_productions(){
    return production_list;
}
