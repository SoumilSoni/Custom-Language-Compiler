#ifndef CALLFRAME_H
#define CALLFRAME_H

#include<bits/stdc++.h>
#include "runtimeValue.h"
using namespace std;

class CallFrame{
private:
    map<string,RuntimeValue> variables;
public:
    bool insert(const string &name,RuntimeValue value);
    RuntimeValue* lookup(const string &name);
};
#endif