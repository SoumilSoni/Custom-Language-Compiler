#ifndef INTERPRETER_H
#define INTERPRETER_H

#include<vector>
#include<string>
#include<map>
#include "../Ast/ast.h"
#include "callFrame.h"
#include "runtimeFunctionTable.h"

// Executes the program by traversing and evaluating the AST.
class Interpreter{
private:
    // Current runtime call frame.
    // Non-owning pointer; points to the frame currently being executed.
    CallFrame* currFrame; 

    // Stores function definitions for runtime function lookup.
    RuntimeFunctionTable functionTable; 

    // Collects all function definitions from the AST.
    void collectFunctions(AST* root);

     // Executes statements that may contain a return statement.
    int executeFunction(AST* node,bool &returned); 

    // Creates a new call frame and executes a function.
    int callFunction(FunctionNode* function,std::vector<AST*> arguments); 

    // Evaluates an AST node and returns its runtime value.
    int visit(AST* node); 
public:
    Interpreter();

    // Executes the program starting from main().
    int interpret(AST* root);
};
#endif