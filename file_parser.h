//
// Created by youssef on 17/04/18.
//

#ifndef PARSER_GENERATOR_FILE_PARSER_H
#define PARSER_GENERATOR_FILE_PARSER_H

#include "terminal.h"
#include <set>
#include <string>
#include <vector>
#include <unordered_map>
#define  NO_ERR 0
#define  INVALID_STATEMENT 1
using std::string;
using  std::set;
using std::istream;
using std::vector;
using std::unordered_map;
using std::pair;

typedef pair<int, int> substring;
class symbol;
class non_terminal;
struct file_parser_arg {
    string start_string;
    string equator;
    set<char> escape_set;
    string epsilon;
};

class file_parser{

protected:
    file_parser_arg args;
    int error_val;
    set<token> token_set;
    unordered_map<string,non_terminal*> non_terminals;
    unordered_map<string,terminal*> terminals;
    const char *input;
    int input_size;
    bool parse_productions(pair<string,substring> prod);
    bool has_set;
    vector<const non_terminal * > grammar;
public:
    file_parser(file_parser_arg);
    bool parse(const string  &c);
    bool parse(const string &c,const set<token> &token_set);
    void flush();
    vector <const non_terminal*> get_grammar();
    vector<token> get_token_set();
//    int get_error_();

};

class grammar_validator {

};
#endif //PARSER_GENERATOR_FILE_PARSER_H
