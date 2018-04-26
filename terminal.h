//
// Created by Lenovo on 4/19/2018.
//

#ifndef PARSER_GENERATOR_TERMINAL_H
#define PARSER_GENERATOR_TERMINAL_H
#include "symbol.h"
class parser;
class file_parser;
class terminal :public  symbol {
public:
#ifdef debug_mode

    terminal(token t);

    token terminal_name = eps;

#endif
private:

#ifndef debug_mode

    terminal(token t);

#endif

    token terminal_name = eps;

protected:
    friend class file_parser;
    void accept( parser *) const override;
public:

    token get_token()const;

    static const  terminal epsilon;
      static const terminal end_terminal;
};

#endif //PARSER_GENERATOR_TERMINAL_H
