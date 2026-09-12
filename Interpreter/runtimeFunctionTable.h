#ifndef RUNTIMEFUNCTIONTABLE_H
#define RUNTIMEFUNCTIONTABLE_H

#include<bits/stdc++.h>
#include "../Ast/ast.h"
using namespace std;

class RuntimeFunctionTable{
private:
    map<string,FunctionNode*> functions;
public:
    bool insert(const string &name,FunctionNode* functionNode);
    FunctionNode* lookup(const string &name);
};

#endif