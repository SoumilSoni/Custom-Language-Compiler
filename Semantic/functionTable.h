#ifndef FUNCTION_TABLE_H
#define FUNCTION_TABLE_H

#include "functionSymbol.h"
#include<bits/stdc++.h>
using namespace std;

class FunctionTable{
private:
    map<string,FunctionSymbol> functions;
public:
    FunctionTable();
    bool insert(const FunctionSymbol &function);
    FunctionSymbol* lookup(const string &name);
};
#endif