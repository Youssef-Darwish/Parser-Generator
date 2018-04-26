//
// Created by Lenovo on 4/18/2018.
//
#include "predictive_table.h"
#include "production.h"
#include "terminal.h"
#include "non_terminal.h"
#include "wrapper.h"
#include <vector>
using std::vector;

predictive_table::predictive_table( const vector<token> &token_set,const vector<parser_symbol*> &all_sym ,
                                     first_follow_wrapper & ftab):tab(ftab){
    this->token_set = token_set;
    this->construction_set = all_sym;
    this->tab = tab;
    construct();
}

int predictive_table::get_prod(parser_symbol * s,token t) {

    if(symb_tab.count(s) && token_tab.count(t))
        return  table [symb_tab[s]][token_tab[t]];
    return -2;
}
void predictive_table::construct() {
    if(!construction_set.size())
        return;
    start = construction_set[0];
    for(int j = 0; j < token_set.size() ; j ++) {
        token_tab[token_set[j]] = j;
    }
        for (int i = 0; i < construction_set.size();i++) {
        table.push_back(vector<int>());
        symb_tab[construction_set[i]] = i;
        for(int j = 0; j < token_set.size() ; j ++) {
            int v = -1;
            if(tab.get_first(construction_set[i])->count(token_set[j])) {
                vector < production> allps = construction_set[i]->get_productions();
                for(int k = 0; k < allps.size() && v <0;k++) {
                    const symbol * ofst  = allps[k].get_symbol_list().at(0);
                    if(tab.get_first(ofst)->count(token_set[j]))
                        v = k;
                }

            }
            else if (tab.get_follow(construction_set[i])->count(token_set[j])) {
                vector < production> allps = construction_set[i]->get_productions();
                for(int k = 0; k < allps.size() && v <0;k++) {
                    const symbol *ofst = allps[k].get_symbol_list().at(0);
                    if (ofst == &terminal::epsilon)
                        v = k;
                }
            }
            table[i].push_back(v);
        }
    }
}
parser_symbol * predictive_table::get_start() {
    return start;
}

entry_status  predictive_table::get_entry_status( parser_symbol * s, token t) {
    int val = get_prod(s,t);
    if(val >= 0)
        return  VALID;
    if(tab.get_follow(s)->count(t))
        return SYNCH;
    return ERROR;
}
production predictive_table::get_next_production(const parser_symbol* s ,token t) {
    int val = get_prod(s,t);
    if(val >=0)
        return s->get_productions()[val];
    return  production();

}

ostream& operator <<( ostream& os,  predictive_table & tab) {
        os<<"\t|";
        for (int i=0;i<tab.token_set.size();i++)
            os<<tab.token_set[i].name<<"\t|";
        os<<"\n";
        for(int i=0;i<tab.construction_set.size();i++) {
            os<<tab.construction_set[i]->get_name()<<"::\t|";
            for(int j=0;j<tab.table[i].size();j++) {
                int err = tab.get_entry_status(tab.construction_set[i],tab.token_set[j]);
                if(err == VALID) {
                    os<<tab.construction_set[i]->get_productions()[tab.get_prod(tab.construction_set[i],tab.token_set[j])]<<"\t|";
                } else if(err == SYNCH)
                    os<<"SYNCH\t|";
                else
                    os<<"ERR\t|";
            }
            os<<"\n";
        }
    return  os;
}