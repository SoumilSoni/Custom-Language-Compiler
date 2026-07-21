#include<bits/stdc++.h>
#include "parser.h"
using namespace std;

//constructor => intialise the lexer and currToken
Parser::Parser(Lexer l):lexer(l){
    currToken=this->lexer.getNextToken();
    nextToken=this->lexer.getNextToken();
}

//eat function() => consumes the expected token else gives error
void Parser:: eat(tokenType type){ //type(argument of the function) is the expected token 
    if(currToken.type==type){
        currToken=nextToken;
        nextToken=lexer.getNextToken();
    }else{
        cout << "Expected: " << type << endl;
        cout << "Got: " << currToken.type << endl;
        throw runtime_error("Unexpected Token");
    }
}

//factor function() => deals with paranthesis, number and unary operator and return the pointer of the number node or the parent operator
AST* Parser::factor(){
    Token token=currToken;
    if(token.type==PLUS){               //unary plus (Implements the grammer rule F -> +F)
        eat(token.type);
        return new UnaryOpNode(token,factor());
    }else if(token.type==MINUS){        //unary minus (Implements the grammer rule F-> -F)
        eat(token.type);
        return new UnaryOpNode(token,factor());
    }else if(token.type==IDENTIFIER){   //it recognizes the variable and create a new node
        eat(token.type);
        return new VariableNode(token.value);
    }else if(token.type==NUMBER){ //This implements the grammer rule F -> number
        //it consumes the token moves forward and create a node in syntax tree and return its pointer
        eat(token.type);
        return new NumberNode(token.value);
    }else if(token.type==LEFTPAREN){ //This implements the grammer rule F -> (E)
        eat(LEFTPAREN);
        AST* node=comparison();
        eat(RIGHTPAREN);
        return node;
    }
    throw runtime_error("Invalid syntax");
}

// term function() => deals with * and / operator and return the pointer to the parent operator 
AST* Parser::term(){
    AST* node=factor(); // it gives the left operand of the operator
    while(currToken.type==MULTIPLY || currToken.type==DIVIDE){
        //it determines the operator and consumes it
        Token token=currToken;
        if(token.type==MULTIPLY){
            eat(MULTIPLY);
        }else if(token.type==DIVIDE){
            eat(DIVIDE);
        }
        // it creates a node with a binary operator as parent pointing to two operands in left and right and stores it on the left node for future operator,which defines the associativity in the grammer.
        node=new BinaryOpNode(node,token,factor());
    }
    return node;
}

// expression function() => deals with + and - operator and return the pointer to the parent operator
AST* Parser::expression(){
    AST* node=term(); // it gives the left operand of the operator
    while(currToken.type==PLUS || currToken.type==MINUS){
        // it determines the operator and consumes it
        Token token=currToken;
        if(token.type==PLUS){
            eat(PLUS);
        }else if(token.type==MINUS){
            eat(MINUS);
        }
        //it creates a binary operator node as parent with its left and right ppointer pointing to its operand and the pointer to the parent gets stored in the left node which can be used in next iteration. 
        node=new BinaryOpNode(node,token,term());
    }
    return node;
}

// statement function() => deals with variable assignment operation
AST* Parser::statement(){
    if(currToken.type==INT || currToken.type==BOOL){ //This implements S -> D
        return declare();
    }
    if(currToken.type==IDENTIFIER && nextToken.type==ASSIGN){ //This implements S -> id=L
        Token varToken=currToken;
        eat(IDENTIFIER);
        eat(ASSIGN);
        AST* node=logicalOr();
        eat(SEMI);
        VariableNode* varNode=new VariableNode(varToken.value);
        return new AssignNode(varNode,node);
    }
    if(currToken.type==IF){
        return ifStatement();
    }
    if(currToken.type==WHILE){
        return whileStatement();
    }
    AST* node=logicalOr();
    eat(SEMI);
    return node; //This implements S -> L
}

// declare function() => it deals with the declaration and initialization of the variable with it types
AST* Parser::declare(){
    DataType type;
    if(currToken.type==INT){
        type=DataType::INT;
        eat(INT);
    }else{
        type=DataType::BOOL;
        eat(BOOL);
    }
    Token varToken=currToken;
    eat(IDENTIFIER);
    VariableNode* varNode=new VariableNode(varToken.value);
    if(currToken.type==SEMI){
        eat(SEMI);
        return new DeclareNode(type,varNode);
    }
    eat(ASSIGN);
    AST* node=logicalOr();
    eat(SEMI);
    return new DeclareNode(type,varNode,node);
}

// program function() => deals with entire program and parse entire program sequentially
AST* Parser::program(){
    vector<AST*> statements; //It will store all statement sequentially
    while(currToken.type!=END){
        statements.push_back(statement()); //Adding statement to the program
    }
    return new ProgramNode(statements);
}

//comparison function() => deals with comparison operators and return the pointer to the parent operator
AST* Parser::comparison(){
    AST* node=expression();
    if(
        currToken.type==EQUAL || 
        currToken.type==NOT_EQUAL || 
        currToken.type==GREATER || 
        currToken.type==GREATER_EQUAL || 
        currToken.type==LESS || 
        currToken.type==LESS_EQUAL
    ){
        Token token=currToken;
        eat(token.type);
        node=new BinaryOpNode(node,token,expression());
    }
    return node;
}

// block function() => it is used to parse the statements inside different blocks like if and while
AST* Parser:: block(){
    eat(LEFTBRAC);
    vector<AST*> statements;
    while(currToken.type!=RIGHTBRAC){
        statements.push_back(statement());
    }
    eat(RIGHTBRAC);
    return new BlockNode(statements);
}

// ifStatement function() => it is used to parse the if-else statements it parse the condition and block of code inside both if and else statment
AST* Parser::ifStatement(){
    eat(IF);
    eat(LEFTPAREN);
    AST* condition=logicalOr();
    eat(RIGHTPAREN);
    BlockNode* thenbody=static_cast<BlockNode*>(block());
    if(currToken.type==ELSE){
        eat(ELSE);
        BlockNode* elsebody=static_cast<BlockNode*>(block());
        return new IfNode(condition,thenbody,elsebody);
    }
    return new IfNode(condition,thenbody);
}

//whileStatment function() => it is used to parse the while statement it parses the condition and block of code inside the while loop
AST* Parser::whileStatement(){
    eat(WHILE);
    eat(LEFTPAREN);
    AST* condition=logicalOr();
    eat(RIGHTPAREN);
    BlockNode* body=static_cast<BlockNode*>(block());
    return new WhileNode(condition,body);
}

//logicalOr function() => it deals with || operator and return the pointer to the parent operator
AST* Parser::logicalOr(){
    AST* node=logicalAnd();
    while(currToken.type==OR){
        Token token=currToken;
        eat(OR);
        node=new BinaryOpNode(node,token,logicalAnd());
    }
    return node;
}

//logicalAnd function() => it deals with && operator and return the pointer to the parent operator
AST* Parser::logicalAnd(){
    AST* node=logicalNot();
    while(currToken.type==AND){
        Token token=currToken;
        eat(AND);
        node=new BinaryOpNode(node,token,logicalNot());
    }
    return node;
}

//logicalNot function() => it deals with ! operator and return the pointer to the parent operator
AST* Parser::logicalNot(){
    if(currToken.type==NOT){
        Token token=currToken;
        eat(NOT);
        return new UnaryOpNode(token,logicalNot());
    }
    return comparison();
}

// parse function() => This is the entry point of the parser it calls the statement function and constructs the abstact syntax tree and return the pointer to the root of the tree.
AST* Parser::parse(){
    //it starts with the P-production rule and construct the whole syntax tree and return the root node of the constructed tree.
    AST* root=program();
    if(currToken.type!=END && nextToken.type!=END){
        throw runtime_error("Unexpected Token");
    }
    return root;
}
