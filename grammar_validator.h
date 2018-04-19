//
// Created by Lenovo on 4/19/2018.
//

#ifndef PARSER_GENERATOR_GRAMMAR_VALIDATOR_H
#define PARSER_GENERATOR_GRAMMAR_VALIDATOR_H

#include <vector>
using  std::vector;
class production;
class symbol;
class grammar_validator {
public:
    vector<symbol> convert_grammar(vector<symbol>); //converts grammar to LL1
    bool is_LL1(vector<symbol>); // checks if grammar is LL1
};
#endif //PARSER_GENERATOR_GRAMMAR_VALIDATOR_H
