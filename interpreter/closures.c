#ifndef COMPILER_2_0_CLOSURES_C
#define COMPILER_2_0_CLOSURES_C


#include "headers/environment.h"
#include <Lexer_Parser_Files/nodes.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <interpreter/headers/bindings.h>
#include "headers/interpret.h"

FRAME *extend_frame(ENV *env, NODE *ids, NODE *args) {
    NODE *ip;
    NODE *ap;

    FRAME *newEnv = malloc(sizeof(FRAME));
    if (newEnv == 0) {
        printf("Frame Allocation Failed.\n ");
        return NULL;
    }
    newEnv->bindings = NULL;

    // For the sequence of identifiers and the sequence of arguments, while neither of them are equal to null, work through them.

    for (ip = ids, ap = args; ip != NULL && ap != NULL; ip = ip->right, ap = ap->right) {
        BINDING *new = malloc(sizeof(BINDING));
        if (new != 0) {
            new->name = (TOKEN *) ip->left;
            new->val = interpret(ip->right, env);
            new->next = (struct BINDING *) newEnv->bindings;
        }
    }
}

VALUE* lexical_call_method(TOKEN* name, NODE* args, ENV* env){
    CLOSURE* f = name_method(name, env->frames);
    FRAME* newEnv = extend_frame(env, f->ids, args);
    newEnv->next = (struct FRAME *) env->frames;
    return interpret(f->body, env);
}

#endif //COMPILER_2_0_CLOSURES_C