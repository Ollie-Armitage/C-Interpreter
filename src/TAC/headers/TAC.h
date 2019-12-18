//
// Created by ollie on 17/12/2019.
//

#ifndef COMPILER_2_0_TAC_H
#define COMPILER_2_0_TAC_H

#include <stdlib.h>
#include <stdio.h>
#include "Lexer_Parser_Files/nodes.h"
#include "Lexer_Parser_Files/C.tab.h"
#include "src/TAC/headers/TAC.h"
#include "Lexer_Parser_Files/token.h"

enum op{
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    MOD,
    GREATER_THAN,
    LESS_THAN,
    GREATER_THAN_OR_EQUAL_TO,
    LESS_THAN_OR_EQUAL_TO,
    EQUAL_TO,
    NOT_EQUAL_TO
} OP;

/* TOKEN* name - Procedure to be called.
 * int arity - How many args that procedure has.*/

typedef struct call{
    TOKEN* name;
    int arity;
} CALL;

/* There will be n variables in this block. */

typedef struct block{
    int nvars;
} BLOCK;

/* Load an int or a variable name into a temp. */

typedef struct load{
    struct TAC* temp;
    union{
        int constant;
        TOKEN* variable;
    } value;

} LOAD;

/* Store a temp value in a token (variable). */

typedef struct store{
    struct TAC* temp;
    TOKEN* name;
} STORE;


typedef struct tac{
    int tac_number;
    enum OP* op;
    union {
        BLOCK block;
        CALL call;
        LOAD load;
        STORE store;
    } args;
    TOKEN* result;
    struct TAC* next;
} TAC;

/* Basic block - List of TACs. */

typedef  struct  bb {
    TAC* leader;
} BB;






int generate_TAC(NODE *tree, char* file_directory, int debug);


#endif //COMPILER_2_0_TAC_H
