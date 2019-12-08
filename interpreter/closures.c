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
#include <interpreter/headers/value.h>
#include "headers/interpret.h"

VALUE* build_closure(FRAME* env, NODE* ids, NODE* body){
    VALUE* value;
    CLOSURE* closure = malloc(sizeof(CLOSURE));
    closure->env = env;
    closure->ids = ids;
    closure->body = body;
    value = make_closure_value(closure);
    return value;
}

FRAME *extend_frame(ENV* env, NODE *ids, NODE *args) {

    // Build a new frame for a function and attach the current frame from the environment provided to it's end.

    FRAME *newFrame = malloc(sizeof(FRAME));
    newFrame->next = (struct FRAME *) env->frames;

    // If there are no parameters or no arguments, return the new frame empty.

    if(ids == NULL || args == NULL) return newFrame;

    NODE *ip;
    NODE *ap;

    // Do all up to the last one / two values.
    for (ip = ids, ap = args; (ip->left->type == ',' && ap->left->type == ','); ip = ip->left, ap = ap->left) {
        BINDING *newBinding = malloc(sizeof(BINDING));
        if (newBinding != 0) {

            newBinding->name = (TOKEN *) ip->right->right->left;
            newBinding->val = interpret(ap->right, env);
            newBinding->next = (struct BINDING *) newFrame->bindings;
            newFrame->bindings = newBinding;
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
            newBinding->next = (struct BINDING *) newFrame->bindings;
            newFrame->bindings = newBinding;
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
        newBinding->next = (struct BINDING *) newFrame->bindings;
        newFrame->bindings = newBinding;
        printf("Binding Allocated: %s\t Value: %ld\n", newBinding->name->lexeme, newBinding->val->v.integer);
    }
    else{
        printf("Error: Binding Allocation Failed.\n");
    }

    // Once all the parameters have arguments bound to them, and are stored in the new frame, return the new frame.

    return newFrame;
}

VALUE* lexical_call_method(TOKEN* name, NODE* args, ENV* env){
    //TODO: Problem is that environment is being updated before args are evaluated.

    ENV* tempEnv = malloc(sizeof(ENV));
    *tempEnv = *env;

    // Gets the function from the environment.
    CLOSURE* f = name_method(name, env->frames)->v.closure;

    env->frames = extend_frame(env, f->ids, args);
    env->frames->next = (struct FRAME *) f->env;



    // Runs the function and returns its output.
    printf("Entering function: %s\n", name->lexeme);
    VALUE* answer = interpret(f->body, env);
    *env = *tempEnv;
    free(tempEnv);
    return answer;
}

#endif //COMPILER_2_0_CLOSURES_C