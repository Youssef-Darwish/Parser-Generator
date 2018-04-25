#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <fstream>

#define debug_mode

#include "headers.h"
#include "file_parser.h"
using  namespace std;
int main() {
    cout <<"start" <<endl;
    file_parser_arg arg;
    arg.epsilon = "\\L";
    arg.escape_set.insert('\t');
    arg.escape_set.insert(' ');
    arg.escape_set.insert('\n');
    arg.escape_set.insert('\'');
    arg.start_string = "#";
    arg.equator = "=";
    file_parser parser = file_parser(arg);
    ifstream ifile("E:/Projects/Syntax Analyzer/Parser-Generator/test.txt");
    stringstream ss;
    string all;
    while(!ifile.eof()) {
        string t;
        getline(ifile,t);
        ss <<t;
        if(!t.size() ||  t[0] == '~')
            continue;
        all+=t;
    }
   // cout <<all<<endl;

    cout << parser.parse(all)<<endl;
    vector<non_terminal*> vec = parser.get_grammar();
    for(int i=0;i<vec.size();i++) {
        cout<<vec[i] <<" "<<(*vec[i]);
    }
    cout <<"end"<<endl;
    return 0;
}