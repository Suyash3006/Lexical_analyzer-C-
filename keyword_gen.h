#include<iostream>
#include "def.h"
using namespace std;

int keyword_find(string tok){
    if(tok == "short"){
        return SHORT;
    }else if(tok == "int"){
        return INT;
    }else if(tok == "float"){
        return FLOAT;
    }else if(tok == "double"){
        return DOUBLE;
    }else if(tok == "char"){
        return CHAR;
    }else if(tok == "bool"){
        return BOOL;
    }else if(tok == "signed"){
        return SIGNED;
    }else if(tok == "unsigned"){
        return UNSIGNED;
    }else if(tok == "for"){
        return FOR;
    }else if(tok == "while"){
        return WHILE;
    }else if(tok == "do"){
        return DO;
    }else if(tok == "return"){
        return RETURN;
    }else if(tok == "struct"){
        return STRUCT;
    }else if(tok == "const"){
        return CONST;
    }else if(tok == "void"){
        return VOID;
    }else if(tok == "switch"){
        return SWITCH;
    }else if(tok == "break"){
        return BREAK;
    }else if(tok == "case"){
        return CASE;
    }else if(tok == "continue"){
        return CONTINUE;
    }else if(tok == "goto"){
        return GOTO;
    }else if(tok == "long"){
        return LONG;
    }else if(tok == "static"){
        return STATIC;
    }else if(tok == "union"){
        return UNION;
    }else if(tok == "default"){
        return DEFAULT;
    }else if(tok == "if"){
        return IF;
    }else if(tok == "else"){
        return ELSE;
    }else if(tok == "+"){
        return PLUS;
    }else if(tok == "-"){
        return MINUS;
    }else if(tok == "*"){
        return MULT;
    }else if(tok == "/"){
        return DIV;
    }else if(tok == "%"){
        return PERCENT;
    }else if(tok == "++"){
        return PLUS_PLUS;
    }else if(tok == "--"){
        return MINUS_MINUS;
    }else if(tok == "="){
        return EQ;
    }else if(tok == "+="){
        return PLUS_EQ;
    }else if(tok == "-="){
        return MINUS_EQ;
    }else if(tok == "*="){
        return MULT_EQ;
    }else if(tok == "/="){
        return DIV_EQ;
    }else if(tok == "=="){
        return EQ_EQ;
    }else if(tok == "<"){
        return LESSER;
    }else if(tok == "<="){
        return LESS_EQ;
    }else if(tok == ">"){
        return GREATER;
    }else if(tok == ">="){
        return GREAT_EQ;
    }else if(tok == "["){
        return L_SQUARE;
    }else if(tok == "]"){
        return R_SQUARE;
    }else if(tok == "("){
        return L_PARAEN;
    }else if(tok == ")"){
        return R_PARAEN;
    }else if(tok == "main"){
        return MAIN;
    }else if(tok == "{"){
        return L_CBRACE;
    }else if(tok == "}"){
        return R_CBRACE;
    }else if(tok == ","){
        return COMMA;
    }else if(tok == ";"){
        return SEMICOL;
    }else{
        return NOTOK;
    }
}