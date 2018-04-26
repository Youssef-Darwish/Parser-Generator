//
// Created by Lenovo on 4/24/2018.
//

#ifndef PARSER_GENERATOR_HEADERS_H
#define PARSER_GENERATOR_HEADERS_H

#include <ostream>

class non_terminal;

using std::ostream;
class production;
class first_follow_wrapper;
class predictive_table;
ostream& operator <<(ostream& ,const  non_terminal &) ;

ostream& operator <<( ostream& , const production &);


ostream& operator <<( ostream& ,  first_follow_wrapper &);

ostream& operator <<( ostream& ,  predictive_table &);

#endif //PARSER_GENERATOR_HEADERS_H
