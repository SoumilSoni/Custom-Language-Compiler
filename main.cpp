#include<bits/stdc++.h>
#include "Parser/parser.h"
#include "Interpreter/interpreter.h"
#include "Semantic/semanticAnalyzer.h"
using namespace std;

int main(){
    cout<<"Compiler Calculator Project\n";
    Lexer lexer(
            "int x = 10;"
            "int y = 20;"
            "bool flag = x < y;"
            "if (flag) {"
                "x = x + y;"
            "}"
            "while (x > 0) {"
                "x = x - 5;"
            "}"
            );
    Parser parser(lexer);
    AST* root=parser.parse();
    cout<<"Parsed successfully!!\n";
    SemanticAnalyzer semanticanalyzer;
    semanticanalyzer.analyze(root);
    cout<<"Program semantically verified!!\n";
    Interpreter interpreter;
    int result=interpreter.visit(root);
    cout<<"Evaluated successfully!!\n";
    cout<<"Result: "<<result<<'\n';
    return 0;
}