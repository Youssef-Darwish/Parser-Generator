//
// Created by Lenovo on 4/24/2018.
//

#ifndef PARSER_GENERATOR_HEADERS_H
#define PARSER_GENERATOR_HEADERS_H
class non_terminal;

using std::ostream;
class production;
ostream& operator <<(ostream& , non_terminal &);

ostream& operator <<( ostream& , production &);

#endif //PARSER_GENERATOR_HEADERS_H
