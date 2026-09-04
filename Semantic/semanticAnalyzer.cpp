#include<bits/stdc++.h>
#include "semanticAnalyzer.h"
using namespace std;

SemanticAnalyzer::SemanticAnalyzer(){

}

//This function analyses the whole program and decides that the program is semantically verified or not
void SemanticAnalyzer::analyze(AST* root){
    currScope=new Scope(nullptr);
    ProgramNode* program=dynamic_cast<ProgramNode*>(root);
    for(auto function:program->functions){
        collectFunctions(function);
    }
    validateMain();
    for(auto function:program->functions){
        analyzeFunctionBodies(function);
    }
    delete currScope;
}

DataType SemanticAnalyzer::analyzeExpression(AST* node){

    if(FunctionCallNode* callNode=dynamic_cast<FunctionCallNode*>(node)){
        return checkFunctionCall(callNode);
    }

    if(NumberNode* numbernode=dynamic_cast<NumberNode*>(node)){
        return DataType::INT;
    }
    
    if(VariableNode* varnode=dynamic_cast<VariableNode*>(node)){
        string varname=varnode->name;
        Symbol* sym=currScope->lookup(varname);
        if(!sym){
            throw runtime_error("Use of undefined variable: "+varname);
        }
        if(!sym->initialized){
            throw runtime_error("Use of unintialized variable: "+varname);
        }
        return sym->type;
    }

    if(UnaryOpNode* unarynode=dynamic_cast<UnaryOpNode*>(node)){
        DataType type=analyzeExpression(unarynode->exp);
        if(type==DataType::INT && (unarynode->op.type==PLUS || unarynode->op.type==MINUS)){
            return type;
        }else if(type==DataType::BOOL && unarynode->op.type==NOT){
            return type;
        }
        string err="Unary Operator type mismatch";
        throw runtime_error(err);
    }

    if(BinaryOpNode* binarynode=dynamic_cast<BinaryOpNode*>(node)){
        DataType left=analyzeExpression(binarynode->left);
        DataType right=analyzeExpression(binarynode->right);
        if(binarynode->op.type==PLUS || 
          binarynode->op.type==MINUS || 
          binarynode->op.type==MULTIPLY || 
          binarynode->op.type==DIVIDE){
            if(left==DataType::INT && right==DataType::INT){
                return DataType::INT;
            }
        }else if(binarynode->op.type==GREATER ||
                binarynode->op.type==GREATER_EQUAL || 
                binarynode->op.type==LESS || 
                binarynode->op.type==LESS_EQUAL){
            if(left==DataType::INT && right==DataType::INT){
                return DataType::BOOL;
            }
        }else if(binarynode->op.type==EQUAL || binarynode->op.type==NOT_EQUAL){
            if(left==right){
                return DataType::BOOL;
            }
        }else if(binarynode->op.type==AND || binarynode->op.type==OR){
            if(left==DataType::BOOL && right==DataType::BOOL){
                return DataType::BOOL;
            }
        }
        throw runtime_error("Binary Operator Type mismatch");
    }
}

void SemanticAnalyzer::analyzeFunctionBodies(FunctionNode* function){
    FunctionSymbol* funcSym=functionTable.lookup(function->name);
    Scope* oldScope=currScope;
    Scope* newScope=new Scope(currScope);
    for(auto para:funcSym->parameters){
        Symbol sym(para.name,para.type,true);
        if(!newScope->insert(sym)){
            throw runtime_error("Redeclaration of variable:"+sym.name);
        }
    }
    currScope=newScope;
    currFunction=funcSym;
    visit(function->body);
    currScope=oldScope;
    delete newScope;
}

void SemanticAnalyzer::collectFunctions(FunctionNode* functionNode){
    DataType returnType=functionNode->returnType;
    string name=functionNode->name;
    vector<Parameter> parameters;
    for(auto param:functionNode->parameters){
        Parameter para(param->name,param->type);
        parameters.push_back(para);
    }
    FunctionSymbol function(name,returnType,parameters);
    if(!functionTable.insert(function)){
        string error="Redeclaration of function: "+function.name;
        throw runtime_error (error);
    }
} 

void SemanticAnalyzer::checkReturn(ReturnNode* node){
    DataType type=analyzeExpression(node->expression);
    if(currFunction->returnType!=type){
        string error="Return type mismatch\n";
        throw runtime_error(error);
    }
}

void SemanticAnalyzer::validateMain(){
    FunctionSymbol* it=functionTable.lookup("main");
    if(it==nullptr){
        throw runtime_error ("Main function not declared.");
    }
    if(it->returnType!=DataType::INT){
        throw runtime_error ("ReturnType of main() must be int.");
    }
    if(it->parameters.size()!=0){
        throw runtime_error ("No paramter should be passed into the main().");
    }
}

DataType SemanticAnalyzer::checkFunctionCall(FunctionCallNode* functionnode){
    FunctionSymbol* funcSym=functionTable.lookup(functionnode->name);
    if(funcSym==nullptr){
        throw runtime_error(functionnode->name+"() not declared");
    }
    if(functionnode->arguments.size()!=funcSym->parameters.size()){
        string error="In function "+functionnode->name+"()\nExpected "+ to_string(funcSym->parameters.size())+"arguments"+"\nReceived "+to_string(functionnode->arguments.size())+"arguments.";
        throw runtime_error(error);
    }
    int argsize=functionnode->arguments.size();
    for(int i=0;i<argsize;i++){
        DataType argType=analyzeExpression(functionnode->arguments[i]);
        if(argType!=funcSym->parameters[i].type){
            throw runtime_error(to_string(i+1)+"th Arguments type mismatch");
        }
    }
    return funcSym->returnType;
}

//This function visits the statement nodes and semantically verify them if there is something wrong it throws the runtime error
void SemanticAnalyzer::visit(AST* node){

    if(ReturnNode* returnnode=dynamic_cast<ReturnNode*>(node)){
        checkReturn(returnnode);
        return ;
    }

    if(DeclareNode* declarenode=dynamic_cast<DeclareNode*>(node)){
        string varname=declarenode->variable->name;
        Symbol sym(varname,declarenode->type,false);
        if(!currScope->insert(sym)){
            throw runtime_error("Redeclaration of the varible: "+varname);
        }
        if(declarenode->initializer){
            DataType declareType=declarenode->type;
            DataType rhsType=analyzeExpression(declarenode->initializer);
            NumberNode* numnode=dynamic_cast<NumberNode*>(declarenode->initializer);
            if(declareType==rhsType){

            }else if(
            (declareType==DataType::BOOL) && 
            (numnode) && 
            (numnode->value=="0" || numnode->value=="1")
            ){
                 
            }else{
                throw runtime_error("Type Mismatch");
            }
            Symbol* var=currScope->lookup(varname);
            var->initialized=true;
        }
        return ;
    }

    if(AssignNode* assignnode=dynamic_cast<AssignNode*>(node)){
        string varname=assignnode->left->name;
        Symbol* sym=currScope->lookup(varname);
        if(!sym){
            throw runtime_error("Use of undefined variable: "+varname);
        }
        DataType lhsType=sym->type;
        DataType rhsType=analyzeExpression(assignnode->right);
        NumberNode* numnode=dynamic_cast<NumberNode*>(assignnode->right);
        if(lhsType==rhsType){
            
        }else if(
            (lhsType==DataType::BOOL) && 
            (numnode) && 
            (numnode->value=="0" || numnode->value=="1")
        ){
            
        }else{
            throw runtime_error("Type Mismatch");
        }
        sym->initialized=true;
        return ;
    }

    if(BlockNode* blocknode=dynamic_cast<BlockNode*>(node)){
        Scope* oldscope=currScope;
        Scope* newscope=new Scope(currScope);
        currScope=newscope;
        for(auto statement:blocknode->statements){
            visit(statement);
        }
        currScope=oldscope;
        delete newscope;
        return ;
    }

    if(IfNode* ifnode=dynamic_cast<IfNode*>(node)){
        DataType type=analyzeExpression(ifnode->condition);
        if(type!=DataType::BOOL){
            throw runtime_error("Condition in the if statment should be BOOL");
        }
        visit(ifnode->condition);
        visit(ifnode->thenbody);
        if(ifnode->elsebody){
            visit(ifnode->elsebody);
        }
        return ;
    }

    if(WhileNode* whilenode=dynamic_cast<WhileNode*>(node)){
        DataType type=analyzeExpression(whilenode->condition);
        if(type!=DataType::BOOL){
            throw runtime_error("Condition in the while loop should be BOOL");
        }
        visit(whilenode->condition);
        visit(whilenode->body);
        return ;
    }

    if(ProgramNode* program=dynamic_cast<ProgramNode*>(node)){
        for(auto function:program->functions){
            visit(function);
        }
        return ;
    }

}

