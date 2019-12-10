#ifndef COMPILER_2_0_BINDINGS_C
#define COMPILER_2_0_BINDINGS_C

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "headers/environment.h"
#include "Lexer_Parser_Files/token.h"

VALUE *name_method(TOKEN *token, FRAME *frame) {
    while (frame != NULL) {
        BINDING *bindings = frame->bindings;
        while (bindings != NULL) {
            if (bindings->name == token) return bindings->val;
            bindings = (BINDING *) bindings->next;
        }
        frame = (FRAME *) frame->next;
    }
    return NULL;
}

VALUE *assignment(TOKEN *token, FRAME *frame, VALUE *value) {
    while (frame != NULL) {
        BINDING *bindings = frame->bindings;
        while (bindings != NULL) {
            if (bindings->name == token) bindings->val = value;
            return NULL;
        }
        frame = (FRAME *) frame->next;
    }
    return NULL;
}

VALUE *declaration_method(TOKEN *token, FRAME *frame) {
    BINDING *bindings = frame->bindings;
    BINDING *new = malloc(sizeof(BINDING));
    if (new != 0) {
        new->name = token;
        new->val = NULL;
        new->next = (struct BINDING *) bindings;
        frame->bindings = new;
        return NULL;
    }
    else return NULL;
}

#endif // BINDINGS_C