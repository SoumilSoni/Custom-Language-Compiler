#include<bits/stdc++.h>
#include "../Ast/ast.h"
#include "interpreter.h"
using namespace std;

//dynamic_cast is used to check the node belong to numberNode class or binaryOpNode class
// dynamic_cast in C++ is used for safe type conversion in inheritance hierarchies, mainly with polymorphism

Interpreter::Interpreter(){
    currFrame=NULL;
}

void Interpreter::collectFunctions(AST* root){
    ProgramNode* program=dynamic_cast<ProgramNode*>(root);
    for(auto function:program->functions){
        if(!functionTable.insert(function->name,function)){
            throw runtime_error ("Redeclaration of "+function->name+"()");
        }
    }
}

int Interpreter::executeFunction(AST* node,bool &returned){

    if(ReturnNode* returnNode=dynamic_cast<ReturnNode*>(node)){
        int result=visit(returnNode->expression);
        returned=true;
        return result;
    }

    if(BlockNode* block=dynamic_cast<BlockNode*>(node)){
        for(auto statement:block->statements){
            int result=executeFunction(statement,returned);
            if(returned){
                return result;
            }
        }
    }

    if(IfNode* ifnode=dynamic_cast<IfNode*>(node)){
        int conditionResult=visit(ifnode->condition);
        if(conditionResult){
            int result=executeFunction(ifnode->thenbody,returned);
            if(returned){
                return result;
            }
        }else if(ifnode->elsebody!=NULL){
            int result=executeFunction(ifnode->elsebody,returned);
            if(returned){
                return result;
            }
        }
        return 0;
    }

    if(WhileNode* whilenode=dynamic_cast<WhileNode*>(node)){
        while(visit(whilenode->condition)){
            int result=executeFunction(whilenode->body,returned);
            if(returned){
                return result;
            }
        }
        return 0;
    }

    return visit(node);
}

int Interpreter::callFunction(FunctionNode* function,vector<AST*> arguments){
    string funcName=function->name;
    vector<int> values;
    for(auto exp:arguments){
        values.push_back(visit(exp));
    }
    CallFrame* newFrame=new CallFrame();
    for(int i=0;i<function->parameters.size();i++){
        DataType datatype=function->parameters[i]->type;
        int val=values[i];
        string paraName=function->parameters[i]->name;
        RuntimeValue runtimeValue(datatype,val,true);
        newFrame->insert(paraName,runtimeValue);
    }
    CallFrame* previousFrame=currFrame;
    currFrame=newFrame;
    bool returned=false;
    int returnValue=executeFunction(function->body,returned);
    currFrame=previousFrame;
    delete newFrame;
    return returnValue;

} 

int Interpreter::visit(AST* node){

    if(NumberNode* number=dynamic_cast<NumberNode*>(node)){
        return stoi(number->value);
    }
    //If a variable node comes it checks in the symbol table if it is stored there it returns the value else it throws error
    if(VariableNode* var=dynamic_cast<VariableNode*>(node)){
        auto it=currFrame->lookup(var->name);
        if(it==nullptr){
            throw runtime_error("Undefined variable: "+var->name);
        }
        if(!it->initialized){
            throw runtime_error("Accessing Unitialialized variable: "+var->name);
        }

        return it->value;
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
        for(AST* function:program->functions){
            result=visit(function);
        }
        return result;
    }
    
    if(FunctionCallNode* function=dynamic_cast<FunctionCallNode*>(node)){
        FunctionNode* functionNode=functionTable.lookup(function->name);
        if(functionNode==nullptr){
            throw runtime_error("Undefined Function"+function->name+"()");
        }
        return callFunction(functionNode,function->arguments);
    }

    if(DeclareNode* declarenode=dynamic_cast<DeclareNode*>(node)){
        RuntimeValue var(declarenode->type,0,false);
        int result=0;
        if(declarenode->initializer){
            result=visit(declarenode->initializer);
            var.value=result;
            var.initialized=true;
        }
        currFrame->insert(declarenode->variable->name,var);
        return result;
    }

    //It assigns the value to the variable (i.e by updating the symbol table) and also returns the evaluated value.
    if(AssignNode* assign=dynamic_cast<AssignNode*>(node)){
        int result=visit(assign->right); //evaluate the expression
        auto it=currFrame->lookup(assign->left->name);
        if(it==nullptr){
            throw runtime_error("Undefined Variable: "+assign->left->name);
        }
        it->value=result;//update the symbol table
        it->initialized=true;
        return it->value;//return the evaluated value
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

int Interpreter::interpret(AST* root){
    collectFunctions(root);
    FunctionNode* mainFunction=functionTable.lookup("main");
    if(mainFunction==nullptr){
        throw runtime_error("main Function not found!");
    }
    return callFunction(mainFunction,{});
}
