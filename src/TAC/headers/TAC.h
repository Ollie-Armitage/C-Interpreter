//
// Created by ollie on 17/12/2019.
//

#ifndef COMPILER_2_0_TAC_H
#define COMPILER_2_0_TAC_H

#include <stdlib.h>
#include <stdio.h>
#include "Lexer_Parser_Files/nodes.h"
#include "src/interpreter/headers/environment.h"
#include "Lexer_Parser_Files/C.tab.h"
#include "src/TAC/headers/TAC.h"
#include "src/interpreter/headers/interpret.h"
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

typedef struct quad{
    enum OP* op;
    TOKEN* arg1;
    TOKEN* arg2;
    TOKEN* result;
    struct QUAD* next;
} QUAD;

typedef struct triple{
    enum OP* op;
    TOKEN* arg1;
    TOKEN* arg2;
} TRIPLE;

/* Basic block - List of Quads. */

typedef  struct  bb {
    QUAD* leader;
} BB;


/* TOKEN* name - Procedure to be called.
 * int arity - How many args that procedure has.*/

typedef struct call{
    TOKEN* name;
    int arity;
} CALL;

/* */

typedef struct block{
    int nvars;
} BLOCK;

int generate_TAC(NODE *tree, ENV *e, char* file_directory, int debug);


#endif //COMPILER_2_0_TAC_H
