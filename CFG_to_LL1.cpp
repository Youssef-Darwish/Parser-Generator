/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/* 
 * File:   CFG_to_LL1.cpp
 * Author: Dahlia
 *
 * Created on April 16, 2018, 11:44 PM
 */
#include "production.h"
#include "symbol.h"
#include "non_terminal.h"
#include "CFG_to_LL1.h"
#include "terminal.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>

CFG_TO_LL1::CFG_TO_LL1(vector <non_terminal> input) {
    this-> input = input;
}

void CFG_TO_LL1::from_input_to_CFG() {
    for (int i = 0; i < input.size(); i++) {
        
        std::string non_terminal =input[i].get_name();
        vector <production> prod_list =input[i].get_productions();
        productions to_fill(prod_list.size());

        for (int j=0;j<prod_list.size();j++)
        {
            for (int k=0;k<prod_list[j].size();k++)
            {
                symbol* sym =prod_list[j].get_symbol(k);
                to_fill[j].push_back(sym->get_name());
            }
        }
        CFG.insert(make_pair(non_terminal,to_fill));
        map_of_indices.insert(make_pair(i,CFG.find(non_terminal)));
    }
    original_CFG=CFG;
}
vector <non_terminal> CFG_TO_LL1::get_LL1()
{
    for (auto it=LL1.begin();it!=LL1.end();it++)
    {
        non_terminal x = non_terminal (it->first);
        for (int i=0;i<it->second.size();i++)
        {
            production prod;
            for (int j=0;j<it->second.size();j++)
            {
                symbol* sym = new symbol(it->second[i][j]);
                prod.add_to_symbol_list(sym);
            }
            x.add_production(prod);
        }
        output.push_back(x);
    }
    return output;
}
void CFG_TO_LL1::print_grammar (grammar g)
{
    for (auto it = g.begin();it!=g.end();it++)
    {
        std::cout <<it->first <<" -> ";
        for (int i=0;i<it->second.size();i++)
        {
           for (int j=0;j<it->second[i].size();j++)
           {
               std::cout <<it->second[i][j];
           }
          if (i!=it->second.size()-1) std:: cout <<" | ";
        }
        std::cout <<"\n";
    }
}
void  CFG_TO_LL1::print()
{
    std::cout<<"CFG"<<"\n";
    print_grammar(CFG);
    std::cout<<"LL1"<<"\n";
    print_grammar(LL1);
}
bool CFG_TO_LL1::eliminate_immediate_left_recursion(grammar::iterator i) {
    
    std::string non_terminal = i->first, non_terminal_prime = non_terminal + prime;
    productions non_terminal_productions = i->second;
    productions prime_productions;
    int old_size=non_terminal_productions.size();
    for (int k = 0; k < non_terminal_productions.size(); k++) {
        if (non_terminal_productions[k][0] != non_terminal) continue;
        non_terminal_productions[k].erase(non_terminal_productions[k].begin());
        non_terminal_productions[k].push_back(non_terminal_prime);
        prime_productions.push_back(non_terminal_productions[k]);
        non_terminal_productions.erase(non_terminal_productions.begin() + k);
    }
    if (non_terminal_productions.size()==old_size)
    {
       LL1.insert(make_pair(i->first,i->second));
        return 0;
    }
    std::vector <std::string> empty(1);
    empty[0]=epsilon_;
    prime_productions.push_back(empty);

    for (int j = 0; j < non_terminal_productions.size(); j++)
        non_terminal_productions[j].push_back(non_terminal_prime);
    LL1.insert(make_pair(non_terminal,non_terminal_productions));
    LL1.insert(make_pair(non_terminal_prime,prime_productions));
    return 1;
    }

void CFG_TO_LL1::eliminate_left_recursion() {
    for (auto i = map_of_indices.begin(); i != map_of_indices.end(); i++) {
        for (auto j = map_of_indices.begin(); j != i; j++)
               substitute(i->second, j->second);
        eliminate_immediate_left_recursion(i->second);
        }
}

void CFG_TO_LL1::substitute(grammar::iterator i, grammar::iterator j) {
            productions productions_j = LL1.find(j->first)->second; // substitute with production from LL1
            productions productions_i = i->second; // get production to be modified from CFG
            productions modified, temp,to_fill(productions_j.size());
            temp = productions_j;
           
    for (int k = 0; k < productions_i.size(); k++) {
        modified.clear();
        temp = productions_j;
        for (int l = 0; l < productions_i[k].size(); l++) {
            if ((LL1.find(j->first) != LL1.end())&& (productions_i[k][l] != LL1.find(j->first)->first))continue;
            productions_i[k].erase(productions_i[k].begin() + l); // vector to be appended
            // Append operation
            for (int m = 0; m < productions_j.size(); m++){
                to_fill[m].insert(to_fill[m].end(), productions_i[k].begin(), productions_i[k].begin()+l);
                to_fill[m].insert(to_fill[m].end(), temp[m].begin(), temp[m].end());
                to_fill[m].insert(to_fill[m].end(), productions_i[k].begin()+l, productions_i[k].end());
            }
               
            replace(k, modified, to_fill, productions_i);
            i->second=modified;
            
            if (!eliminate_immediate_left_recursion(i))
            {
                i->second = original_CFG.find(i->first)->second;
                LL1.erase(LL1.find(i->first));
            } 
        }
    }
}

void CFG_TO_LL1::replace(int k, productions & modified, productions productions_j, productions productions_i) {
    int a = 0;
    for (a = 0; a < k; a++)
        modified.push_back(productions_i[a]);
    for (a = 0; a < productions_j.size(); a++)
       modified.push_back(productions_j[a]);
    for (a = k + 1; a < productions_i.size(); a++)
         modified.push_back(productions_i[a]);
            
}
void CFG_TO_LL1::left_factor() {
    grammar copy = clone();
  for (grammar::iterator i = copy.begin(); i != copy.end(); i++) 
      left_factor(i);
}

void CFG_TO_LL1::left_factor(grammar::iterator it) {
    std::map <std::string,std::string > state;
    std::map <std::string,productions> left_factored_symbols;
    productions p= it->second,to_fill;
    std::vector<std::string> eps ;
    eps.push_back(epsilon_);
    
    for (int i=0;i<p.size();i++)
    {
        to_fill.clear();
        if (left_factored_symbols.find(p[i][0])== left_factored_symbols.end())
        {
            std::string entry= p[i][0];
            p[i].erase(p[i].begin());
            if (p[i].empty()) to_fill.push_back(eps);
            else to_fill.push_back(p[i]);
            left_factored_symbols.insert(make_pair(entry,to_fill));
            state.insert(make_pair(entry,it->first));
        }
        else
        {
            p[i].erase(p[i].begin());
            if (p[i].empty()) left_factored_symbols.find(p[i][0])->second.push_back(eps);
            else left_factored_symbols.find(p[i][0])->second.push_back(p[i]);
            grammar:: iterator itr = LL1.find(it->first);
            itr->second.erase(itr->second.begin()+i);
        }
    }
     std::vector<std::string> temp;
     std::string non_terminal_prime="",primes="";
    for (auto k=left_factored_symbols.begin();k!=left_factored_symbols.end();k++)
    {
        if (k->second.size()==1)continue;
        temp.clear();
        non_terminal_prime="";
        primes+=prime;
        non_terminal_prime=(state.find(k->first)->second)+primes;
        for (int i=0;i<LL1.find(it->first)->second.size();i++)
        {
            if (LL1.find(it->first)->second [i][0]==k->first){
                LL1.find(it->first)->second.erase( LL1.find(it->first)->second.begin()+i);
                break;
            }
        }
        temp.push_back(k->first);
        temp.push_back(non_terminal_prime);
        LL1.find(it->first)->second.push_back(temp);
        LL1.insert(make_pair(non_terminal_prime,k->second));
    } 
}
grammar CFG_TO_LL1::clone()
{
    grammar copy;
    for (grammar::iterator i = LL1.begin(); i != LL1.end(); i++) 
        copy.insert(make_pair(i->first,i->second));
    return copy;
}
bool CFG_TO_LL1::LL1_validator() {
    
        from_input_to_CFG();
        eliminate_left_recursion();
        left_factor();
        print();
        return (CFG==LL1);
}
