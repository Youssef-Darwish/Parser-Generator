/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CFG_to_LL1.h
 * Author: Dahlia
 *
 * Created on April 16, 2018, 11:44 PM
 */
#include"production.h"
#include "non_terminal.h"
#include "terminal.h"
#include <vector>
#include <map>
#include <set>
#include <string>

#ifndef CFG_TO_LL1_H
#define CFG_TO_LL1_H

#define productions std::vector<std::vector<std::string>>
#define grammar std::map <std::string,productions>

const std::string epsilon_ ="epsilon"; // to be updated from terminal.h
const std::string prime_rec ="'", prime_fac = "^";
class token;
class CFG_TO_LL1 {
public:
    CFG_TO_LL1(std::vector <const non_terminal * > input, std::vector<token> token_set);
    bool LL1_validator();
    vector <const  non_terminal *> get_LL1();
    void print();

private:
    std::set<token> tokens;
    std::map < std::string , non_terminal *> all_non_terminals;

    std::map < std::string , terminal *> all_terminals;
    std::vector <const non_terminal * > input,output;
    grammar CFG, LL1,original_CFG;
    std::map <int,grammar:: iterator> map_of_indices;
    bool eliminate_immediate_left_recursion(grammar::iterator i);
    void eliminate_left_recursion();
    void left_factor(grammar::iterator it);
    void left_factor();
    void substitute(grammar::iterator i,grammar::iterator j);
    void replace(int k, productions & modified, productions productions_j, productions productions_i);
    grammar clone();
    void from_input_to_CFG();
    void print_grammar (grammar g);
};

#endif /* CFG_TO_LL1_H */

