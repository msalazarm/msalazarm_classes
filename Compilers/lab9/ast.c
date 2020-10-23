/*
ast.c
	
Name: Marco Salazar
Date: 05/6/2020
Description: This code implements a simple Abstract Syntax Tree.

This program simply takes in an AST pointer and prints out the entire Abstract Syntax Tree according to the rules of the language.
The input is a Global Pointer to the AST.
The output is a printed form of the AST.
The Assumption is that the AST pointer is not null and that the AST follows the rules layed out in the language.

 */
#include "symtable.h"
#include "ast.h"
#include <stdio.h>
#include <malloc.h>
/*
 * This code prints out an abstract syntax tree recursively.
Pre: p is not null, if it is nothing will be printed.
Post: the AST from the point of p will be printed.
 */
void ASTprint(ASTNode *p, int level){
    if (p == NULL) return;
    if(p->Type != EMPTY) indent(level);//if it is not a worthless branch then indent
    switch(p->Type){
        case VARDEC:
            printf("Variable ");
            TYPEprint(p->datatype);
            printf("%s", p->Name);
            //value is used to indicate if there is an array
            if(p->value > 0) printf("[%d]", p->value);
            printf(" has offset %d", (p->symbol)->offset);//changed to show the offset
            printf("\n");
            ASTprint(p->s1, level);
            break;
        case FUNDEC:
            TYPEprint(p->datatype);
            printf("FUNCTION %s\n", p->Name);
            printf(" max offset %d", (p->symbol)->mysize);//changed to show the offset
            //if there is no node the function has no parameters
            if (p->s1 == NULL){
                indent(level+1);
                printf("(VOID) \n");
            }
            //else it has parameters.
            else{
                indent(level+1);
                printf("(\n");
                ASTprint(p->s1, level+1);
                indent(level+1);
                printf(")\n");
            }
            //no matter what the body of the function must be printed
            ASTprint(p->s2, level+1);
            break;
        case PARAM:
            printf("Paramater ");
            TYPEprint(p->datatype);
            printf(" %s", p->Name);
            //if size is -1 it is an array refrence being passed.
            if(p->size == -1){
                printf("[]");
            }
            printf("\n");
            break;
        case BLOCK:
            printf("BLOCK STATMENT\n");
            ASTprint(p->s1, level+1);
            ASTprint(p->s2, level+1);
            break;
        case MYWRITE:
            printf("WRITE STATMENT\n");
            if (p->s1 != NULL) ASTprint(p->s1, level+1);
            else  printf("%s %s \n",p->label, p->Name);
            break;
        case MYNUM:
            printf("Number with value %d\n", p->size);
            break;
        case MYREAD:
            printf("READ STATMENT\n");
            ASTprint(p->s1, level+1);
            break;
        case MYVAR:
            printf("IDENTIFIER %s\n", p->Name);
            //if size is -1 it is an array refrence being called.
            if(p->size == -1){
                indent(level+1);
                printf("Array Reference [\n");
                ASTprint(p->s1, level +2);
                indent(level+1);
                printf("] end of array \n");
            }
            break;
        case MRETURN:
            printf("Returning \n");
            // if size does not equal -1 then returning is returning something, so print it.
            if(p->size != -1){
             ASTprint(p->s1, level+1);
            }
            break;
        case ASSIGN:
            printf("Assignment STATMENT \n");
            ASTprint(p->s1, level +1);
            ASTprint(p->s2, level + 1);
            break;
        case EMPTY:
            //a case used for empty branches so no errors are made.
            break;
        case MYWHILE:
            printf("WHILE Statement \n");
            ASTprint(p->s1, level + 1);
            ASTprint(p->s2, level + 2);
            break;
        case MYIFTHEN:
            printf("IF Statement \n");
            ASTprint(p->s1, level+1);
            ASTprint(p->s2, level);
            break;
        case IFELSE:
            printf("Then \n");
            ASTprint(p->s1, level+1);
            indent(level);
            printf("Else \n");
            ASTprint(p->s2, level+1);
            break;
        case EXPRESSIONSTMT:
            printf("EXPRSTMT\n");
            ASTprint(p->s1, level + 1);
            break;
        case EXPRESSION:
            printf("EXPR ");
            OPprint(p->op);
            printf("\n");
            ASTprint(p->s1, level+1);
            ASTprint(p->s2, level+1);
            break;
        case MBOOL:
            //while not used in this version, I have this rule just in 
            //case normal Booleans will be used instead of numbers.
            printf("BOOLEAN ");
            //if the value is 1 its true
            if(p->value == 1){
                printf("true\n");
            }else{
                //otherwise it is false
                printf("false\n");
            }
            break;
        case BOOLNOT:
            printf("Not \n");
            ASTprint(p->s1, level+1);
            break;
        case CALL:
            printf("CALL FUNCTION %s\n", p->Name);
            ASTprint(p->s1, level+1);
            break;
        case ARG:
            printf("ARG \n");
            ASTprint(p->s1, level+1);
            //changed
            //ASTprint(p->s2, level);
            break;
        default:
            printf("UNKOWN type is ASTPrint %d\n", p->Type);
            
            break;
    }
    ASTprint(p->next, level);
} // of ASTprint

/*
 * This code indents the code according to what level it is at in the AST.
Pre: level is greater than 0
Post: The specified number of indents will be printed.
 */
void indent(int level){
 while(level > 0){
     printf(" ");
     level = level-1;
 }
}

/*
 * This code will print out the correct operator when given an enum OPERATORS type.
pre: given a valid OPERATORS declared in the number
post: will print out the correct OPERATORS
 */
void OPprint(enum OPERATORS op){
    switch(op){
        case MAND:
            printf("AND");
            break;
        case MOR:
            printf("OR");
            break;
        case MPLUS:
            printf("+");
            break;
        case MMINUS:
            printf("-");
            break;
        case MMULT:
            printf("*");
            break;
        case MDIVIDE:
            printf("/");
            break;
        case MLE:
            printf("<=");
            break;
        case MGE:
            printf(">=");
            break;
        case MEQ:
            printf("==");
            break;
        case MNE:
            printf("!=");
            break;
        case MLT:
            printf("<");
            break;
        case MGT:
            printf(">");
            break;
    };
}

/*
 * This code prints out the correct DATATYPE
Pre: given a correct DATATYPE according to what is declared in the enum
Post: prints out the correct DATATYPE
 */
void TYPEprint(enum DATATYPE d){
    switch(d){
        case INTTYPE:
            printf("INT ");
            break;
        case VOIDTYPE:
            printf("VOID ");
            break;
        case BOOLEANTYPE:
            printf("BOOLEAN ");
            break;
        default:
            printf("UNKOWN type def %d\n", d);
            break;
        
    }
}

/*
 * Creates an ASTNode and sets everything to a default value.
Pre: The given  NODETYPE is valid.
Post: an empty ASTNode will be created.
 */
ASTNode* ASTCreateNode(enum NODETYPE desiredType){
    ASTNode *p;
    p = (ASTNode *)(malloc(sizeof (struct ASTNodeType)));
    p->Type = desiredType;
    p->op = 0;
    p->next = NULL;
    p->s1 = NULL;
    p->s2 = NULL;
    p->value = 0;
    p->datatype = 0;
    p->size = 0;
    p->symbol = NULL;
    return p;
} // of ASTCreateNode

/*
 * Function to check formal and actual parameters
 * Pre:None, but only use this for paramaters
 * Post: returns 1 if true, and 0 for false
 * it is true if the paramaters match and are of the same length
 */
int check_formals_and_params(ASTNode * f, ASTNode *a){
    if( (f == NULL) && (a == NULL) ) return 1;
    if( (f == NULL) || (a == NULL) ) return 0;
    if( f->datatype != a->datatype ) return 0;
    return check_formals_and_params(f->next, a->next);
    
}
