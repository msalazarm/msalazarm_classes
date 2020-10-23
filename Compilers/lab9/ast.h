/*
ast.h
	
Name: Marco Salazar
Date: 05/6/2020
Description: This code implements a simple Abstract Syntax Tree.

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
 ARG,
 INTDEC
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
    char* Name;// the name of the node
    char* label; // the label if needed for the node
    enum NODETYPE Type;// the specific NODETYPE of the node
    enum OPERATORS op;// what mathematical or logical operator it is
    enum DATATYPE datatype; // int void or boolean
    struct ASTNodeType *s1, *s2, *next;
    int size;// how much space it takes up
    int value;// what value it holds
    struct SymbTab *symbol;// so we can have access to symbol in code generation
} ASTNode;

void indent(int level);
void OPprint(enum OPERATORS op);
void TYPEprint(enum DATATYPE d);

void ASTprint(ASTNode *p, int level);

ASTNode* ASTCreateNode(enum NODETYPE desiredType);

//formal and actuals
int check_formals_and_params(ASTNode * f, ASTNode *a);

#endif
