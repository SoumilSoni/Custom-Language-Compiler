#include<bits/stdc++.h>
#include "functionTable.h"
using namespace std;

FunctionTable::FunctionTable(){
    
}
bool FunctionTable::insert(const FunctionSymbol &function){
    return functions.insert({function.name,function}).second;
}

FunctionSymbol* FunctionTable::lookup(const string &name){
    auto it=functions.find(name);
    if(it==functions.end()){
        return nullptr;
    }
    return &(it->second);
}
