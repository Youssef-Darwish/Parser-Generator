#ifndef PARSER_GENERATOR_DERIVATION_WRITER_H
#define PARSER_GENERATOR_DERIVATION_WRITER_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using std::vector;
using std::string;
using std::fstream;

class token;

class symbol;

class non_terminal;

enum exit_status {
    SUCCESS,
    SUCCESS_WITH_ERROR,
    FAIL
};

class derivation_writer {
public:
    derivation_writer();

    void set_start(const symbol *);

    void derive_non_terminal(const vector<const symbol *> *);

    void clear_epsilon();

    void match(token);

    void insert_unmatched(token);

    void discard_illegal(const non_terminal *, token);

    void terminate(exit_status);

private:
    const string DERIVATION_PATH = "../out/derivation.txt";
    fstream derivation_file;
    vector<string> processed;
    vector<const symbol *> non_processed;

    void print_derivation();
};


#endif
