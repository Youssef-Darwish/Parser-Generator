////
//// Created by youssef on 25/04/18.
////
//
//
//#ifndef PARSER_GENERATOR_FIRST_FOLLOW_WRAPPER_H
//#define PARSER_GENERATOR_FIRST_FOLLOW_WRAPPER_H
//
//#include "non_terminal.h"
//#include "set"
//#include "symbol.h"
//#include "map"
//
//using std::set;
//using std::vector;
//using std::map;
//
//
//class first_follow_wrapper {
//
//public:
//
//    set<token> *get_first(non_terminal *);
//
//    set<token> *get_follow(non_terminal *);
//
//    first_follow_wrapper(map<symbol *, set<token> *>,
//                         map<symbol *, set<token> *>);
//
//private:
//
//    map<symbol *, set<token> *> first_set_map;
//    map<symbol *, set<token> *> follow_set_map;
//
//};
//
//#endif //PARSER_GENERATOR_FIRST_FOLLOW_WRAPPER_H
