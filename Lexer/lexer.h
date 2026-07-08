//This file is defining the structure of the Lexer, what it will be containing, it's behaviour and attributes.
#ifndef LEXER_H
#define LEXER_H

#include<string>
#include "token.h"
using namespace std;

class Lexer{
private:
    //attributes
    string text;        //contain the input string 
    int currPos;        //contain the current Position 
    char currChar;      //contain the character at currPos
    
    Token number();     //It is a private method that will recognize a number and return the token (private because it is a internal helper function)
    Token identifier(); //It is a private method that will recognize the variable names and return the token (private because it is a internal helper function)
    char peek();        //It is a private method that will be used to know the next character in the input string without moving the currpos pointer of the string
public:
    //methods
    Lexer(string input);        //constructor-> initialise the text,currPos,currChar
    void advance();             //method to move pointer forward as all attributes are private member
    void skipWhiteSpace();      //this method will skip the unnecessary white spaces from the input string
    Token getNextToken();       //recognize the character and return its token

};
#endif