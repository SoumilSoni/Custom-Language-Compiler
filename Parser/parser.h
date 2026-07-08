#ifndef PARSER_H
#define PARSER_H

#include "../Lexer/lexer.h"
#include "../Ast/ast.h"
using namespace std;

class Parser{
private:
    //attributes
    Lexer lexer; //Parser will use lexer internally
    Token currToken; //It contains the current token of the input string that is being processed
    Token nextToken; //It contains the next token of the input string (used in assignment operator)

    AST* program(); //This function is representing the grammer rule " P -> SP | epsilon "
    // It will handle the exection of all the statement in the program.

    AST* statement(); //This function is representing the grammer rule " S -> D | L | I | W"
    //It will handle the assignment operartion i.e. assigning values to the variables.

    AST* declare();

    AST* expression();// This function is representing the grammer rule " E -> TE' " and " E' -> +TE' | -TE' | epsilon "
    //It will handle the + and - operator and join it with the left and right operand and construct the syntax tree, it returns the pointer of the operator.

    AST* term(); //This function is representing the grammer rule " T -> FT' " and " T' -> *FT' | /FT' | epsilon "
    //It will handle the * and / operator and join it with the left and right operand and construct the syntax tree, it returns the pointer of the operator.

    AST* factor(); // This function is representing the grammer rule  "F -> +F | -F | number | (E)"
    //It will handle the numbers,unary operator and deal with paranthesis and return the node pointer representing the number node in the syntax tree.

    AST* comparison(); // This function is representing the grammer rule " C -> EC' " and "C' -> (==)EE' | epsilon "
    // It will handle the comparator operators and its precedence is less than the arithmetic operator.

    AST* block();

    AST* ifStatement();

    AST* whileStatement();
    
    AST* logicalOr();

    AST* logicalAnd();

    AST* logicalNot();

public:
    //methods
    Parser(Lexer l); //It is the constructor of the Parser
    void eat(tokenType type); //It consumes the token if the matches with the expected type
    AST* parse(); //This function is the entry point of the parser and it constructs the whole parse tree and return the pointer of the root.
};

#endif
/*
                                                -----Grammer Rule-----

                                            P -> SP | epsilon  (implemented using program function) 
                                            S -> D | A | L | I | W (id==IDENTIFIER) (implemented using statement function)
                                            D -> TY id(=C)? (TY=type) (implemented using declare function)
                                            A -> id=L
                                            TY -> int | bool
                                            W -> while(L)B (implemented using whileStatement function)
                                            I -> if(L)B | if(L)B else B (implemented using ifStatement function)
                                            B ->{SP} (implemented using block function)
                                            L -> O( || O)* (implemented using logicalOr fuction)
                                            O -> A( && A)* (implemented using logicalAnd function)
                                            A -> !A | C (implemented using logicalNot function)
                                            C -> E((== | != | >= | > | <= | <) E)? (implemented using comparison function)
                                            E -> T ((+ | -) T)* (implemented using expression function)
                                            T → F ((* | /) F)* (implemented using term function)
                                            F -> (+|-)F | number | identifier | (L) (implemented using factor function)
*/
/*
                                            -----Precedence Order-----
                                    less pre ---------------------->>>> more prec
                                    !-> comparison -> && -> || ->  *,/ -> +,- -> number
*/