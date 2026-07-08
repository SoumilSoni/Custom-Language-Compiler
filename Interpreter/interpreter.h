#ifndef INTERPRETER_H
#define INTERPRETER_H

#include<string>
#include<map>
#include "../Ast/ast.h"
using namespace std;
//  Interpreter is used to traverse the syntax tree and recursively evaluate the value of the expression

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
class Interpreter{
private:
    map<string,RuntimeValue> variables; //This map is used to store value of variable names with their respective value. (It works as a symbol table).
public:
    int visit(AST* node); //this function identifies what type of node is passed to it and evaluate the value accordingly in a recursive manner.
};
#endif