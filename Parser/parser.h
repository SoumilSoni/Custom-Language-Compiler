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

    AST* statement(); //This function is representing the grammer rule " S -> D | A | L | I | W" and " A -> id=L "
    //It will handle the assignment operartion i.e. assigning values to the variables.

    AST* block(); // This function is representing the grammer " B -> {SP} "
    // This function is representing a block of code which is used in conditional statement or loop blocks

    AST* ifStatement(); // This function is representing the grammer " I -> if(L)B | if(L)B else B "
    //This function is representing the if-else statement it parses the condition and the if and else block statements

    AST* whileStatement();// This function is representing the grammer " W -> while(L)B"
    //This function is representing the while loop block and it parse the condition and the block of while loop

    AST* declare();// This function is representing the grammer " D -> TY id(=C)? " and  " TY -> int | bool "
    //It handles the declaration and initialization of the variable

    AST* logicalOr();// This function is representing the grammer " L -> OL' " and " L' -> ||OL' | epsilon "
    //It handles the logical OR operator and parses the left and right operand by calling the logicalAnd()
    
    AST* logicalAnd();// This function os representing the grammer " O -> AO' " and " O' -> &&AO' | epsilon "
    //It handles the logical AND operator and parses the left an right operand by calling the logicalNot()
    
    AST* logicalNot(); // This function is representing the grammer " A -> !A | C "
    // It handles the logical NOT operator and calls itself recursively or it calls the comparison()
    
    AST* comparison(); // This function is representing the grammer rule " C -> EC' " and " C' -> ==EC' | !=EC' | >=EC' | <=EC' | >EC' | <EC' | epsilon "
    // It will handle the comparator operators and its precedence is less than the arithmetic operator.

    AST* expression();// This function is representing the grammer rule " E -> TE' " and " E' -> +TE' | -TE' | epsilon "
    //It will handle the + and - operator and join it with the left and right operand and construct the syntax tree, it returns the pointer of the operator.

    AST* term(); //This function is representing the grammer rule " T -> FT' " and " T' -> *FT' | /FT' | epsilon "
    //It will handle the * and / operator and join it with the left and right operand and construct the syntax tree, it returns the pointer of the operator.

    AST* factor(); // This function is representing the grammer rule  "F -> +F | -F | number | (E)"
    //It will handle the numbers,unary operator and deal with paranthesis and return the node pointer representing the number node in the syntax tree.
    
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
                                            A -> id=L
                                            D -> TY id(=C)? (TY=type) (implemented using declare function)
                                            TY -> int | bool
                                            I -> if(L)B | if(L)B else B (implemented using ifStatement function)
                                            W -> while(L)B (implemented using whileStatement function)
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
                    Precedence                  Operators                   Associativity
                    1.(Highest)                 Unary+, Unary-, !           Right-to-Left
                    2.                          *, /                        Left-to-Right
                    3.                          +, -                        Left-to-Right
                    4.                          >, <, >=, <=                Left-to-Right
                    5.                          ==, !=                      Left-to-Right
                    6.                          &&                          Left-to-Right
                    7.(Lowest)                  ||                          Left-to-Right
*/