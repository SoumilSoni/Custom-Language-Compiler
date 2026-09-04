#include<bits/stdc++.h>
#include "Parser/parser.h"
#include "Interpreter/interpreter.h"
#include "Semantic/semanticAnalyzer.h"
using namespace std;

int main(){
    cout<<"Compiler Calculator Project\n";
    Lexer lexer(
        // "int main(){"
        //     "int x = 10;"
        //     "int y = 20;"
        //     "bool flag = x < y;"
        //     "if (flag) {"
        //         "y = x + y;"
        //     "}"
        //     "while (x > 0) {"
        //         "x = x - 5;"
        //     "}"
        //     "y+x;"
        // "}"
        // "int add(int a,int b,int c){"
        //         "return a+b+c;"
        //     "}"
        // "int main(){"
        //     "int a=10;"
        //     "int b=a+6;"
        //     "return add(add(0,1,a),b,3*12+9);"
        // "}"
        "int add(int a, int b) {"
            "return a + b;"
        "}"

        "int doubleIt(int x) {"
            "return add(x,x);"
        "}"

        "int main() {"
            "return doubleIt(10);"
        "}"
        );
    Parser parser(lexer);
    AST* root=parser.parse();
    cout<<"Parsed successfully!!\n";
    SemanticAnalyzer semanticanalyzer;
    semanticanalyzer.analyze(root);
    cout<<"Program semantically verified!!\n";
    // Interpreter interpreter;
    // int result=interpreter.visit(root);
    // cout<<"Evaluated successfully!!\n";
    // cout<<"Result: "<<result<<'\n';
    return 0;
}