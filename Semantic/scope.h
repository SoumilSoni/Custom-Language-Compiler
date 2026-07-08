#ifndef SCOPE_H
#define SCOPE_H

#include<map>
#include "symbol.h"
using namespace std;

class Scope{
private:
    map<string,Symbol> symbols;
    Scope* parent;
public:
    Scope(Scope* parent);
    bool insert(const Symbol& symbol);
    Symbol* lookup(const string &name);
};
#endif