#include<bits/stdc++.h>
#include "Parser/parser.h"
#include "Interpreter/interpreter.h"
#include "Semantic/semanticAnalyzer.h"
using namespace std;

int main(){
    cout<<"Compiler Calculator Project\n";
    Lexer lexer(
            "bool x;"
            "x=4;"
            );
Parser parser(lexer);
AST* root=parser.parse();
SemanticAnalyzer semanticanalyzer;
semanticanalyzer.analyze(root);
cout << "Program semantically verified!!\n";
    return 0;
}