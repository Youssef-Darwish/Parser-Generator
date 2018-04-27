#include <iostream>
#include <sstream>
#include <fstream>

#define debug_mode

#include "symbol.h"
#include "headers.h"
#include "file_parser.h"
#include "first_follow_generator.h"
#include "predictive_table.h"
#include "CFG_to_LL1.h"
#include "analyzer/parser.h"

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
    arg.enc1 = arg.enc2 = '\'';
    arg.equator = "=";
    file_parser fp = file_parser(arg);
    ifstream ifile("../grammar.txt");
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
     cout <<all<<endl;

    cout << "\n*******************\n";

    cout << fp.parse(all)<<endl;
    vector<const non_terminal*> vec = fp.get_grammar();
    for(int i=0;i<vec.size();i++) {
        cout<<vec[i] <<" "<<(*vec[i]);
    }
    cout<<endl;
    return  0;
    vector <token> vt = fp.get_token_set();

    CFG_TO_LL1 convertor(vec,vt);
    cout << convertor.LL1_validator()<<endl;
    vector<const  non_terminal * > LL1 = convertor.get_LL1();

    for(int i=0;i<LL1.size();i++) {
        cout<<LL1[i] <<" "<<(*LL1[i]);
    }

    cout<<endl;
    vt.push_back(end_token);
    cout<<"first follow \n";
    first_follow_generator *generator = new first_follow_generator(vec);
    generator->start_first_calculations();
    generator->start_follow_calculations();
    generator->print();
    first_follow_wrapper * wrap = generator->get_wrapper();
    cout<<*wrap<<endl;
    predictive_table * pt = new predictive_table(vt,vec,*wrap);
    cout<<*pt<<endl;
    cout <<"end"<<endl;



    parser p = parser(pt);
    p.parse();

      return 0;
}