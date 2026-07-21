#include<bits/stdc++.h>
#include "../Ast/ast.h"
#include "interpreter.h"
using namespace std;

//dynamic_cast is used to check the node belong to numberNode class or binaryOpNode class
// dynamic_cast in C++ is used for safe type conversion in inheritance hierarchies, mainly with polymorphism
int Interpreter::visit(AST* node){

    if(NumberNode* number=dynamic_cast<NumberNode*>(node)){
        return stoi(number->value);
    }
    //If a variable node comes it checks in the symbol table if it is stored there it returns the value else it throws error
    if(VariableNode* var=dynamic_cast<VariableNode*>(node)){
        auto it=variables.find(var->name);
        if(it==variables.end()){
            throw runtime_error("Undefined variable: "+var->name);
        }
        if(!it->second.initialized){
            throw runtime_error("Accessing Unitialialized variable: "+var->name);
        }

        return it->second.value;
    }

    if(UnaryOpNode* opNode=dynamic_cast<UnaryOpNode*>(node)){
        int value=visit(opNode->exp);
        switch(opNode->op.type){
            case PLUS:
                return value;
            case MINUS:
                return -value;
            case NOT:
                return !value;
            default:
                throw runtime_error("Invalid operator");
        }
    }
    
    if(ProgramNode* program=dynamic_cast<ProgramNode*>(node)){
        int result=0;
        for(AST* statements : program->statements){
            result=visit(statements);
        }
        return result;
    }
    
    if(DeclareNode* declarenode=dynamic_cast<DeclareNode*>(node)){
        RuntimeValue var(declarenode->type,0,false);
        int result=0;
        if(declarenode->initializer){
            result=visit(declarenode->initializer);
            var.value=result;
            var.initialized=true;
        }
        variables.insert({declarenode->variable->name,var});
        return result;
    }
    //It assigns the value to the variable (i.e by updating the symbol table) and also returns the evaluated value.
    if(AssignNode* assign=dynamic_cast<AssignNode*>(node)){
        int result=visit(assign->right); //evaluate the expression
        auto it=variables.find(assign->left->name);
        if(it==variables.end()){
            throw runtime_error("Undefined Variable: "+assign->left->name);
        }
        it->second.value=result;//update the symbol table
        it->second.initialized=true;
        return it->second.value;//return the evaluated value
    }
    
    if(BinaryOpNode* opNode=dynamic_cast<BinaryOpNode*>(node)){
        //These two lines traverse in the tree and return the result after evaluating the left and right subtree
        int LEFT=visit(opNode->left);
        int RIGHT=visit(opNode->right);
        //It handles the operation according to the operator and returns the result
        switch(opNode->op.type){
            case PLUS:
                return LEFT+RIGHT;
            case MINUS:
                return LEFT-RIGHT;
            case MULTIPLY:
                return LEFT*RIGHT;
            case DIVIDE:
                return LEFT/RIGHT;
            case EQUAL:
                return LEFT==RIGHT;
            case NOT_EQUAL:
                return LEFT!=RIGHT;
            case GREATER:
                return LEFT>RIGHT;
            case GREATER_EQUAL:
                return LEFT>=RIGHT;
            case LESS:
                return LEFT<RIGHT;
            case LESS_EQUAL:
                return LEFT<=RIGHT;
            case AND:
                return LEFT&&RIGHT;
            case OR:
                return LEFT||RIGHT;
            default:
                throw runtime_error("Invalid Operator");
        }
    }

    if(IfNode* ifnode=dynamic_cast<IfNode*>(node)){
        if(visit(ifnode->condition)){
            visit(ifnode->thenbody);
        }else if(ifnode->elsebody!=NULL){
            visit(ifnode->elsebody);
        }
        return 0;
    }

    if(WhileNode* whilenode=dynamic_cast<WhileNode*>(node)){
        while(visit(whilenode->condition)){
            visit(whilenode->body);
        }
        return 0;
    }

    if(BlockNode* body=dynamic_cast<BlockNode*>(node)){
        int result=0;
        for(AST* statement:body->statements){
            result=visit(statement);
        }
        return result;
    }

    throw runtime_error("Invalid AST node");
}