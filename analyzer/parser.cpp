#include "parser.h"
#include "../terminal.h"
#include "../production.h"

vector<string> tokens = {"int", "id", ";", "id", "assign", "num", ";", "if", "(", "id", "relop", "num", ")", "{", "id", "assign", "num", ";", "}",
                         "else" ,"{","id","assign","-","id",";","}","$"};
int cur = -1;

parser::parser(predictive_table *table):cur_token("") {
    this->table = table;
    // TODO: this->lexical_analyzer = lexical_analyzer;
    error = false;
}

void parser::parse() {
    parser_stack.push(&terminal::end_terminal);
    parser_stack.push((const symbol*) table->get_start());
    deriver.set_start((const symbol*) table->get_start());

    // TODO: if Analyzer->has_next(); i.e, src file is not empty, o.w: ERROR
    std::cout << "here\n";
    cur_token = token(tokens[++cur]); // TODO: lexical_analyzer->next_token()
    std::cout << "here\n";

    while (!parser_stack.empty())
        parser_stack.top()->accept(this);

    if (error) // TODO: if Analyzer->has_next(); i.e; more tokens that could not be parsed
        deriver.terminate(exit_status::FAIL);
    else if (error)
        deriver.terminate(exit_status::SUCCESS_WITH_ERROR);
}

void parser::process(const terminal *top) {
    parser_stack.pop();
    if (top->get_name() == terminal::epsilon.get_name()) {
        deriver.clear_epsilon();
    } else if (top->get_token() == cur_token) {
        if (cur_token.name == terminal::end_terminal.get_token().name) { // Done parsing
            if (!error)
                deriver.terminate(exit_status::SUCCESS);
            else
                deriver.terminate(exit_status::FAIL);
        } else { // token match
            deriver.match(cur_token);
            cur_token = token(tokens[++cur]); // TODO: lexical_analyzer->next_token()
        }
    } else { // ERROR
        error = true;
        deriver.insert_unmatched(cur_token);
    }
}

void parser::process(const non_terminal *top) {
    entry_status status = table->get_entry_status(top, cur_token);
    switch (status) {
        case VALID : {
            parser_stack.pop();
            production top_production = table->get_next_production(top, cur_token);
            vector<const symbol *> symbol_list = top_production.get_symbol_list();
            deriver.derive_non_terminal(&symbol_list);
            for (int i = (int) symbol_list.size() - 1; i >= 0; i--)
                parser_stack.push((symbol_list)[i]); // push the production in reverse order
            break;
        }
        case SYNCH: {
            parser_stack.pop();
            break;
        }
        case ERROR: {
            error = true;
            deriver.discard_illegal(top, cur_token);
            cur_token = token(tokens[++cur]); // TODO: lexical_analyzer->next_token()

        }
    }
}
