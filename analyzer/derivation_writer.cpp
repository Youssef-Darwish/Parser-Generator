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
    /**/ std::cout << "-> " << start->get_name() << "\n";
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
    /**/ std::cout << "-- Matching '" << cur_token.name << "'\n";
    derivation_file << "-- Matching '" << cur_token.name << "'\n";
}

void derivation_writer::insert_unmatched(token token) {
    /**/ std::cout << "** ERROR: Unmatched token '" << token.name << "' inserted\n";
    derivation_file << "** ERROR: Unmatched token '" << token.name << "' inserted\n";
}

void derivation_writer::discard_illegal(const non_terminal *top_non_terminal, token cur_token) {
    /**/ std::cout << "** ERROR: Illegal '" << top_non_terminal->get_name() << "' - Discard '" << cur_token.name << "'\n";
    derivation_file << "** ERROR: Illegal '" << top_non_terminal->get_name() << "' - Discard '" << cur_token.name << "'\n";
}

void derivation_writer::terminate(exit_status status) {
    switch (status) {
        case FAIL:
            /**/ std::cout << "\n--- Unable to complete parsing ---\n";
            derivation_file << "\n--- Unable to complete parsing ---\n";
            break;
        case SUCCESS_WITH_ERROR:
            /**/ std::cout << "\n--- Parsing Completed with errors ---\n";
            derivation_file << "\n--- Parsing Completed with errors ---\n";
            break;
        default:
            /**/ std::cout << "\n--- Parsing Completed Successfully ---\n";
            derivation_file << "\n--- Parsing Completed Successfully ---\n";
    }
    derivation_file.close(); // closed by default when object is destroyed
}

void derivation_writer::print_derivation() {
    /**/ std::cout << "-> ";
    derivation_file << "-> ";
    for (auto processed_token : processed) {
        /**/ std::cout << processed_token << "\t";
        derivation_file << processed_token << "\t";
    }

    for (long i = non_processed.size() - 1; i >= 0; i--) {
        /**/ std::cout << non_processed[i]->get_name() << "\t";
        derivation_file << non_processed[i]->get_name() << "\t";
    }
    /**/ std::cout << "\n";
    derivation_file << "\n";
}
