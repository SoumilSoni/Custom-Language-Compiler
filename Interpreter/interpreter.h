#ifndef INTERPRETER_H
#define INTERPRETER_H

#include<string>
#include<map>
#include "../Ast/ast.h"
#include "callFrame.h"
#include "runtimeFunctionTable.h"

using namespace std;
//  Interpreter is used to traverse the syntax tree and recursively evaluate the value of the expression
class Interpreter{
private:
    map<string,RuntimeValue> variables; //This map is used to store names of variable names with their respective runtime values.(It works as a symbol table).
    CallFrame* currFrame;
    RuntimeFunctionTable functionTable;
    void collectFunctions(AST* root);
    int executeFunction(AST* node,bool &returned);
    int callFunction(FunctionNode* function,vector<AST*> arguments);
    int visit(AST* node); //this function identifies what type of node is passed to it and evaluate the value accordingly in a recursive manner.
public:
    Interpreter();
    int interpret(AST* root);
};
#endif