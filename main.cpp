#include <iostream>

#define  debug_mode

#include "symbol.h"
#include "non_terminal.h"
#include "production.h"
#include "terminal.h"
#include "first_follow_generator.h"

#ifdef debug_mode
const terminal terminal::epsilon = terminal(eps);
#endif

int main() {

    non_terminal *E = new non_terminal("E");

    non_terminal *E_dash = new non_terminal("E`");
    non_terminal *T = new non_terminal("T");
    non_terminal *T_dash = new non_terminal("T`");
    non_terminal *F = new non_terminal("F");
    production *prod = new production();

    terminal *asterisk = new terminal(token("*"));
    terminal *plus = new terminal(token("+"));
    terminal *id = new terminal(token("id"));
    terminal *open_brack = new terminal(token("("));
    terminal *close_brack = new terminal(token(")"));
    const terminal * eps = &terminal::epsilon;

    prod->symbol_list.push_back((symbol *) T);
//
    prod->symbol_list.push_back((symbol *) E_dash);
    E->add_production(*prod);
    prod->symbol_list.clear();
    production *prod1 = new production();
    prod1->symbol_list.push_back((symbol *) plus);
    prod1->symbol_list.push_back((symbol *) T);
    prod1->symbol_list.push_back((symbol *) E_dash);
    E_dash->add_production(*prod1);

    prod->symbol_list.clear();
    prod->symbol_list.push_back((symbol *) eps);

    E_dash->add_production(*prod);

    prod->symbol_list.clear();
    prod->symbol_list.push_back((symbol *) F);
    prod->symbol_list.push_back((symbol *) T_dash);

    T->add_production(*prod);


    prod->symbol_list.clear();




    prod->symbol_list.push_back((symbol *) asterisk);
    prod->symbol_list.push_back((symbol *) F);
    prod->symbol_list.push_back((symbol *) T_dash);

    T_dash->add_production(*prod);
    prod->symbol_list.clear();

    prod->symbol_list.push_back((symbol *) eps);

    T_dash->add_production(*prod);

    prod->symbol_list.clear();

    prod->symbol_list.push_back((symbol *) open_brack);
    prod->symbol_list.push_back((symbol *) E);
    prod->symbol_list.push_back((symbol *) close_brack);

    F->add_production(*prod);
    prod->symbol_list.clear();
    prod->symbol_list.push_back((symbol *) id);
    F->add_production(*prod);

    vector<non_terminal *> rec;
    rec.push_back(E);
    rec.push_back(E_dash);
    rec.push_back(T);
    rec.push_back(T_dash);
    rec.push_back(F);

    first_follow_generator *generator = new first_follow_generator(rec);
//
    generator->start_first_calculations();
    generator->start_follow_calculations();
    generator->print();
    return 0;
}