#include <iostream>

#define  debug_mode
#include "symbol.h"
#include "production.h"
#include "non_terminal.h"
#include "terminal.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    symbol *A = new non_terminal("A");

    return 0;
}