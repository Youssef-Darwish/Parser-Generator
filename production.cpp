//
// Created by Lenovo on 4/23/2018.
//


#include "production.h"
#include "symbol.h"
production::production(vector<const symbol*>sl){
    this->symbol_list =  sl;
}

ostream& operator <<( ostream& os, production & p) {
    for(int i=0;i<p.symbol_list.size();i++) {
        os<<p.symbol_list[i]->get_name() <<" ";
    }
    return os;
}
production::production() {

}
const vector <const symbol *> * production::get_symbol_list() {
    return &symbol_list;
}
