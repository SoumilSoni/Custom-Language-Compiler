#include<bits/stdc++.h>
#include "runtimeFunctionTable.h"
using namespace std;

bool RuntimeFunctionTable::insert(const string &name,FunctionNode* functionNode){
    bool result=functions.insert({name,functionNode}).second;
    return result;
}

FunctionNode* RuntimeFunctionTable::lookup(const string &name){
    auto it=functions.find(name);
    if(it==functions.end()){
        return nullptr;
    }
    return it->second;
}