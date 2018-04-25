//
// Created by Lenovo on 4/18/2018.
//

#ifndef PARSER_GENERATOR_PREDICTIVE_TABLE_H
#define PARSER_GENERATOR_PREDICTIVE_TABLE_H

#include <vector>
#include <unordered_map>
#include "non_terminal.h"
#include "wrapper.h"
using std::vector;
using std::unordered_map;
class token;
typedef const non_terminal parser_symbol;
class production;
enum entry_status {
    VALID,
    ERROR,
    SYNCH
};
class predictive_table {
    public:
        predictive_table(const vector<token> &,const vector<parser_symbol*>&,  first_follow_wrapper & );
        /**
         * gets production from state and token
         * @return production
         */
        production get_next_production( parser_symbol*,token);
        const parser_symbol * get_start();
        entry_status  get_entry_status( parser_symbol * , token);

protected :
    int get_prod(parser_symbol * ,token);
    unordered_map<parser_symbol * ,int> symb_tab;

    unordered_map<token ,int> token_tab;
      void construct();
      parser_symbol * start;
     first_follow_wrapper &tab;
     vector<token> token_set;
     vector<parser_symbol*> construction_set;
     vector < vector < int > > table;
};
#endif //PARSER_GENERATOR_PREDICTIVE_TABLE_H
