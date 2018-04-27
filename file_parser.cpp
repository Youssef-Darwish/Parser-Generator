//
// Created by Engineer Ahmed Hamdy on 4/22/2018.
//
#include <cstring>
#include "file_parser.h"
#include "terminal.h"
#include "non_terminal.h"
#include "production.h"
#define debug_mode
#ifdef  debug_mode
#include <iostream>
using std::cout;
using std::endl;
#endif
using std::pair;
using std::unordered_map;

file_parser::file_parser(file_parser_arg args) {
    this->args = args;
    error_val = NO_ERR;
    has_set = false;
}

#define ind first
#define siz second

void create_lps(const string &str, int lps[]) {
    lps[0] = 0;
    int l = 0;
    int i = 1;
    while (i < str.size())
        if (str[i] == str[l])
            lps[i++] = ++l;
        else if (l == 0)
            lps[i++] = 0;
        else
            l = lps[l - 1];

}
string copy_ind(const char* str,substring sub,set<char> &escape) {
    string res;
    int i = 0;
    while(i < sub.siz &&   escape.count(str[i+sub.ind])) {
        i++;
    }
    if(i == sub.siz)
        return "";
    char temp[256];
    strncpy(temp,str+sub.ind+i,sub.siz - (i-sub.ind));
    i = sub.siz - (i ) - 1;
    while(i >=0 && escape.count(temp[i]))
        i--;
    temp[i+1] = 0;
    return  string(temp);
}
vector<int> occu(int lps[], const string &delim, const char str[], int n,char e1,char e2) {
    int i = 0, j = 0;
    vector<int> occs;
   // char temp[256*256];
   // strncpy(temp, str, n);
    //temp[n] = 0;
    if (delim.size() > n)
        return occs;
    bool es = 0;
    while (i < n) {
        if(str[i] == e1 && !es) {
            es = 1;
            j = 0;

        }
        else if(str[i] == e2 && es)
            es =0;
        if(es) {
            i++;
            continue;
        }
        if (str[i] == delim[j])
            i++, j++;
        else if (j == 0)
            i++;
        else
            j = lps[j - 1];
        if (j == delim.size()) {
            occs.push_back(i - j);
            j = 0;
        }
    }
}
vector<substring> split_string(const set<char> &delims,const char str[],int n) {
    vector <substring> rets;
    int lst = 0;
    for(int i=0;i<n;i++) {
        if(delims.count(str[i]) ) {
            if(i>lst)
                rets.push_back({lst,i-lst});
            lst = i+1;
        }
    }
    if(n - lst)
        rets.push_back({lst,n-lst});
    return  rets;
}
vector<substring> split_string(const string &delim, const char str[], int n,char escape1 ,char escape2) {
    int lps[256];
    create_lps(delim, lps);
    int del_size = delim.size();
    vector<int> seps = occu(lps, delim, str, n,escape1,escape2);
    vector<substring> rets;
    int cur, sz, lst = 0;
    for (int i = 0; i < seps.size(); i++) {
        cur = seps[i];
       if(cur > 0 && str[cur-1] =='\\')
            continue;
        sz = cur - lst;
        if (sz)
            rets.push_back({lst, sz});
        lst = cur + del_size;
    }
    if (n - lst)
        rets.push_back({lst, n - lst});
    return rets;
}
bool file_parser::parse_productions(pair<string,substring> prod) {
    const char *bas = input+prod.second.ind;
    non_terminal * cur = non_terminals[prod.first];
    if(cur == NULL)
        return false;
    set<char> temp;
    temp.insert('|');
    vector<substring> all_prods = split_string(temp,bas,prod.second.siz);
    for ( int i = 0 ;i < all_prods.size();i++) {
        const char *pbase = bas + all_prods[i].ind;
        int psize = all_prods[i].siz;
        vector<const symbol*> new_prod;
        vector<substring> contents = split_string(args.escape_set,pbase,psize);
        for(int j = 0;j < contents.size();j++) {
            char temp[256];
            string symbol_name = copy_ind(pbase,contents[j],args.escape_set);
            const symbol * nsym;
            if(symbol_name == args.epsilon) {
                nsym = &terminal::epsilon;
            }
            else if(non_terminals.count(symbol_name)) {
                nsym = non_terminals[symbol_name];
            }
            else if (terminals.count(symbol_name))
                nsym = terminals[symbol_name];
            else {
                nsym = new terminal(token(symbol_name));
                terminals[symbol_name] = (terminal*)nsym;
                if(has_set) {
                    if(!token_set.count(symbol_name))
                        return  false;
                }
                else
                    token_set.insert(symbol_name);
            }
            new_prod.push_back(nsym);
        }
        cur->production_list.push_back(production(new_prod));
    }
    return true;

}
bool file_parser::parse(const string &c) {
    input = c.c_str();
    input_size = strlen(input);
    vector<substring> productions = split_string(args.start_string, input, input_size,args.enc1,args.enc2);
    vector < pair< string , substring > > production_list;
    for (int i = 0 ;i < productions.size();i++) {
        //cout<< copy_ind(input,productions[i],args.escape_set)<<" done that from "<<productions[i].ind <<" "<<
          //  productions[i].siz << endl;
        int base  = productions[i].ind;
        const char * view = input + base;
        vector<substring> sides;
        sides = split_string(args.equator,input+base,productions[i].siz,args.enc1,args.enc2);
        if(sides.size() !=2) {

            error_val = INVALID_STATEMENT;
            return false;
        }
        string temp_str =copy_ind(input+base,sides[0],args.escape_set);
        if(!non_terminals.count(temp_str))
            non_terminals[temp_str] = new non_terminal(temp_str);
        production_list.push_back({temp_str,{productions[i].ind + sides[1].ind,sides[1].siz}});

    }
    set<non_terminal*> added;
    for (int i = 0 ;i < production_list.size(); i++) {
        if(!parse_productions(production_list[i]))
            return false;
        if(added.count(non_terminals[production_list[i].first]))
            continue;
        grammar.push_back(non_terminals[production_list[i].first]);
        added.insert(non_terminals[production_list[i].first]);
    }

    return true;

}

bool file_parser::parse(const string &c, const set<token> &token_set){
    has_set = true;
    this->token_set = token_set;
    return parse(c);
}
void file_parser::flush() {
    has_set = false;
    unordered_map<string,non_terminal*>::iterator it;
    for(it = non_terminals.begin();it!=non_terminals.end();it++) {
        non_terminal * cur = it->second;
        delete cur;
    }
    unordered_map<string,terminal*>::iterator it2;

    for(it2 = terminals.begin();it2!=terminals.end();it2++) {
        terminal * cur = it2->second;
        delete cur;
    }
    non_terminals.clear();
    terminals.clear();
    token_set.clear();
    grammar.clear();
    input_size = 0;
}
//
vector<const non_terminal *> file_parser::get_grammar() {
    return  grammar;
}
vector<token> file_parser::get_token_set() {
    vector <token> toret;
    for(auto i:token_set) {
        toret.push_back(i);
    }
    return  toret;
}

//
//set<token> get_token_set();
//
//int get_error_();