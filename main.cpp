#include<bits/stdc++.h>
#include "Parser/parser.h"
#include "Interpreter/interpreter.h"
#include "Semantic/semanticAnalyzer.h"
using namespace std;

int main(){
    cout<<"Compiler Calculator Project\n";
    Lexer lexer(
        "bool max(int a,int b){"
            "return a>b;"
        "}"
        "int main(){"
            "int a=6;"
            "int b=5;"
            "if(max(a,b)){"
                "return a;"
            "}"
            "return b;"
        "}"
        );
    Parser parser(lexer);
    AST* root=parser.parse();
    cout<<"Parsed successfully!!\n";
    SemanticAnalyzer semanticanalyzer;
    semanticanalyzer.analyze(root);
    cout<<"Program semantically verified!!\n";
    Interpreter interpreter;
    int result=interpreter.interpret(root);
    cout<<"Evaluated successfully!!\n";
    cout<<"Result: "<<result<<'\n';
    return 0;
}

// g++ main.cpp Lexer/lexer.cpp Parser/parser.cpp Semantic/scope.cpp Semantic/functionTable.cpp Semantic/semanticAnalyzer.cpp Interpreter/callFrame.cpp  Interpreter/runtimeFunctionTable.cpp Interpreter/interpreter.cpp -o compiler