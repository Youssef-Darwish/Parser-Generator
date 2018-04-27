#include "derivation_writer.h"
#include "../terminal.h"
#include "../non_terminal.h"

derivation_writer::derivation_writer() {
    //const string derivation_writer::DERIVATION_PATH = "../out/derivation.txt";
    derivation_file = fstream(DERIVATION_PATH);
    derivation_file.open(DERIVATION_PATH);
}

void derivation_writer::set_start(const symbol *start) {
    non_processed.push_back(start);
    derivation_file << "-> " << start->get_name() << "\n";
}

void derivation_writer::derive_non_terminal(const vector<const symbol *> *symbol_list) {
    non_processed.pop_back();
    for (int i = (int) symbol_list->size() - 1; i >= 0; i--)
        non_processed.push_back((*symbol_list)[i]); // push the production in reverse order
    print_derivation();
}

void derivation_writer::clear_epsilon() {
    non_processed.pop_back();
    print_derivation();
}

void derivation_writer::match(token cur_token) {
    processed.push_back(non_processed.back()->get_name());
    non_processed.pop_back();
    derivation_file << "-- Matching '" << cur_token.name << "'...\n";
}

void derivation_writer::insert_unmatched(token token) {
    derivation_file << "** ERROR: Unmatched token '" << token.name << "' inserted...\n";
}

void derivation_writer::discard_illegal(const non_terminal *top_non_terminal, token cur_token) {
    derivation_file << "** ERROR: Illegal '" << top_non_terminal->get_name() << "' - Discard '" << cur_token.name << "'...\n";
}

void derivation_writer::terminate(exit_status status) {
    switch (status) {
        case FAIL:
            derivation_file << "\n--- Unable to complete parsing ---\n";
            break;
        case SUCCESS_WITH_ERROR:
            derivation_file << "\n--- Parsing Completed with errors ---\n";
            break;
        default:
            derivation_file << "\n--- Parsing Completed Successfully ---\n";
    }
    derivation_file.close(); // closed by default when object is destroyed
}

void derivation_writer::print_derivation() {
    derivation_file << "-> ";
    for (auto processed_token : processed)
        derivation_file << processed_token << "\t";
    for (size_t i = non_processed.size() - 1; i >= 0; i--)
        derivation_file << non_processed[i]->get_name() << "\t";
    derivation_file << "\n";
}
