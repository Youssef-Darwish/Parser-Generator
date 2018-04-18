//
// Created by Lenovo on 4/18/2018.
//

#ifndef PARSER_GENERATOR_PREDICTIVE_TABLE_H
#define PARSER_GENERATOR_PREDICTIVE_TABLE_H

#include <vector>
using std::vector;
class token;
class parser_symbol;
class production;
class predictive_table {
    public:
        predictive_table(vector<token> token_set,vector<parser_symbol> );
        /**
         * gets production from state and token
         * @return production
         */
        production get(parser_symbol,token);
};
#endif //PARSER_GENERATOR_PREDICTIVE_TABLE_H
