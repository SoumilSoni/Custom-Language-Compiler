#include "../Ast/ast.h"
#include "interpreter.h"
using namespace std;

Interpreter::Interpreter(){
    currFrame=nullptr;
}

void Interpreter::collectFunctions(AST* root){
    ProgramNode* program=dynamic_cast<ProgramNode*>(root);
    for(auto function:program->functions){
        if(!functionTable.insert(function->name,function)){
            throw runtime_error ("Function Redeclaration: "+function->name);
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
    if(arguments.size()!=function->parameters.size()){
        string err1="Expected: "+function->parameters.size();
        string err2="Got: "+arguments.size();
        throw runtime_error("Argument coount mismatch in function '"+function->name+"':"+"\n"+err1+'\n'+err2);
    }
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

    if(NumberNode* numberNode=dynamic_cast<NumberNode*>(node)){
        return stoi(numberNode->value);
    }

    if(VariableNode* varNode=dynamic_cast<VariableNode*>(node)){
        auto it=currFrame->lookup(varNode->name);
        if(it==nullptr){
            throw runtime_error("Undefined variable: "+varNode->name);
        }
        if(!it->initialized){
            throw runtime_error("Variable uninitialized: "+varNode->name);
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
                throw runtime_error("Invalid unary operator: "+opNode->op.value);
        }
    }
    
    if(FunctionCallNode* functionCallNode=dynamic_cast<FunctionCallNode*>(node)){
        FunctionNode* functionNode=functionTable.lookup(functionCallNode->name);
        if(functionNode==nullptr){
            throw runtime_error("Undefined Function: "+functionCallNode->name);
        }
        return callFunction(functionNode,functionCallNode->arguments);
    }

    if(DeclareNode* declareNode=dynamic_cast<DeclareNode*>(node)){
        RuntimeValue var(declareNode->type,0,false);
        int result=0;
        if(declareNode->initializer){
            result=visit(declareNode->initializer);
            var.value=result;
            var.initialized=true;
        }
        currFrame->insert(declareNode->variable->name,var);
        return result;
    }

    if(AssignNode* assignNode=dynamic_cast<AssignNode*>(node)){
        int result=visit(assignNode->right);
        auto it=currFrame->lookup(assignNode->left->name);
        if(it==nullptr){
            throw runtime_error("Undefined Variable: "+assignNode->left->name);
        }
        it->value=result;
        it->initialized=true;
        return it->value;
    }
    
    if(BinaryOpNode* opNode=dynamic_cast<BinaryOpNode*>(node)){
        int leftValue=visit(opNode->left);
        int rightValue=visit(opNode->right);
        switch(opNode->op.type){
            case PLUS:
                return leftValue+rightValue;
            case MINUS:
                return leftValue-rightValue;
            case MULTIPLY:
                return leftValue*rightValue;
            case DIVIDE:
                if(rightValue==0){
                    throw runtime_error("Divide by zero");
                }
                return leftValue/rightValue;
            case EQUAL:
                return leftValue==rightValue;
            case NOT_EQUAL:
                return leftValue!=rightValue;
            case GREATER:
                return leftValue>rightValue;
            case GREATER_EQUAL:
                return leftValue>=rightValue;
            case LESS:
                return leftValue<rightValue;
            case LESS_EQUAL:
                return leftValue<=rightValue;
            case AND:
                return leftValue&&rightValue;
            case OR:
                return leftValue||rightValue;
            default:
                throw runtime_error("Invalid Binary Operator: "+opNode->op.value);
        }
    }

    if(IfNode* ifNode=dynamic_cast<IfNode*>(node)){
        if(visit(ifNode->condition)){
            visit(ifNode->thenbody);
        }else if(ifNode->elsebody!=NULL){
            visit(ifNode->elsebody);
        }
        return 0;
    }

    if(WhileNode* whileNode=dynamic_cast<WhileNode*>(node)){
        while(visit(whileNode->condition)){
            visit(whileNode->body);
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
