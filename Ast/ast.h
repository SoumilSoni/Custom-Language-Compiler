#ifndef AST_H
#define AST_H

#include<string>
#include<vector>
#include "../Lexer/token.h"
#include "../Semantic/symbol.h"
using namespace std;
//AST is the base class of AST(Abstract Syntax Tree) which will be inherited by numberNode, binaryOpNode, unaryOpNode, etc...
// These classes will be used to build syntax tree nodes.
// We need a base AST class because a parser should return a generic AST node not a specific type of node.
class AST{
public:
    virtual ~AST(){} //It is a virtual destructor
    //using virtual because it use correct destructor based on actual object type
};

//NumberNode is a child class inheriting AST class. This class will be used to represent a number node in the syntax tree.
class NumberNode:public AST{
public:
    string value;
    NumberNode(string input){
        value=input;
    }
};

//BinaryOpNode is a child class inheriting AST class. This class will be representing the binary operator which will have a left and right pointer that will be pointing to the two operands.
class BinaryOpNode:public AST{
public:
    AST* left;
    Token op;
    AST* right;
    BinaryOpNode(AST* left,Token op, AST* right){
        this->left=left;
        this->op=op;
        this->right=right;
    }
};

//UnaryOpNode is a child class inheriting AST class. This class will be representing the unary operator which will have a operator and exp pointer that will be pointing to the expression connected with the unary operator
class UnaryOpNode:public AST{
public:
    AST* exp;
    Token op;
    UnaryOpNode(Token op,AST* exp){
        this->exp=exp;
        this->op=op;
    }
};

//Varialbe Node is a child class inheriting AST class. This class will be representing the variables and store the variable names.
class VariableNode:public AST{
public: 
    string name;
    VariableNode(const string& name){
        this->name=name;
    }
};

//AssignNode is a child class inheriting AST class. This class will be representing '=' node and it will have a left and right pointer in which left pointer is pointing to the variable to which the value has to be assigned and right pointer is pointing to the expression.
class AssignNode:public AST{
public: 
    VariableNode* left;
    AST* right;
    AssignNode(VariableNode* left,AST* right){
        this->left=left;
        this->right=right;
    }
};


class ParameterNode:public AST{
public: 
    DataType type;
    string name;
    ParameterNode(DataType type,const string &name){
        this->type=type;
        this->name=name;
    }
};

//BlockNode is a child class inherting AST class. This class is representing the different block of codes which is wriitten inside the different if-else statements or loop statements
class BlockNode:public AST{
public:
    vector<AST*> statements;
    BlockNode(vector<AST*> statements){
        this->statements=statements;
    }
};

class FunctionNode:public AST{
public:
    DataType returnType;
    string name;
    vector<ParameterNode*> parameters;
    BlockNode* body;
    FunctionNode(DataType returnType,const string &name,vector<ParameterNode*> &parameters,BlockNode* body){
        this->returnType=returnType;
        this->name=name;
        this->parameters=parameters;
        this->body=body;
    }
};

//ProgramNode is a child class inheriting AST class. This class is representing the entire program. It is having a vector which stores the pointer to the every statement in the program.
class ProgramNode:public AST{
public:
    vector<FunctionNode*> functions;
    ProgramNode(vector<FunctionNode*> functions){
        this->functions=functions;
    }
};




//IfNode is a child class inherting AST class. This class is representing the if-else statements. It stores the condition of the if-statement the code inside if-else statement
class IfNode:public AST{
public: 
    AST* condition;
    BlockNode* thenbody;
    BlockNode* elsebody;
    IfNode(AST* condition,BlockNode* thenbody,BlockNode* elsebody=NULL){
        this->condition=condition;
        this->thenbody=thenbody;
        this->elsebody=elsebody;
    }
};

//WhileNode is a child class inherting AST class. This class is representing the while loop. It store the condition of the while loop and the block of code inside the while loop
class WhileNode:public AST{
public:
    AST* condition;
    BlockNode* body;
    WhileNode(AST* condition,BlockNode* body){
        this->condition=condition;
        this->body=body;
    }
};

//DeclareNode is a child class inherting AST class. This class is representing the declaration statement. It stores the datatype of the variable, the variable and the initializing expression
class DeclareNode:public AST{
public:
    DataType type;
    VariableNode* variable;
    AST* initializer;

    DeclareNode(DataType type,VariableNode* variable,AST* initializer=nullptr){
        this->type=type;
        this->variable=variable;
        this->initializer=initializer;
    }

};

class ReturnNode:public AST{
public: 
    AST* expression;
    ReturnNode(AST* expression){
        this->expression=expression;
    }
};

class FunctionCallNode:public AST{
public:     
    string name;
    vector<AST*> arguments;
    FunctionCallNode(string name,vector<AST*> &arguments){
        this->name=name;
        this->arguments=arguments;
    }
};

#endif

/*
                                    ------Base Classes------
                                    1. numberNode class
                                    2. binaryOpNode class
                                    3. unaryOpNode class
                                    4. variableNode class
                                    5. assignNode class
                                    6. programNode class
                                    7. blockNode class
                                    8. ifNode class
                                    9. whileNode class

*/