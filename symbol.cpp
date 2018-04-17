//
// Created by youssef on 17/04/18.
//

#include "symbol.h"

bool symbol::operator==(const symbol & sym) {
        return this->symbol_name == sym.symbol_name;
}

