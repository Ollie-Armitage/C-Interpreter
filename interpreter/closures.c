#ifndef COMPILER_2_0_CLOSURES_C
#define COMPILER_2_0_CLOSURES_C


#include "headers/environment.h"
#include <Lexer_Parser_Files/nodes.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <interpreter/headers/bindings.h>
#include <interpreter/headers/environment.h>
#include <Lexer_Parser_Files/C.tab.h>
#include "headers/interpret.h"

VALUE* build_closure(FRAME* env, NODE* ids, NODE* body){
    VALUE* value = malloc(sizeof(VALUE));
    CLOSURE* closure = malloc(sizeof(CLOSURE));
    closure->env = env;
    closure->ids = ids;
    closure->body = body;
    value->v.closure = closure;
    return value;
}

FRAME *extend_frame(ENV* env, NODE *ids, NODE *args) {

    FRAME *newEnv = malloc(sizeof(FRAME));

    if(ids == NULL || args == NULL){
        newEnv->next = (struct FRAME *) env->frames;
        return newEnv;
    }

    NODE *ip;
    NODE *ap;



    if (newEnv == 0) {
        printf("Frame Allocation Failed.\n ");
        return NULL;
    }
    // For the sequence of identifiers and the sequence of arguments, while neither of them are equal to null, work through them.



    // Do all up to the last one / two values.
    for (ip = ids, ap = args; (ip->left->type == ',' && ap->left->type == ','); ip = ip->left, ap = ap->left) {
        BINDING *newBinding = malloc(sizeof(BINDING));
        if (newBinding != 0) {

            newBinding->name = (TOKEN *) ip->right->right->left;
            newBinding->val = interpret(ap->right, env);
            newBinding->next = (struct BINDING *) newEnv->bindings;
            newEnv->bindings = newBinding;
            printf("Binding Allocated: %s\t Value: %ld\n", newBinding->name->lexeme, newBinding->val->v.integer);
        }
        else{
            printf("Error: Binding Allocation Failed.\n");
        }
    }

    // If two values left.

    if(ip->type == ',' && ap->type == ','){
        BINDING *newBinding = malloc(sizeof(BINDING));
        if (newBinding != 0) {

            newBinding->name = (TOKEN *) ip->right->right->left;
            newBinding->val = interpret(ap->right, env);
            newBinding->next = (struct BINDING *) newEnv->bindings;
            newEnv->bindings = newBinding;
            printf("Binding Allocated: %s\t Value: %ld\n", newBinding->name->lexeme, newBinding->val->v.integer);
        }
        else{
            printf("Error: Binding Allocation Failed.\n");
        }
        ip = ip->left;
        ap = ap->left;
    }

    // If one left.

    BINDING *newBinding = malloc(sizeof(BINDING));
    if (newBinding != 0) {

        newBinding->name = (TOKEN *) ip->right->left;
        newBinding->val = interpret(ap, env);
        newBinding->next = (struct BINDING *) newEnv->bindings;
        newEnv->bindings = newBinding;
        printf("Binding Allocated: %s\t Value: %ld\n", newBinding->name->lexeme, newBinding->val->v.integer);
    }
    else{
        printf("Error: Binding Allocation Failed.\n");
    }



    newEnv->next = (struct FRAME *) env->frames;
    return newEnv;
}

VALUE* lexical_call_method(TOKEN* name, NODE* args, ENV* env){
    printf("Entering function: %s\n", name->lexeme);
    CLOSURE* f = name_method(name, env->frames)->v.closure;
    ENV* tempEnv = malloc(sizeof(ENV));
    FRAME* newFrame = extend_frame(env, f->ids, args);
    tempEnv->frames = newFrame;
    VALUE* answer = interpret(f->body, tempEnv);
    return answer;
}

#endif //COMPILER_2_0_CLOSURES_C