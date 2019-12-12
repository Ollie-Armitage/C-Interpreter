//
// Created by ollie on 08/12/2019.
//

#ifndef COMPILER_2_0_TAC_VALUE_H
#define COMPILER_2_0_TAC_VALUE_H

//
// Created by ollie on 08/12/2019.
//

typedef struct call {
    TOKEN* name;
    int arity;
} CALL;

typedef struct block{
    int nvars;
} BLOCK;

typedef struct tac{
    int op; // TODO: Better as an enum, work this out.
    union{ CALL call; BLOCK block;} args;
    struct TAC* next;
} TAC;

typedef struct bb{
    TAC* leader;
} BB;

#endif //COMPILER_2_0_TAC_VALUE_H
