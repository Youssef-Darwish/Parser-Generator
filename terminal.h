//
// Created by Lenovo on 4/19/2018.
//

#ifndef PARSER_GENERATOR_TERMINAL_H
#define PARSER_GENERATOR_TERMINAL_H
#include "symbol.h"
class parser;
class file_parser;
class terminal : public symbol {

protected:
    friend class file_parser;
    token terminal_name = eps;
    terminal(token t) ;
    void accept( parser *) const override;
public:

    token get_token()const;

    static const  terminal epsilon;
      static const terminal end_terminal;
};
//const static terminal epsilon ; /// TODO define it in file parser;

#endif //PARSER_GENERATOR_TERMINAL_H
