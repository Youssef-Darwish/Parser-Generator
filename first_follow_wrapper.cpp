//
// Created by youssef on 25/04/18.
//

#include "wrapper.h"


first_follow_wrapper::first_follow_wrapper(map<const symbol *, set<token> *> first,
                                           map<const symbol *, set<token> *> follow) {
    this->first_set_map = first;
    this->follow_set_map = follow;

}

set<token> *first_follow_wrapper::get_first(const symbol  *sym) {
    if (first_set_map.count(sym)) {
        return first_set_map[sym];
    } else {
        return new set<token>();
    }

}

set<token> *first_follow_wrapper::get_follow(const symbol *sym) {
    if (follow_set_map.count(sym)) {
        return follow_set_map[sym];
    } else {
        return new set<token>();
    }
}

ostream& operator <<( ostream&os ,  first_follow_wrapper & t){
   os<< t.first_set_map.size()<<"\n";
   vector <const  symbol*> temp;
   for (auto i:t.first_set_map) {
       temp.push_back(i.first);
//       os<<i.first->get_name()<<" "<<i.second->size()<<".."<<t.get_follow(i.first)->size()<<"..";
   }
//   return os;
   for(int i = 0; i < temp.size();i++) {
       set<token> *fs = t.get_first(temp[i]);
       set<token> *ss = t.get_follow(temp[i]);
       os<<temp[i]->get_name()<<" ::{";
       for(auto it: *fs) {
           os<<it.name<<",";
       }
       os<<"} {";
       for(auto it: *ss) {
           os<<it.name<<",";
       }
       os<<"}\n";

   }
    return  os;
}