/*
ast.h
	
Name: Marco Salazar
Date: 03/29/2020
Description: This code implements a simple Abstract Syntax Tree to be used in later labs.

This is a header file, no inputs outputs or assumptions.

 */

#ifndef AST
#define AST

/*
 * This declares all the different types of nodes that will be used in the language.
 */
enum NODETYPE{
 VARDEC, 
 FUNDEC,
 PARAM,
 BLOCK,
 MYWRITE,
 MYNUM,
 MYVAR,
 MYREAD,
 MRETURN,
 ASSIGN,
 EMPTY,
 MYWHILE,
 MYIFTHEN,
 IFELSE,
 EXPRESSIONSTMT,
 EXPRESSION,
 MBOOL,
 BOOLNOT,
 CALL,
 ARG
}; // end of enum NODETYPE

/*
 * This declares all the different types of operators that will be allowed to be used in the language.
 */
enum OPERATORS{
    MAND,
    MOR,
    MPLUS,
    MMINUS,
    MMULT,
    MDIVIDE,
    MLE,
    MGE,
    MEQ,
    MNE,
    MLT,
    MGT,
    MNOT
};

/*
 * This declares all the valid Data types in the language.
 */
enum DATATYPE{
 INTTYPE,
 VOIDTYPE,
 BOOLEANTYPE
};

/*
 * This declares a structure of an ASTNode that will be used to create an Abstract Syntax Tree
 */
typedef struct ASTNodeType {
    char* Name;
    enum NODETYPE Type;
    enum OPERATORS op;
    enum DATATYPE datatype;
    struct ASTNodeType *s1, *s2, *next;
    int size;
    int value;
} ASTNode;

void indent(int level);
void OPprint(enum OPERATORS op);
void TYPEprint(enum DATATYPE d);

void ASTprint(ASTNode *p, int level);

ASTNode* ASTCreateNode(enum NODETYPE desiredType);

#endif
