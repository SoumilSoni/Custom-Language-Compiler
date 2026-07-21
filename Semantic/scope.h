#ifndef SCOPE_H
#define SCOPE_H

#include<map>
#include "symbol.h"
using namespace std;

 // This class is storing the variables of the current scope and helps to find any variable into the current scope and the outer scope
class Scope{
private:
    map<string,Symbol> symbols; // It stores the variable name and its symbol information in the map
    Scope* parent; // It points to the parent scope
public:
    Scope(Scope* parent);
    bool insert(const Symbol& symbol); //This is used to inset variable in the current scope and to check whether that same name variable is declared in that scope earlier or not
    Symbol* lookup(const string &name); //It is used to find the variable in the current and outer scopes and return its refernce of that variable symbol
};
#endif