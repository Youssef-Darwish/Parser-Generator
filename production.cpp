//
// Created by Lenovo on 4/23/2018.
//


#include "production.h"
#include "symbol.h"
production::production(vector<const symbol*>sl){
    this->symbol_list =  sl;
}

ostream& operator <<( ostream& os, const production & p) {
    os<<"("<<p.symbol_list.size()<<")";
    for(int i=0;i<p.symbol_list.size();i++) {
        os<<p.symbol_list[i] <<"."<<p.symbol_list[i]->get_name() <<" ";
    }
    return os;
}
production::production() {

}
vector <const symbol *>  production::get_symbol_list() const {
    return symbol_list;
}
