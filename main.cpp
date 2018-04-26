#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <fstream>

#define debug_mode

#include "symbol.h"
#include "headers.h"
#include "file_parser.h"
#include "first_follow_generator.h"
#include "predictive_table.h"
#include "CFG_to_LL1.h"
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
    vector<const non_terminal*> vec = parser.get_grammar();
    for(int i=0;i<vec.size();i++) {
        cout<<vec[i] <<" "<<(*vec[i]);
    }
    vector <token> vt = parser.get_token_set();

    CFG_TO_LL1 convertor(vec,vt);
    cout << convertor.LL1_validator()<<endl;
//    vector<const  non_terminal * > LL1 = convertor.get_LL1();
//
//    for(int i=0;i<LL1.size();i++) {
//        cout<<LL1[i] <<" "<<(*LL1[i]);
//    }

    cout<<endl;
    vt.push_back(end_token);
//    cout<<"first follow \n";
//    first_follow_generator *generator = new first_follow_generator(vec);
//    generator->start_first_calculations();
//    generator->start_follow_calculations();
//    generator->print();
//    first_follow_wrapper * wrap = generator->get_wrapper();
//    cout<<*wrap<<endl;
//    predictive_table * pt = new predictive_table(vt,vec,*wrap);
//    cout<<*pt<<endl;
//    cout <<"end"<<endl;
//
      return 0;
}