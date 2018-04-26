//
// Created by youssef on 17/04/18.
//

#ifndef PARSER_GENERATOR_PRODUCTION_H
#define PARSER_GENERATOR_PRODUCTION_H

#include <vector>
#include <string>
#include <iostream>
using std::vector;
using std::string;
using std::ostream;
class symbol;
/**
 * class representing RHS of 1 single production
 * for example A->BCD|ED the class may hold either BCD  or ED
 * the production is represented bs a vector of symbol references
 */
class production{

public:

#ifdef debug_mode
    vector<symbol *> symbol_list;
#endif

    const symbol *get_symbol(int index) {
        return symbol_list[index];
    }

    int get_symbol_list_size() {
        return (int) symbol_list.size();
    }
    vector<const symbol *> get_symbol_list() const;

production();
production(vector<const symbol*>);
friend ostream& operator <<(ostream& os,const  production & p);

/**
 * operator equating 2 productins
 * @return true iff the 2 symbol sequences are identical
 *          assuming symbols are represented by their references
 */
    bool operator ==( const production &);
private:
#ifndef debug_mode
    vector<const symbol *> symbol_list;

#endif

};

#endif //PARSER_GENERATOR_PRODUCTION_H
