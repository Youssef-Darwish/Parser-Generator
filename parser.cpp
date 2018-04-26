#include "parser.h"
#include "production.h"
#include "terminal.h"
#include "predictive_table.h"

parser::parser(predictive_table *table) {
    this->table = table;
    cur_token = new token("epsilon");
    // TODO: this->lexical_analyzer = lexical_analyzer;
}

void parser::parse() {
    parser_stack.push(&terminal::end_terminal);
    parser_stack.push((const symbol*)table->get_start());

    // TODO: if Analyzer->has_next(); i.e, src file is not empty, o.w: ERROR
    *cur_token = token(""); // TODO: lexical_analyzer->next_token()
    while (!parser_stack.empty())
        parser_stack.top()->accept(this);
}

void parser::process(const terminal *top) {
    parser_stack.pop();
    if (top == &terminal::epsilon)
        return;
    if (top->get_token() == *cur_token) {
        if (*cur_token == token("$")) { // Done parsing
            // TODO: Message: Parsing Completed Successfully
            cout << "\nParsing Completed Successfully.\n";
        } else { // token match
            *cur_token = token(""); // TODO: lexical_analyzer->next_token()
        }
    } else { // ERROR
        // TODO: ERROR -> Message: Unmatched terminal (top_terminal->get_token()->get_string()).. Inserted
    }
}

void parser::process(const non_terminal *top) {
    entry_status status = table->get_entry_status(top, *cur_token);

    production top_production = table->get_next_production(top, *cur_token);

     vector<const symbol *> symbol_list;
    switch (status) {
        case VALID :
            parser_stack.pop();
            symbol_list = top_production.get_symbol_list();
            for (int i = (int) symbol_list.size() - 1; i >= 0; i--)
                parser_stack.push((symbol_list)[i]); // push the production in reverse order
            break;
        case SYNCH:
            parser_stack.pop();
            break;
        case ERROR:
            // TODO: ERROR -> Message: Illegal (top_non_terminal->get_name()) - Discard (cur_token->get_string())
            *cur_token = token(""); // TODO: lexical_analyzer->next_token()
    }
}
