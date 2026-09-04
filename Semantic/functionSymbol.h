#ifndef FUNCTION_SYMBOL_H
#define FUNCTION_SYMBOL_H

#include<bits/stdc++.h>
#include "symbol.h"
using namespace std;

struct Parameter{
    string name;
    DataType type;
    Parameter(const string &name,DataType type){
        this->name=name;
        this->type=type;
    }
};

struct FunctionSymbol{
    string name;
    DataType returnType;
    vector<Parameter> parameters;
    FunctionSymbol(const string &name,DataType returnType, vector<Parameter> &parameters){
        this->name=name;
        this->returnType=returnType;
        this->parameters=parameters;
    }
};
#endif