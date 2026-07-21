#include<bits/stdc++.h>
#include "semanticAnalyzer.h"
using namespace std;

SemanticAnalyzer::SemanticAnalyzer(){

}

//This function analyses the whole program and decides that the program is semantically verified or not
void SemanticAnalyzer::analyze(AST* root){
    currScope=new Scope(nullptr);
    visit(root);
    delete currScope;
}

DataType SemanticAnalyzer::analyzeExpression(AST* node){

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

//This function visits the statement nodes and semantically verify them if there is something wrong it throws the runtime error
void SemanticAnalyzer::visit(AST* node){

    if(DeclareNode* declarenode=dynamic_cast<DeclareNode*>(node)){
        string varname=declarenode->variable->name;
        Symbol sym(varname,declarenode->type,false);
        if(!currScope->insert(sym)){
            throw runtime_error("Redeclaration of the varible: "+varname);
        }
        if(declarenode->initializer){
            DataType declareType=declarenode->type;
            DataType rhsType=analyzeExpression(declarenode->initializer);
            if(declareType!=rhsType){
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
        if(lhsType!=rhsType){
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
        for(auto statement:program->statements){
            visit(statement);
        }
        return ;
    }

}

