#include <bits/utmp.h>
#include "parser.h"
#include "../terminal.h"
#include "../production.h"

using derivation_writer::exit_status;

parser::parser(predictive_table *table) {
    this->table = table;
    // TODO: this->lexical_analyzer = lexical_analyzer;
    error = false;
}

void parser::parse() {
    parser_stack.push(&terminal::end_terminal);
    parser_stack.push(table->get_start());
    deriver.set_start(table->get_start());

    // TODO: if Analyzer->has_next(); i.e, src file is not empty, o.w: ERROR
    cur_token = token(""); // TODO: lexical_analyzer->next_token()
    while (!parser_stack.empty())
        parser_stack.top()->accept(this);
    if (true) // TODO: if Analyzer->has_next(); i.e; more tokens that could not be parsed
        deriver.terminate(exit_status::FAIL);
    else if (error)
        deriver.terminate(exit_status::SUCCESS_WITH_ERROR);
}

void parser::process(const terminal *top) {
    parser_stack.pop();
    if (top == &terminal::epsilon) {
        deriver.clear_epsilon();
    } else if (top->get_token() == cur_token) {
        if (cur_token == terminal::end_terminal.get_token()) { // Done parsing
            if (!error)
                deriver.terminate(exit_status::SUCCESS);
        } else { // token match
            deriver.match(cur_token);
            cur_token = token(""); // TODO: lexical_analyzer->next_token()
        }
    } else { // ERROR
        error = true;
        deriver.insert_unmatched(cur_token);
    }
}

void parser::process(const non_terminal *top) {
    entry_status status = table->get_entry_status(top, cur_token);
    switch (status) {
        case VALID :
            parser_stack.pop();
            production top_production = table->get_next_production(top, cur_token);
            const vector<const symbol *> *symbol_list = top_production.get_symbol_list();
            deriver.derive_non_terminal(symbol_list);
            for (int i = (int) symbol_list->size() - 1; i >= 0; i--)
                parser_stack.push((*symbol_list)[i]); // push the production in reverse order
            break;
        case SYNCH:
            parser_stack.pop();
            break;
        case ERROR:
            error = true;
            deriver.discard_illegal(top, cur_token);
            cur_token = token(""); // TODO: lexical_analyzer->next_token()
    }
}
