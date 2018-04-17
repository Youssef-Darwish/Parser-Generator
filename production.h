//
// Created by youssef on 17/04/18.
//

#ifndef PARSER_GENERATOR_PRODUCTION_H
#define PARSER_GENERATOR_PRODUCTION_H

#include "vector"

using std::vector;

class symbol;
class production{

public:
//    virtual bool operator==(const symbol &);       // to compare symbols


private:
    vector<symbol*> symbol_list;
};
bool operator ==(const production&, const production &);
#endif //PARSER_GENERATOR_PRODUCTION_H
