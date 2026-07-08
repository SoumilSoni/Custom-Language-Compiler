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

//numberNode is a child class inheriting AST class. This class will be used to represent a number node in the syntax tree.
class numberNode:public AST{
public:
    string value;
    numberNode(string input){
        value=input;
    }
};

// binaryOpNode is a child class inheriting AST class. This class will be representing the binary operator which will have a left and right pointer that will be pointing to the two operands.
class binaryOpNode:public AST{
public:
    AST* left;
    Token op;
    AST* right;
    binaryOpNode(AST* left,Token op, AST* right){
        this->left=left;
        this->op=op;
        this->right=right;
    }
};

//unaryOpNode is a child class inheriting AST class. This class will be representing the unary operator which will have a operator and exp pointer that will be pointing to the expression connected with the unary operator
class unaryOpNode:public AST{
public:
    AST* exp;
    Token op;
    unaryOpNode(Token op,AST* exp){
        this->exp=exp;
        this->op=op;
    }
};

//varialbe Node is a child class inheriting AST class. This class will be representing the variables and store the variable names.
class variableNode:public AST{
public: 
    string name;
    variableNode(const string& name){
        this->name=name;
    }
};

// assignNode is a child class inheriting AST class. This class will be representing '=' node and it will have a left and right pointer in which left pointer is pointing to the variable to which the value has to be assigned and right pointer is pointing to the expression.
class assignNode:public AST{
public: 
    variableNode* left;
    AST* right;
    assignNode(variableNode* left,AST* right){
        this->left=left;
        this->right=right;
    }
};

// programNode is a child class inheriting AST class. This class is representing the entire program. It is having a vector which stores the pointer to the every statement in the program.
class programNode:public AST{
public:
    vector<AST*> statements;
    programNode(vector<AST*> statements){
        this->statements=statements;
    }
};

//blockNode is a child class inherting AST class. This class is representing the different block of codes which is wriitten inside the different if-else statements or loop statements
class blockNode:public AST{
public:
    vector<AST*> statements;
    blockNode(vector<AST*> statements){
        this->statements=statements;
    }
};

//ifNode is a child class inherting AST class. This class is representing the if-else statements. It stores the condition of the if-statement the code inside if-else statement
class ifNode:public AST{
public: 
    AST* condition;
    blockNode* thenbody;
    blockNode* elsebody;
    ifNode(AST* condition,blockNode* thenbody){
        this->condition=condition;
        this->thenbody=thenbody;
        this->elsebody=NULL;
    }
    ifNode(AST* condition,blockNode* thenbody,blockNode* elsebody){
        this->condition=condition;
        this->thenbody=thenbody;
        this->elsebody=elsebody;
    }
};

//whileNode is a child class inherting AST class. This class is representing the while loop. It store the condition of the while loop and the block of code inside the while loop
class whileNode:public AST{
public:
    AST* condition;
    blockNode* body;
    whileNode(AST* condition,blockNode* body){
        this->condition=condition;
        this->body=body;
    }
};

class declareNode:public AST{
public:
    DataType type;
    variableNode* variable;
    AST* initializer;

    declareNode(DataType type,variableNode* variable,AST* initializer=nullptr){
        this->type=type;
        this->variable=variable;
        this->initializer=initializer;
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