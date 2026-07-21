#ifndef SYMBOL_H
#define SYMBOL_H

#include<string>
using namespace std;

//It represents the data types present in the language
enum class DataType{
    INT,            //integer
    BOOL,           //boolean
};

//It represents how a variable in the semantic analyzer will look like 
//It will store the name of variable, its data type and whether that variable is initalized or not
struct Symbol{
    string name; //name of variable
    DataType type; // data type of variable
    bool initialized; //initializing status of the variable

    Symbol(const string& name,DataType type,bool initialized){
        this->name=name;
        this->type=type;
        this->initialized=initialized;
    }
};

#endif