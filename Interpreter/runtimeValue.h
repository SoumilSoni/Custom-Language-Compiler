#ifndef RUNTIMEVALUE_H
#define RUNTIMEVALUE_H

#include<bits/stdc++.h>
#include "../Semantic/symbol.h"
using namespace std;

struct RuntimeValue{
    DataType type;
    int value;
    bool initialized;
    RuntimeValue(DataType type,int value,bool initialized){
        this->type=type;
        this->value=value;
        this->initialized=initialized;
    }
};

#endif