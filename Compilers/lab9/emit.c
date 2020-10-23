/*
emit.c
	
Name: Marco Salazar
Date: 05/6/2020
Description: This code emits the MIPS code when given an AST

This program simply takes in an AST pointer and prints out the MIPS code
The input is a Global Pointer to the AST.
The output is a printed MIPS code
The Assumption is that the AST pointer is not null and that the AST follows the rules layed out in the language.

 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ast.h"
#include "emit.h"


static int GLABEL = 0;  // global label counter
char * CURR_FUNCTION;  // the current function we are in

//to get rid of warning in emit_identifier
void emit_expr(ASTNode *p, FILE *fp);

/*
 * since the labels do not need to be human readable
 * this function genereates labels that never conflict with themselves
 * or with global names.
 * precondition: NONE
 * Post: will return a unique label
 */
char * genlabel()
{  char s[100];
   char *s1;
   sprintf(s,"_L%d",GLABEL++);
   s1=strdup(s);  // get heap memory for the label name
   return (s1);
}

// precondition ptr to astnode
// post prints out all of the strings in MIPS format
void EMITSTRINGS(ASTNode *p, FILE *fd){
    if(p == NULL) return;
    if((p->Type == MYWRITE) && (p->Name != NULL)){
        fprintf(fd, "%s:\t .asciiz\t%s\n", p->label, p->Name);
    }
    EMITSTRINGS(p->next, fd);
    EMITSTRINGS(p->s1, fd);
    EMITSTRINGS(p->s2, fd);
}


// precondition ptr to astnode
// post prints out all of the global variables in MIPS format
void EMITGLOBALS(ASTNode *p, FILE *fd){
    if(p == NULL) return;//if it is void, print out nothing
    if((p->Type == VARDEC) && (p->symbol->level == 0)){
        fprintf(fd, "%s:\t .space\t%d\n", p->Name, p->symbol->mysize*WSIZE);
    }
    EMITGLOBALS(p->next, fd);
    EMITGLOBALS(p->s1, fd);
}

// helper function to make clean MIPS code
// Take in 4 params, and print them out pretty
// PRE : given 3 strings, print them out in Assembly formatting
//       in fp
//    example emit(fp, "L1", "ldi R!#, 15", "# load a number "
void emit(FILE *fp, char *Label, char * command, char *comment){
    if (strcmp("",Label) == 0){//if there is no label
        fprintf(fp,"\t\t%s\t\t%s\n", command, comment);
    }else{// if there is a label
        fprintf(fp,"%s:\t\t%s\t\t%s\n", Label, command, comment);
    }
}

/*emit_identifier
 * pre: p is a PTR to an IDENT node
 * post: MIPS code such that $a0 is the address of where the identifier is
 */
void emit_identifier(ASTNode *p, FILE *fp){
    //we need to figure out if ident is global or local
    //we need to figure out if ident is a scalar or array
    char s[100];
    if(p->symbol->IsAFunc == 2){// is an array
        emit_expr(p->s1, fp);//a0 has index of element in array
        emit(fp, "", "move $a1 $a0", "#index of the array");
        sprintf(s, "sll $a1 $a1 %d", LOGWSIZE);
        emit(fp, "", s, "#shift index twice to left for Word Size");
    }else{
        emit(fp, "", "li $a1 0", "#not array, so index is 0");
    }
    //if a local variable
    if(p->symbol->level > 0){
        sprintf(s, "add $a1 $a1 %d", p->symbol->offset * WSIZE);
        emit(fp, "", s, "# add index + location of beginning of array from sp");
        emit(fp, "", "add $a0, $sp, $a1", "# identifier is a scaler");
        emit(fp, "", "", "");
    }else{// is global
        sprintf(s, "la $a0, %s", p->symbol->name);
        emit(fp, "", s, "# identifier is a global scaler");
        emit(fp, "", "add $a0 $a0 $a1", "#add the index offset if array");
        emit(fp, "", "", "");
        
    }
}

//prototype to get rid of warnings ins emit_expr
void emit_call(ASTNode *p, FILE *fp);

/*emit_expr
 * Pre: a PTR to an expression as defined in the YACC language
 * Post: MIPS code taht sets the $a0 to the value of PTR
 */
void emit_expr(ASTNode *p, FILE *fp){
    if(p == NULL) return;//if it is null, do nothing to avoid errors
    char s[100];
    //switch statement to deal with all expression cases
    switch(p->Type){
        case MYNUM:
                if(p->datatype == BOOLEANTYPE){
                    sprintf(s, "li $a0, %d", p->size);
                    emit(fp, "", s, "# expression is a Boolean");
                    return;
                }else{
                    sprintf(s, "li $a0, %d", p->size);
                    emit(fp, "", s, "# expression is a NUMBER");
                    return;
                }
            break;
        case MYVAR:
                emit_identifier(p, fp); // we know that $a0 is the address of MYVAR
                emit(fp, "", "lw $a0 ($a0)", "# fetch value for the var");
                return;
            break;
        case CALL:
            emit_call(p, fp); // $a0 will be the value of the called function
            return;
    }
    
    //expression 
    
    //as the recrusive case lets store s1 and then perform operation on it and s2
    emit_expr(p->s1, fp);
    sprintf(s, "sw $a0 %d($sp)", p->symbol->offset*WSIZE);
    emit(fp, "", s, "# store s1 in temporary spot");
    emit_expr(p->s2, fp);
    emit(fp, "", "move $a1 $a0", "#move a0 to a1");
    sprintf(s, "lw $a0 %d($sp)", p->symbol->offset*WSIZE);
    emit(fp, "", s, "# load a0 with the temp value");
    
    //perform operation on s1 and s2
    switch(p->op){
        case MAND:
            emit(fp, "", "and $a0 $a0 $a1", " # perform and");
            break;
        case MOR:
            emit(fp, "", "or $a0 $a0 $a1", "# perform or");
            break;
        case MPLUS:
            emit(fp, "", "add $a0 $a0 $a1", "# perform addition");
            break;
        case MMINUS:
            emit(fp, "", "sub $a0 $a0 $a1", "# perform subtraction");
            break;
        case MMULT:
            emit(fp, "", "mult $a0 $a1", "# preform multiplication");
            emit(fp, "", "mflo $a0", "# save the lower multiplication in a0");
            break;
        case MDIVIDE:
            emit(fp, "", "div $a0 $a1", "# perform division");
            emit(fp, "", "mflo $a0", "# save the quotient in a0");
            break;
        case MLE:
            emit(fp, "", "sle $a0 $a0 $a1", "# is a0 <= a1");
            break;
        case MGE:
            emit(fp, "", "sge $a0 $a0 $a1", "# is a0 >= a1");
            break;
        case MEQ:
            emit(fp, "", "seq $a0 $a0 $a1", "# is a0 == a1");
            break;
        case MNE:
            emit(fp, "", "sne $a0 $a0 $a1", "# is a0 != a1");
            break;
        case MLT:
            emit(fp, "", "slt $a0 $a0 $a1", "# is a0 < a1");
            break;
        case MGT:
            emit(fp, "", "sgt $a0 $a0 $a1", "# is a0 > a1");
            break;
        case MNOT:
            emit(fp, "", "sltiu $a0 $a0 1", "# not of a0");
            break;
    }
    
}

/*
 * function to set up the Head MIPS code for a function
 * pre: given an non null node that is for a function
 * post: will emit the setup necessary for that function
 */
void emit_function_head(ASTNode *p, FILE *fp){
    char s[100];
    emit(fp, p->Name, "", "# start of Function");
    //set the global FUNCTION variable
    CURR_FUNCTION = p->Name;
    
    //build the stack pointer movement
    
    sprintf(s, "subu $a0, $sp, %d", p->symbol->mysize*WSIZE);
    emit(fp, "", s, "# adjust the stack for function setup");
    emit(fp, "", "sw $sp, ($a0)", "");
    emit(fp, "", "sw $ra, 4($a0)", "");
    emit(fp, "", "move $sp, $a0", "# adjust the stack pointer");
    emit(fp, "", "", "");
}

/*
 * method to handle explicit and implicit function returns
 * Pre: ptr to return or null
 * post: return code in MIPS printed in fp
 */
void emit_function_return(ASTNode *p, FILE *fp){
    /* we have to do things different if it is main*/
    
    if (p !=NULL){
        // we need to evaluate the expr
        emit_expr(p, fp); // this leaves $a0 with the result
        
    }
    // if it is NULL, we do nothing with $a0;
    
    // adjust activation recode back
    emit(fp,"","","");
    emit(fp, "", "lw $ra, 4($sp)"," #restore RA");
    emit(fp, "", "lw $sp, ($sp)"," #restore SP");
    emit(fp,"","","");
    if (strcmp(CURR_FUNCTION, "main") == 0){
        //handle main returns
        emit(fp, "", "li $v0, 10", "# leave MAIN program");
        emit(fp, "", "syscall", "# Leave MAIN");
    }else{// every other funtion
        // use JUMP to go back to where $ra refrences
        emit(fp, "", "jr $ra", "#jump back to the previous context");
    }
}

/*
 * Pre: ptr to return or null
 * post: returns the call code printed in MIPS to fp
 */
void emit_call(ASTNode *p, FILE *fp){
    char s[100];
    //if there are paramaters, process them
    if(p->s1 != NULL){
        ASTNode *param = p->s1;
        while( param != NULL){
            emit_expr(param->s1, fp); // a0 has the value of the paramaters
            sprintf(s, "sw $a0 %d($sp)", param->symbol->offset*WSIZE);
            emit(fp, "", s, "# store s1 in temporary spot");
            param = param->next;
        }
    }
    
    //calculate the future stack pointer
    sprintf(s, "subu $t2, $sp, %d", p->symbol->mysize*WSIZE);
    emit(fp, "", s, "# adjust the stack for function setup");
    
    //if there are paramaters, copy them into their function positions
    if(p->s1 != NULL){
        ASTNode *param = p->s1;
        int fparamoffset = 2;
        while( param != NULL){
            sprintf(s, "lw $a0 %d($sp)", param->symbol->offset*WSIZE);
            emit(fp, "", s, "# load one of the paramaters");
            sprintf(s, "sw $a0 %d($t2)", fparamoffset*WSIZE);
            emit(fp, "", s, "# load one of the paramaters");
            
            param = param->next;
            fparamoffset = fparamoffset + 1;
        }
    }
    
    sprintf(s, "jal %s", p->Name);
    emit(fp, "", s, "#jump to the function");
}

/*
 * Pre: ptr to return or null
 * Post: prints out the while loop code in MIPS to fp
 */
void emit_while(ASTNode *p, FILE *fp){
    char s[100];
    //generate labels for the states
    char *L1;
    char *L2;
    L1 = genlabel();
    L2 = genlabel();
    
    //checking the while condition
    sprintf(s, "%s", L1);
    emit(fp, s, "", "# check while condition");
    emit_expr(p->s1, fp); //a0 has the value of the condition
    emit(fp, "", "li $t0 0", "#flag to compare against for branching");
    
    sprintf(s, "beq $a0 $t0 %s", L2);
    emit(fp, "", s, "# if false jump out of while statement");
    
    //do the inner loop
    EMITAST(p->s2, fp);
    sprintf(s, "j %s", L1);
    emit(fp, "", s, "#go back to back to check to while expression");
    
    //leave the loop
    sprintf(s, "%s", L2);
    emit(fp, s, "", "# exit while clause");
    
    
}

/*
 * Pre: ptr to return or null
 * post: prints out the if then else statements in MIPS to fp
 */
void emit_if(ASTNode *p, FILE *fp){
    char s[100];
    //create labels for different states
    char *L1;
    char *L2;
    L1 = genlabel();
    L2 = genlabel();
    
    //find out if expr is true or false
    emit_expr(p->s1, fp); //a0 has the value of the expression
    emit(fp, "", "li $t0 0", "#flag to compare against for branching");
    
    //jump to false branch if so
    sprintf(s, "beq $a0 $t0 %s", L1);
    emit(fp, "", s, "# if not equal jump to else");
    
    //true branch
    emit(fp, "", "", "#beginning of true branch");
    EMITAST(p->s2->s1, fp);
    //leave after done
    sprintf(s, "j %s", L2);
    emit(fp, "", s, "#leave if-else branch");
    //false branch
    sprintf(s, "%s", L1);
    emit(fp, s, "", "# beginning of false branch");
    EMITAST(p->s2->s2, fp);
    sprintf(s, "%s", L2);
    emit(fp, s, "", "# end of if-else branch");
    //out of branches
    
    
    
}

/*
 * Pre: ptr to return or null
 * Post: writes out the MIPS code to fp for an assign statement
 */
void emit_assign(ASTNode *p, FILE *fp){
    char s[100];
    emit_expr(p->s2, fp); //value is in a0
    sprintf(s, "sw $a0 %d($sp)", p->symbol->offset*WSIZE);
    emit(fp, "", s, "# move value to be assigned temporarily");
    emit_identifier(p->s1, fp);// identifiers location is in a0
    sprintf(s, "lw $a1 %d($sp)", p->symbol->offset*WSIZE);
    emit(fp, "", s, "# load a1 saved expression");
    //assign the value
    emit(fp, "", "sw $a1 ($a0)", "# save value in memory");
}

/*emit_write MIPS code for write
 * Pre: ptr to a write node
 * post: MIPS code for write in fp
 */
void emit_write(ASTNode *p, FILE *fp){
    char s[100];
    if(p->s1 == NULL){//is a string
        sprintf(s, "la $a0 %s", p->label);
        emit(fp, "", s, "# load a0 with the string address");
        emit(fp, "", "li $v0 4", "# prepare for the syscall to print string");
        emit(fp, "", "syscall", "# print the string");
        emit(fp, "", "", "");
        
    }else{// is an expression
        emit_expr(p->s1, fp); // $a0 has the value set from Expression
        emit(fp, "", "li $v0, 1", "# print the number");
        emit(fp, "", "syscall", "# system call for print number");
        emit(fp, "", "", "");
    }
    emit(fp, "", "la $a0 _NL", "# load with a newline character");
    emit(fp, "", "li $v0 4", "# prepare to print new line");
    emit(fp, "", "syscall", "# system call to print newline");
    emit(fp, "", "", "");
    
}

/*emit_read MIPS code for read
 * Pre: ptr to a read node
 * post: MIPS code for read in fp
 */
void emit_read(ASTNode *p, FILE *fp){
    emit_identifier(p->s1, fp); // $a0 has the value set from Expression
    emit(fp, "", "li $v0, 5", "# read a number from input");
    emit(fp, "", "syscall", "# system call for print number");
    emit(fp, "", "sw $v0, ($a0)", "#store the number in memory");
    emit(fp, "", "", "");  // we know that $v0 has the value we read in
    
}

/*
 * EMITAST(ASTNode p, File fp)
 * Takes an AST tree and outputs in fp the mips code
 */
void EMITAST(ASTNode *p, FILE *fp){
    if(p == NULL) return;//if null return so there are no errors
    switch (p->Type){//print out according to type
        case VARDEC: //we don't need any code here
            break;
        case FUNDEC:
            emit_function_head(p, fp);
            EMITAST(p->s2, fp); // the block
            emit_function_return(NULL, fp);
            break;
        case BLOCK:
            EMITAST(p->s2,fp);
            break;
        case MYWRITE:
            emit_write(p, fp);
            break;
        case MYREAD:
            emit_read(p, fp);
            break;
        case ASSIGN:
            emit_assign(p, fp);
            break;
        case MYIFTHEN:
            emit_if(p, fp);
            break;
        case MYWHILE:
            emit_while(p,fp);
            break;
        case EXPRESSIONSTMT:
            if(p->s1 != NULL){//if expression statement is not null, then print out expression
                emit_expr(p->s1, fp);
            }
            break;
        case MRETURN:
            emit_function_return(p->s1, fp);
            break;
        default: 
            printf("Emit AST Type not implemented\n");
    }// end of switch
    EMITAST(p->next, fp);
}








