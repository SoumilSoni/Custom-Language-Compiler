// Defining the tokens in this file e.g plus, minus, number etc.

#ifndef TOKEN_H
#define TOKEN_H

#include<string>
using namespace std;

//It defines all possible token types or names of all possible tokens in the language
enum tokenType{ 
    NUMBER,                 //numbers
    PLUS,                   //+
    MINUS,                  //-
    MULTIPLY,               //*
    DIVIDE,                 // /
    LEFTPAREN,              // (
    RIGHTPAREN,             // )
    IDENTIFIER,             // variables
    ASSIGN,                 // =
    EQUAL,                  // ==
    NOT_EQUAL,              // !=
    GREATER,                // >
    LESS,                   // <
    GREATER_EQUAL,          // >=
    LESS_EQUAL,             // <=
    AND,                    // &&
    OR,                     // ||
    NOT,                    // !
    SEMI,                   // ; (statement seperators)
    IF,                     // if keyword
    ELSE,                   // else keyword
    WHILE,                  //while keyword
    LEFTBRAC,               // {
    RIGHTBRAC,              // }
    INT,                    // int keyword
    BOOL,                   // bool keyword
    END                     // End of input string
};

//It describes every token has a type and value e.g Token(NUMBER(type),"3"(value)), Token(PLUS,"+") etc.
struct Token{
    tokenType type;
    string value;
    //Default parameter for the Token 
    Token(){
        type=END;
        value="";
    }
    
    //Parametersied constructor for the token
    Token(tokenType t,string v){
        type=t;
        value=v;
    }
};
#endif