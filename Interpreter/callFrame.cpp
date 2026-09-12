#include<bits/stdc++.h>
#include "callFrame.h"
using namespace std;

bool CallFrame::insert(const string &name,RuntimeValue value){
    bool result=variables.insert({name,value}).second;
    return result;
}

RuntimeValue* CallFrame::lookup(const string &name){
    auto it=variables.find(name);
    return it==variables.end()?nullptr:&it->second;
}

