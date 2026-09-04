#ifndef SEMANICANALYSER_h
#define SEMANTICANALYSER_H

#include "scope.h"
#include "../Ast/ast.h"
#include "functionSymbol.h"
#include "functionTable.h"
using namespace std;

//It defines how a semantic analyzer will look like its attributes and behaviour
class SemanticAnalyzer{
private:
    Scope* currScope; //It points to the current scope of the program
    FunctionTable functionTable;
    FunctionSymbol* currFunction;
    void visit(AST* node); //It visit the statement nodes of the program in the AST and check they are semantically correct or not
    void collectFunctions(FunctionNode* functionNode);
    void analyzeFunctionBodies(FunctionNode* function);
    void validateMain();
    void checkReturn(ReturnNode* node);
    DataType checkFunctionCall(FunctionCallNode* functionnode);
    DataType analyzeExpression(AST* node); //It visit to the expression evaluating nodes of the program in the AST and return the Data type of the final evaluated expression of that node
public:  
    SemanticAnalyzer();
    void analyze(AST* root); //It analyses the whole AST and call visit() helper function to analyze the whole AST
};

#endif

/* 
    visit()
        -> DeclareNode 
        -> AssignNode
        -> BlockNode
        -> IfNode
        -> WhileNode
        -> ProgramNode

        
    analyzeExpression()
        -> NumberNode()
        -> VariableNode()
        -> UnaryOpNode()
        -> BinaryOpNode()
*/ 
