//
// Created by ollie on 17/12/2019.
//

#ifndef COMPILER_2_0_TAC_H
#define COMPILER_2_0_TAC_H
#include <stdio.h>
#include <stdlib.h>
#include <Lexer_Parser_Files/nodes.h>
#include <Lexer_Parser_Files/C.tab.h>

typedef enum op{
    PLUS
} op;
typedef int arg;
typedef int result;
typedef int constant;
typedef int label; // Represents the index of an instruction in a sequence of instructions.

/* An assignment instruction could take the form: x = y op z where op is binary arithmetic or logical operation, and
 * x, y and z are addresses. */

/* Another assignment instruction could take the form: x = op y i.e. a unary operation. Examples of this could be
 * unary minus (i.e. x = -y), logical negation (i.e. x = !y) etc. */

/* Another assignment instruction could be copy instructions i.e. x = y, where x is assigned the value of y.*/

/* Another type of instruction is an unconditional jump i.e. goto L, where the three-address instruction with the label
 * L is the next to be executed. */

/* Another type of instruction is a conditional jump. i.e. if x goto L, or if (FALSE x) go to L. Otherwise, if the
 * specific condition is not met, carry on without jumping. */

/* Another type of instruction is a conditional jump with a relation operation (i.e. <, >, >= etc). Note this is
 * different to the conditional jump previously mentioned because it uses a binary operator i.e. (x relop y not
 * op y). The condition results are however the same as the other conditional jump. */

/* Other instructions include procedure calls, which may require parameters takes the form:
 * param1
 * param2...
 * param n
 * call p, n OR y = call p, n where p is the function name, and n is the function argument number (arity). */

typedef struct jump{
    op op;
    arg arg1;
    arg arg2;
    label result;
} JMP;

typedef struct param{
    op op;
    arg arg1;
} param;

/*typedef struct unary{
    op op;
    arg arg1;
    result result;
} unary; No unary operators in --C. */

typedef struct quadruple{
    op op;
    TOKEN* arg1;
    TOKEN* arg2;
    TOKEN* result;
} quad;


typedef enum instruction_type{
    PARAM,
    QUAD,
    JUMP,
} i_type;


typedef struct instruction{
    i_type type;
    union{
        param param;
        quad quad;
        JMP jump;
    } val;
    struct INS* next;
} INS;


typedef struct temporary{
    char* name;
}TEMP;

typedef struct block{
    INS* instruction;
} BLOCK;

typedef struct address{
    int type;
    union{
        TOKEN* name;
        int constant;
        TEMP* temporary;
        char* string;
    };
} ADDRESS;

void generate_TAC(NODE* tree, char* file_directory, int debug);
INS * generate(NODE* tree);

#endif //COMPILER_2_0_TAC_H
