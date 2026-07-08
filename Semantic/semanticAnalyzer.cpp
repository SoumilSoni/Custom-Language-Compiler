#include<bits/stdc++.h>
#include "semanticAnalyzer.h"
using namespace std;

SemanticAnalyzer::SemanticAnalyzer(){

}

void SemanticAnalyzer::analyze(AST* root){
    currScope=new Scope(nullptr);
    visit(root);
    delete currScope;
}

DataType SemanticAnalyzer::analyzeExpression(AST* node){
    if(numberNode* numbernode=dynamic_cast<numberNode*>(node)){
        return DataType::INT;
    }
    
    if(variableNode* varnode=dynamic_cast<variableNode*>(node)){
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

    if(unaryOpNode* unarynode=dynamic_cast<unaryOpNode*>(node)){
        DataType type=analyzeExpression(unarynode->exp);
        if(type==DataType::INT && (unarynode->op.type==PLUS || unarynode->op.type==MINUS)){
            return type;
        }else if(type==DataType::BOOL && unarynode->op.type==NOT){
            return type;
        }
        string err="Unary Operator type mismatch";
        throw runtime_error(err);
    }

    if(binaryOpNode* binarynode=dynamic_cast<binaryOpNode*>(node)){
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

void SemanticAnalyzer::visit(AST* node){

    if(declareNode* declarenode=dynamic_cast<declareNode*>(node)){
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

    if(assignNode* assignnode=dynamic_cast<assignNode*>(node)){
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

    if(blockNode* blocknode=dynamic_cast<blockNode*>(node)){
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

    if(ifNode* ifnode=dynamic_cast<ifNode*>(node)){
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

    if(whileNode* whilenode=dynamic_cast<whileNode*>(node)){
        DataType type=analyzeExpression(whilenode->condition);
        if(type!=DataType::BOOL){
            throw runtime_error("Condition in the while loop should be BOOL");
        }
        visit(whilenode->condition);
        visit(whilenode->body);
        return ;
    }

    if(programNode* program=dynamic_cast<programNode*>(node)){
        for(auto statement:program->statements){
            visit(statement);
        }
        return ;
    }

}

