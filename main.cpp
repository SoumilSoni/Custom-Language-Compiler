#include<bits/stdc++.h>
#include "Parser/parser.h"
#include "Interpreter/interpreter.h"
#include "Semantic/semanticAnalyzer.h"
using namespace std;

int main(){
    cout<<"Compiler Calculator Project\n";
    Lexer lexer(
        "int max(int a,int b){"
            "int ta=a;"
            "int tb=b;"
            "while(ta>0 && tb>0){"
                "ta=ta-1;"
                "tb=tb-1;"
                "if(ta==0){"
                    "return b;"
                "}"
                "if(tb==0){"
                    "return a;"
                "}"
            "}"
            "return a;"
        "}"
        "int main(){"
            "return max(6,5);"
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