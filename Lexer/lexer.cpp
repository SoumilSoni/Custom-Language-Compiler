#include "lexer.h"
#include<bits/stdc++.h>
using namespace std;

//Consturctor of the Lexer class defined in lexer.h
//intialise the text(input string) currPos and currChar
Lexer::Lexer(string input){
    text=input;
    currPos=0;
    if(!text.empty()){
        currChar=text[currPos];
    }else{
        currChar='\0';
    }
}

//Advance function()=> moves the currPos(pointer to the input string) forward and update the currChar
void Lexer::advance(){
    currPos++;
    if(currPos<text.size()){
        currChar=text[currPos];
    }else{
        currChar='\0';
    }
}

//peek function()=>helps to check the next character without actually moving to it.
char Lexer::peek(){
    int nextPos=currPos+1;
    if(nextPos>=text.size()){
        return '\0';
    }
    return text[nextPos];
}

//SkipWhiteSpace function()=> Skips the unwanted spaces in the input string 
void Lexer::skipWhiteSpace(){
    while(currChar==' ' || currChar=='\t' || currChar=='\n'){
        advance();
    }
}

//Number function()=> It is a private function in the lexer.h and it will recognize the number in the input string and return the token
Token Lexer::number(){
    string result="";
    while(currChar>='0' && currChar<='9'){
        result+=currChar;
        advance();
    }
    return Token(NUMBER,result);
}

//Identifier function()=> This is a private function in the lexer.h and it will recognize the variable in the inout string and return the token 
Token Lexer::identifier(){
    string result="";
    while(
        (currChar>='a' && currChar<='z') ||
        (currChar>='A' && currChar<='Z') ||
        (currChar>='0' && currChar<='9') ||
        (currChar)=='_'
    ){
        result+=currChar;
        advance();
    }
    //identifying keywords
    if(result=="if"){
        return Token(IF,"if");
    }
    if(result=="else"){
        return Token(ELSE,"else");
    }
    if(result=="while"){
        return Token(WHILE,"while");
    }
    if(result=="int"){
        return Token(INT,"int");
    }
    if(result=="bool"){
        return Token(BOOL,"bool");
    }
    return Token(IDENTIFIER,result);
}

//getNextToken function()=> This is the main function of the lexer analysis. It iterates on the input string scans it until it is exhausted and convert the characters into their correeponding tokens and return them. 
Token Lexer::getNextToken(){
    
    while(currChar!='\0'){
        //Removes white spaces
        if(currChar==' ' || currChar=='\t' ||currChar=='\n'){
            skipWhiteSpace();
            continue;
        }
        //detect the variable in the string and convert it into token
        if(
            (currChar>='a' && currChar<='z') ||
            (currChar>='A' && currChar<='Z')
        ){
            return identifier();
        }

        //detect logical operator and convert them into token

        if(currChar=='&' && peek()=='&'){
            advance();
            advance();
            return Token(AND,"&&");
        }
        if(currChar=='|' && peek()=='|'){
            advance();
            advance();
            return Token(OR,"||");
        }
        if(currChar=='!'){
            advance();
            return Token(NOT,"!");
        }
        //detect the comparison operator and convert them into token

        //detect the equal_to operator and convert it into token
        //it is placed before the assignment check beacuse the lexer works on a rule that is "Longest matching first"
        if(currChar=='=' && peek()=='='){
            advance();
            advance();
            return Token(EQUAL,"==");
        }
        //detect not_equal_to operator and convert it into token
        if(currChar=='!' && peek()=='='){
            advance();
            advance();
            return Token(NOT_EQUAL,"!=");
        }
        //detect greater_than and greater_than_equal_to operators and convert them into token
        if(currChar=='>'){
            advance();
            if(currChar=='='){
                advance();
                return Token(GREATER_EQUAL,">=");
            }
            return Token(GREATER,">");
        }
        //detect less_than and less_than_equal_to operators and convert them into token
        if(currChar=='<'){
            advance();
            if(currChar=='='){
                advance();
                return Token(LESS_EQUAL,"<=");
            }
            return Token(LESS,"<");
        }
        //detect the assignment operator and convert it into token
        if(currChar=='='){
            advance();
            return Token(ASSIGN,"=");
        }
        //detect a number in the string and convert it into token
        if(currChar>='0' && currChar<='9'){
            return number();
        }
        //detect arithmetic signs and paranthesis and convert them into token 
        
        if(currChar=='+'){
            advance();
            return Token(PLUS,"+");
        }
        if(currChar=='-'){
            advance();
            return Token(MINUS,"-");
        }
        if(currChar=='*'){
            advance();
            return Token(MULTIPLY,"*");
        }
        if(currChar=='/'){
            advance();
            return Token(DIVIDE,"/");
        }
        // detect brackets and convert them into token
        if(currChar=='('){
            advance();
            return Token(LEFTPAREN,"(");
        }
        if(currChar==')'){
            advance();
            return Token(RIGHTPAREN,")");
        }
        if(currChar=='{'){
            advance();
            return Token(LEFTBRAC,"{");
        }
        if(currChar=='}'){
            advance();
            return Token(RIGHTBRAC,"}");
        }
        // detect the semicolon and convert it into token(it works as a statement seperator)
        if(currChar==';'){
            advance();
            return Token(SEMI,";");
        }
        //If the character doesn't belong to any of the symbol then it will throw an error.
        throw runtime_error("Invalid Character");
    }
    //At last it return the END(i.e the string has completetly scanned).
    return Token(END,"");
}

