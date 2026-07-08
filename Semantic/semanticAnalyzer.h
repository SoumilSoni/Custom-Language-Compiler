#ifndef SEMANICANALYSER_h
#define SEMANTICANALYSER_H

#include "scope.h"
#include "../Ast/ast.h"
using namespace std;

class SemanticAnalyzer{
private:
    Scope* currScope;
    void visit(AST* node);
    DataType analyzeExpression(AST* node);
public:  
    SemanticAnalyzer();
    void analyze(AST* root);
};

#endif