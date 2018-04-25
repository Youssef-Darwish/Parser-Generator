//
// Created by youssef on 25/04/18.
//

#include "first_follow_wrapper.h"


first_follow_wrapper::first_follow_wrapper(map<symbol *, set<token> *> first,
                                           map<symbol *, set<token> *> follow) {
    this->first_set_map = first;
    this->follow_set_map = follow;

}

set<token> *first_follow_wrapper::get_first(non_terminal *sym) {
    if (first_set_map.count(sym)) {
        return first_set_map[sym];
    } else {
        return new set<token>();
    }

}

set<token> *first_follow_wrapper::get_follow(non_terminal *sym) {
    if (follow_set_map.count(sym)) {
        return follow_set_map[sym];
    } else {
        return new set<token>();
    }
}