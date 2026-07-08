#ifndef SYMBOL_H
#define SYMBOL_H

#include<string>
using namespace std;

//It represents the data types present in the language
enum class DataType{
    INT,            //integer
    BOOL,           //boolean
};

struct Symbol{
    string name;
    DataType type;
    bool initialized;

    Symbol(const string& name,DataType type,bool initialized){
        this->name=name;
        this->type=type;
        this->initialized=initialized;
    }
};

#endif